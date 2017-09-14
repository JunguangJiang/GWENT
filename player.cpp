#include "player.h"
#include "carddatabase.h"
#include <algorithm>
#include <QDebug>
#include "parameter.h"
#include "deck.h"
#include <QFile>
#include <QDir>
using namespace gwent;
class game;
//--------------------外部调用接口------------------------------

Player::Player(const int userId, QObject *parent) : QObject(parent), m_userId(userId)
{//初始时，需确定用户的id
    m_hasChosenPassed=false;//初始时没有选择让过,
    m_isOnTurn=false;//也没有轮到发牌
    m_isDispatchingCard=false;//也没有在调度
    m_dispatchingCardNumber=0;//已经调度0张卡
    m_timerSwitch=false;//一开始关闭定时器

    m_game=(Game*)parent;

    m_totalStrengthShow=Q_NULLPTR;
    m_background=Q_NULLPTR;

   //新建一个定时器线程
    m_timerThread=new QThread(this);
    m_timerThread->start();

    m_leftTime=PlayerDealTime;//每回合的时间是10s
    m_timer=new QTimer(0);
    m_timer->setInterval(1000);//每隔1s响应一次

    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_oneSecondGone()), Qt::DirectConnection);
    connect(m_timerThread, SIGNAL(finished()), m_timer, SLOT(deleteLater()));//当线程结束时，自动删除定时器

    m_timer->start();
    m_timer->moveToThread(m_timerThread);

    for(int i=0; i<3; i++)
    {
        m_finalStrength[i]=0;
    }
}

Player::~Player()
{
    //终止线程
    m_timerThread->quit();
    m_timerThread->wait();
    m_timerThread->deleteLater();
}


void Player::chooseBackgroud(GraphicsItem* background, int standPoint)//选择游戏背景
{
    m_background=background;
    m_standPoint=standPoint;
    switch (standPoint) {
    case OURSIDE:
        closeBattle=new BattleField(COMBAT_ROW::CLOSE,background);
        remoteBattle=new BattleField(COMBAT_ROW::REMOTE, background);
        siegeBattle=new BattleField(COMBAT_ROW::SIEGE, background);
        handCard=new HandCard(OURSIDE, background);//新建的手牌是属于己方的手牌
        library=new Library(OURSIDE, background);
        graveyard=new Graveyard(OURSIDE, background);
        m_totalStrengthShow=new text(PlayerStrengthShowPos[OURSIDE], PlayerStrengthShowSize, m_background);
        m_totalStrengthShow->setBackgroundColor(Qt::darkBlue);
        break;
    case ENEMY:
        closeBattle=new BattleField(COMBAT_ROW::ENEMY_CLOSE,background);
        remoteBattle=new BattleField(COMBAT_ROW::ENEMY_REMOTE, background);
        siegeBattle=new BattleField(COMBAT_ROW::ENEMY_SIEGE,background);
        handCard=new HandCard(ENEMY,background);
        library=new Library(ENEMY, background);
        graveyard=new Graveyard(ENEMY, background);
        m_totalStrengthShow=new text(PlayerStrengthShowPos[ENEMY], PlayerStrengthShowSize, m_background);
        m_totalStrengthShow->setBackgroundColor(Qt::darkRed);
        break;
    }

    //总分的显示设置
    m_totalStrengthShow->setFontSize(24);
    m_totalStrengthShow->setFontColor(Qt::white);
    m_totalStrengthShow->setCenter();

    //每当战排比分改变时，更新总比分的显示
    connect(this->closeBattle,SIGNAL(updateBattleStrengthShow()), this, SLOT(updateTotalStrengthShow()));
    connect(this->remoteBattle,SIGNAL(updateBattleStrengthShow()), this, SLOT(updateTotalStrengthShow()));
    connect(this->siegeBattle,SIGNAL(updateBattleStrengthShow()), this, SLOT(updateTotalStrengthShow()));

    if(m_standPoint==ENEMY)//如果这个牌组是对方的
    {
        this->handCard->setUnseen();//则手牌区不可见
    }
}

void Player::createCard(Card *card)//玩家创建一张新的卡牌，并连接到当前的游戏和背景，设置其id值
{
    if(m_game)
    {
        card->setGame(m_game);//设置每张卡牌的游戏指针，这样才能发挥卡牌的各种拓展功能
        card->setId(m_card.size());//设置卡牌在玩家中的编号，用于后续的网络传输
        m_card.push_back(card);//将所有卡牌的地址都存入m_card中
        if(m_background)
        {
            card->setParentItem(m_background);//设置其背景为当前的游戏背景
        }
    }
}

void Player::chooseDeck(int deckId)//选择自己编号为deckId的卡组
{
    if(!m_game)
    {
        qDebug()<<"game is not created";//在选择卡组之前一定要先进入一个游戏，获得指向这个游戏的指针
        return;
    }

    QFile file(DeckFilePrefix+QString::number(deckId)+QString(".dat"));//打开存储牌组的文件

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"error reading";
        return;
    }

    Deck newDeck(deckId);
    QDataStream in(&file);
    in>>newDeck;//读入这个牌组

    qDebug()<<"Leader number:"<<newDeck.getNthCardId(0);

    CardDatabase cardDatabase;//打开牌组数据库

    int size=newDeck.getSize();

    for(int i=0; i<size; i++)
    {
        int idOfDatabase=newDeck.getNthCardId(i);//newDeck中存储的是在每张牌在数据库中的编号
        Card* card=cardDatabase.getCardWithIdOfDatabase(idOfDatabase);//从数据库中读入这张牌,
        createCard(card);//将这张卡加入玩家
        connect(card, SIGNAL(cardMoveBy(QPointF,Card*)), this, SLOT(on_cardMoveBy(QPointF,Card*)));//连接和移动相关的信号
        if(i==0)
        {
            handCard->setLeader(card);//卡组第一张总是领袖
        }else
        {
            library->addCard(card);//初始时刻，其余卡牌都放进卡库中
        }
    }
}

void Player::setDeck(Deck* deck)
{
    if(!m_game)
    {
        qDebug()<<"game is not created";//在选择卡组之前一定要先进入一个游戏，获得指向这个游戏的指针
        return;
    }

    qDebug()<<"Leader number:"<<deck->getNthCardId(0);

    CardDatabase cardDatabase;//打开牌组数据库

    int size=deck->getSize();

    for(int i=0; i<size; i++)
    {
        int idOfDatabase=deck->getNthCardId(i);//newDeck中存储的是在每张牌在数据库中的编号
        Card* card=cardDatabase.getCardWithIdOfDatabase(idOfDatabase);//从数据库中读入这张牌,
        createCard(card);//将这张卡加入玩家
        connect(card, SIGNAL(cardMoveBy(QPointF,Card*)), this, SLOT(on_cardMoveBy(QPointF,Card*)));//连接和移动相关的信号
        if(i==0)
        {
            handCard->setLeader(card);//卡组第一张总是领袖
        }else
        {
            library->addCard(card);//初始时刻，其余卡牌都放进卡库中
        }
    }
}

void Player::shuffleCards()//洗牌,伪随机，之后需要改成真随机
{
    library->shuffleCards();
}


void Player::drawInitCards()//游戏初始时抽手牌
{
    for(int i=0; i<10; i++)
    {
        drawACardFromLibrary();
    }
}

void Player::drawACardFromLibrary()//从牌库中抽一张牌
{
    Card* card=library->drawACard();
    if(card)
    {
        handCard->addCard(card);
    }
}
/*
void Player::dispatchCardFromTo(Card *oldCard, Card *newCard)//调度第i个选手的一张卡牌,此处存疑
{
    handCard->removeCard(oldCard);
    handCard->addCard(newCard);
}*/

void Player::setIsDispatchingCard(bool isDispatchingCard)
{
    m_isDispatchingCard=isDispatchingCard;
    if(isDispatchingCard)
    {
        turnOnTimer();
    }else
    {
        turnOffTimer();
    }
}

void Player::dispatchCard(Card *oldCard)
{
    if(!oldCard)
        return;

    m_dispatchingOldCard[m_dispatchingCardNumber]=oldCard;
    m_dispatchingCardNumber++;

    qDebug()<<"my dispatching number"<<m_dispatchingCardNumber;
    qDebug()<<"old card name"<<QString::fromStdString(oldCard->getName());

    handCard->removeCard(oldCard);
    library->addCard(oldCard);

    Card *newCard=library->drawACardByRandom();

    if(!newCard)
    {
        return;
    }

    for(int i=0; i<m_dispatchingCardNumber; i++)
    {
        qDebug()<<"newcard name"<<QString::fromStdString(newCard->getName());
        if(newCard->getName()==m_dispatchingOldCard[i]->getName())//如果调度抽到的卡和之前的丢掉的卡是同名卡
        {
            library->addCard(newCard);//则将其放回卡库
            newCard=library->drawACardByRandom();//重新抽卡
            i=0;
            break;
        }
    }

    //如果总算抽到一张和之前丢掉的卡都不是同名卡的卡牌
    handCard->addCard(newCard);//则将其加入手牌

    if(m_dispatchingCardNumber>=3)
    {
        emit endDispatchingCard();
        return;
    }
}

void Player::getTurn()//获得出牌机会
{
    if(handCard->getSize()==0)//如果手牌为空
    {
        choosePassed();//自动让过
    }

    if(!m_hasChosenPassed)//在没有选择让过的情况下
    {
        qDebug()<<"Player "<<QString::number(m_userId)<<"get turn";

        m_hasDealed=false;//新的一局还没有发牌

        handCard->setMoveable(true);//我方手牌可移动

        m_isOnTurn=true;//轮到出牌

        turnOnTimer();//打开定时器

        m_leftTime=PlayerDealTime;//定时10s

        emit playerGetTurn();//向外界发送自己得到回合的信号
    }
    else
    {
        loseTurn();//让过情况下，自动放弃出牌
    }
}

void Player::loseTurn()//失去出牌机会
{
    if(m_isOnTurn)
    {
        qDebug()<<"Player "<<QString::number(m_userId)<<"lose turn";

        handCard->setMoveable(false);//设置手牌的可移动属性

        m_isOnTurn=false;

        turnOffTimer();//关闭定时器

        m_leftTime=PlayerDealTime;

    }
    emit playerLoseTurn();

}


void Player::addCardFromHandToBattle(Card *card, COMBAT_ROW combatRow)//从手牌中发出一张牌到战排上,此时我方选手还没有失去回合
{
    if(combatRow==COMBAT_ROW::NO_COMBATROW)//如果是特殊卡牌
    {
        handCard->removeCard(card);//手牌区需要删除卡牌
        card->setLeftTop(SpecialCardPos);//将其放置在特殊卡的位置
        card->on_handToBattleField(combatRow);//发动每个牌的部署效果，同时发送出牌的信号
        m_hasDealed=true;//当前已经发出卡牌
    }
    else//如果是一般卡，则放到相应战排
    {
        BattleField *battleField=getBattle(combatRow);
        if(battleField->checkTypeOf(card))//如果卡牌能够加入战排中
        {
            battleField->addCard(card);//相应战排加入卡牌
            handCard->removeCard(card);//手牌区需要删除卡牌
            card->on_handToBattleField(combatRow);//发动每个牌的部署效果，同时发送出牌的信号
            m_hasDealed=true;
        }
    }
}

void Player::updateFinalStrength(int currentRound)
{
    if(currentRound>=3)
        return;

    m_finalStrength[currentRound]=getTotalStrength();
    qDebug()<<"the final strength of round"<<currentRound <<" is "<<m_finalStrength[currentRound];
}

void Player::enterANewRound()//进入新的一个回合
{
    closeBattle->clearAll();//清除所有卡牌及天气效果
    remoteBattle->clearAll();
    siegeBattle->clearAll();
    qDebug()<<"clear battle";

    m_hasChosenPassed=false;//此时我方没有选择让过
    updatePassShow();

    m_isOnTurn=false;//还暂时不能移动手牌
}

void Player::loseOneHandcardByRandom()//随机丢弃一张手牌
{
    if(handCard->getSize()==0)//如果手牌为空
    {
        choosePassed();//自动让过
        return;
    }
    int i=qrand()%handCard->getSize();//否则随机找到一张牌
    Card *card=handCard->getNthCard(i);
    if(card)
    {
        handCard->removeCard(card);//将该卡从手牌移动到墓地
        graveyard->addCard(card);
    }

}

//--------------------内部属性查询接口--------------------------

int Player::getTotalStrength() const//计算玩家的总分
{
    int totalStrength=0;
    totalStrength+=closeBattle->getTotalStrength();
    totalStrength+=remoteBattle->getTotalStrength();
    totalStrength+=siegeBattle->getTotalStrength();
    return totalStrength;
}//获得总分

BattleField *Player::getBattle(COMBAT_ROW combatRow)const//根据combatrow返回相应的战排指针
{
    switch (combatRow) {
    case COMBAT_ROW::CLOSE:
    case COMBAT_ROW::ENEMY_CLOSE:
        return closeBattle;
    case COMBAT_ROW::REMOTE:
    case COMBAT_ROW::ENEMY_REMOTE:
        return remoteBattle;
    case COMBAT_ROW::SIEGE:
    case COMBAT_ROW::ENEMY_SIEGE:
        return siegeBattle;
    default:
        return nullptr;
    }
}

COMBAT_ROW Player::getBattleFieldOfPoint(QPointF point) const
{
    qreal left=BattleFieldLeftTopPoint[static_cast<int>(COMBAT_ROW::CLOSE)].x();
    qreal top=BattleFieldLeftTopPoint[static_cast<int>(COMBAT_ROW::CLOSE)].y();
    qreal width=BattleFieldSize.width();
    qreal height=BattleFieldSize.height();
    qreal x=point.x();
    qreal y=point.y();
    if(
            (x > left)&&
            (x < (left+width))&&
            (y > top)&&
            (y < (top+3*height))
            )
    {
        if(y<top+height)
        {
            return COMBAT_ROW::CLOSE;
        }
        else if(y<top+2*height)
        {
            return COMBAT_ROW::REMOTE;
        }
        else
        {
            return COMBAT_ROW::SIEGE;
        }
    }
    return COMBAT_ROW::NO_COMBATROW;//其余情况，则不在战排内

}

Card *Player::getWeakestCard()const//优先返回近战卡
{
    Card *weakestCard=this->getBattle(COMBAT_ROW::CLOSE)->getWeakestCard();
    Card *nextCard=this->getBattle(COMBAT_ROW::REMOTE)->getWeakestCard();
    weakestCard=Card::getWeakerCard(weakestCard, nextCard);
    nextCard=this->getBattle(COMBAT_ROW::SIEGE)->getWeakestCard();
    weakestCard=Card::getWeakerCard(weakestCard, nextCard);
    return weakestCard;
}

Card *Player::getStrongestCard()const//优先返回近战卡
{
    Card *strongestCard=this->getBattle(COMBAT_ROW::CLOSE)->getStrongestCard();
    Card *nextCard=this->getBattle(COMBAT_ROW::REMOTE)->getStrongestCard();
    strongestCard=Card::getStrongerCard(strongestCard, nextCard);
    nextCard=this->getBattle(COMBAT_ROW::SIEGE)->getStrongestCard();
    strongestCard=Card::getStrongerCard(strongestCard, nextCard);
    return strongestCard;
}


//------------------外部响应接口-------------------------------

void Player::choosePassed() //选择让过
{
    if(!m_hasChosenPassed)
    {
        m_hasChosenPassed=true;
        updatePassShow();
    }
}

void Player::hideBordersOfAllBattles()//所有的战排的边框都不显示
{
    closeBattle->hideBorder();
    remoteBattle->hideBorder();
    siegeBattle->hideBorder();
}

void Player::on_cardReleaseAt(QPointF point, Card *card)
{
    COMBAT_ROW combatRow=getBattleFieldOfPoint(point);//先求得当前点所属战排
    if(combatRow==COMBAT_ROW::NO_COMBATROW){//如果当前点不在己方战排上
        return;//返回
    }
    else//否则，根据所在战排
    {
        this->addCardFromHandToBattle(card,combatRow);//向该战排加入卡牌
    }
    this->hideBordersOfAllBattles();//先隐藏所有的战排边框
    updateAllBorders();
}

void Player::on_cardMoveBy(QPointF point, Card *card)
{
    this->hideBordersOfAllBattles();//先隐藏所有的战排边框

    COMBAT_ROW combatRow=getBattleFieldOfPoint(point);//然后求得当前点所属战排
    if(combatRow!=COMBAT_ROW::NO_COMBATROW)//如果当前点在己方战排上
    {
        this->getBattle(combatRow)->showBorder();//根据所在的战排点亮该战排的边框
    }
    updateAllBorders();
}

void Player::updateAllBorders()
{
    closeBattle->update();
    remoteBattle->update();
    siegeBattle->update();
}

void Player::updateTotalStrengthShow()//更新总分的显示
{
    if(m_totalStrengthShow)
    {
        m_totalStrengthShow->setText(std::to_string(getTotalStrength()));
        m_totalStrengthShow->update();
    }
}

void Player::updatePassShow()//更新玩家是否选择了让过
{
    handCard->showPass(m_hasChosenPassed);

}

void Player::on_oneSecondGone()//每隔1s响应一次
{
    if(m_timerSwitch)//如果计时器打开
    {
        m_leftTime--;//每隔1s剩余时间减一
        qDebug()<<m_leftTime;


        if(m_isDispatchingCard)
        {
            if(m_leftTime==0)
            {
                emit endDispatchingCard();
                turnOffTimer();
            }
            return;
        }

        if(m_isOnTurn)
        {
            if(m_leftTime==0)//如果减到0，
            {
                if(m_hasDealed==false)//如果当前没有发牌
                {
                    loseOneHandcardByRandom();//失去一张手牌作为惩罚
                }
                loseTurn();//失去发牌机会
                return;//返回
            }
        }

    }
}

QDataStream &operator<<(QDataStream &out, const Player &player)
{
    out << (int)player.m_card.size();
    for(int i=0; i<player.m_card.size(); i++)
    {
        out<<*(player.m_card[i]);
    }

    out<<*(player.closeBattle);
    out<<*(player.remoteBattle);
    out<<*(player.siegeBattle);
    out<<*(player.handCard);
    out<<*(player.library);
    out<<*(player.graveyard);

    //out << player.m_leftTime << player.m_isOnTurn << player.m_hasChosenPassed;
    out << player.m_hasChosenPassed;

    for(int i=0; i<3; i++)
    {
        out<<player.m_finalStrength[i];
    }

    return out;

}

QDataStream &operator>>(QDataStream &in, Player &player)
{
    int size;
    in >> size;

    for(int i=0; i<player.m_card.size(); i++)
    {
        in>>*(player.m_card[i]);
    }

    if(size > player.m_card.size())//如果传输过来的卡组数量增加，说明出现了衍生物，那么对于该玩家的卡组后面继续增加卡牌
    {
        CardDatabase cardDatabase;
        for(int i=player.m_card.size(); i<size; i++)
        {
            Card card;
            in>>card;

            Card *newCard=cardDatabase.getCardWithIdOfDatabase(card.getIdOfDatabase());
            player.createCard(newCard);
            qDebug()<<"create derivative";

            newCard->setActualCombatRow(card.getActualCombatRow());
            newCard->setStatus(card.getStatus());
            newCard->setStrength(card.getActualStrength());
            if(card.hasShield())
                newCard->getShield();
            newCard->getArmor(card.hasArmor());
        }
    }

    in>>*(player.closeBattle);
    in>>*(player.remoteBattle);
    in>>*(player.siegeBattle);
    in>>*(player.handCard);
    in>>*(player.library);
    in>>*(player.graveyard);

    //in >> player.m_leftTime >> player.m_isOnTurn >> player.m_hasChosenPassed;
    in >> player.m_hasChosenPassed;
    player.updatePassShow();

    for(int i=0; i<3; i++)
    {
        in >> player.m_finalStrength[i];
    }

    //将传递过程中的id转化为card指针
    player.closeBattle->m_currentCard.clear();
    for(int i=0; i<player.closeBattle->m_transformData.size(); i++)
    {
        struct TransformData data=player.closeBattle->m_transformData[i];
        int id=data.id;
        if(data.loyalty)//如果这种卡牌是忠诚的
        {
            player.closeBattle->addCard(player.m_card[id]);//到我方玩家处取卡牌信息
        }
        else
        {
            if(player.m_game)//否则到敌方玩家处取卡牌信息
            {
                player.closeBattle->addCard(player.m_game->getPlayer(ENEMY)->m_card[id]);
            }
        }
    }

    player.remoteBattle->m_currentCard.clear();
    for(int i=0; i<player.remoteBattle->m_transformData.size(); i++)
    {
        struct TransformData data=player.remoteBattle->m_transformData[i];
        int id=data.id;
        if(data.loyalty)
        {
            player.remoteBattle->addCard(player.m_card[id]);
        }
        else
        {
            if(player.m_game)
            {
                player.remoteBattle->addCard(player.m_game->getPlayer(ENEMY)->m_card[id]);
            }
        }
    }

    player.siegeBattle->m_currentCard.clear();
    for(int i=0; i<player.siegeBattle->m_transformData.size(); i++)
    {
        struct TransformData data=player.siegeBattle->m_transformData[i];
        int id=data.id;
        if(data.loyalty)
        {
            player.siegeBattle->addCard(player.m_card[id]);
        }
        else
        {
            if(player.m_game)
            {
                player.siegeBattle->addCard(player.m_game->getPlayer(ENEMY)->m_card[id]);
            }
        }
    }

    player.handCard->clear();
    int id=player.handCard->m_leaderId;
    if(id==-1)//说明此时已经使用领袖
    {
        player.handCard->setLeader(Q_NULLPTR);
    }else
    {
        player.handCard->setLeader(player.m_card[id]);
    }

    for(int i=0; i<player.handCard->m_cardIds.size(); i++)
    {
        int id=player.handCard->m_cardIds[i];
        player.handCard->addCard(player.m_card[id]);
    }

    player.library->clear();
    for(int i=0; i<player.library->m_cardIds.size(); i++)
    {
        int id=player.library->m_cardIds[i];
        player.library->addCard(player.m_card[id]);
    }

    player.graveyard->clear();
    for(int i=0; i<player.graveyard->m_cardIds.size(); i++)
    {
        int id=player.graveyard->m_cardIds[i];
        player.graveyard->addCard(player.m_card[id]);
    }

    return in;

}


















