#include "game.h"
#include "deck.h"
#include <QTimer>
#include "parameter.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QMutex>
Game::Game(long long gameId,  int userId0, int userId1,  QObject *parent) :
    QObject(parent), m_gameId(gameId)
{ 
    m_userId[0]=userId0;
    m_userId[1]=userId1;

    m_player[0]=Q_NULLPTR;
    m_player[1]=Q_NULLPTR;

    m_gameStatus=GameStatus::UNSTARTED;//初始时，游戏未开始
    for(int i=0; i<3; i++)
    {
      m_gameRoundStatus[i]=GameStatus::UNSTARTED;
    }
    winningTimes[ENEMY]=0;//两个玩家都没有赢过
    winningTimes[OURSIDE]=0;

    m_background=Q_NULLPTR;
    m_bigCardImage=Q_NULLPTR;
    m_cardName=Q_NULLPTR;
    m_cardDescription=Q_NULLPTR;
    m_passButton=Q_NULLPTR;
    m_leftTimeShow=Q_NULLPTR;
    m_turnShow=Q_NULLPTR;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    srand(time(NULL));//根据时间生成随机数种子,存疑


    m_isDispatching=false;
}

Game::~Game()
{

}

void Game::playGameIn(int userId, GraphicsItem* background)//调用game的dialog的用户账号是userId，需要将game映射到background上
{
    //根据userId，来判断敌我方
    if(m_userId[0]==userId)
    {
        m_player[OURSIDE]=new Player(m_userId[0], this);
        m_player[ENEMY]=new Player(m_userId[1],this);
        m_enemyId=m_userId[1];
    }else if(m_userId[1]==userId)
    {
        m_player[OURSIDE]=new Player(m_userId[1], this);
        m_player[ENEMY]=new Player(m_userId[0],this);
        m_enemyId=m_userId[0];
    }else
    {
        return;
    }

    m_userIdOfDialog=userId;
    m_background=background;

    //玩家选择游戏背景
    m_player[OURSIDE]->chooseBackgroud(background,OURSIDE);
    m_player[ENEMY]->chooseBackgroud(background,ENEMY);

    //布置游戏背景上的
    //卡牌大图
    m_bigCardImage=new GraphicsItem(BigCardImagePos,BigCardImageSize, background);

    //卡牌名字
    m_cardName=new text(CardNamePos, CardNameSize, 16, Qt::black, QColor(122,122,0,100), background);
    m_cardName->setCenter();

    //卡牌描述
    m_cardDescription=new text(CardDescriptionPos, CardDescriptionSize,14, Qt::black, Qt::lightGray, background);
    m_cardDescription->setLeft();

    //放弃按钮
    m_passButton=new Button(PassButtonPos, PassButtonSize, PassButtonImagePath,background);
    connect(m_passButton,SIGNAL(buttonPressed()),this,SLOT(on_buttonPressed()));

    //剩余时间显示
    m_leftTimeShow=new text(LeftTimeShowPos, LeftTimeShowSize, background);
    m_leftTimeShow->setFontColor(Qt::yellow);
    m_leftTimeShow->setFontSize(23);
    m_leftTimeShow->setCenter();
    m_leftTimeShow->setText("");
    connect(m_player[OURSIDE]->getTimer(), SIGNAL(timeout()), this, SLOT(on_oneSecondGone()));

    //当前发牌玩家显示
    m_turnShow=new text(TurnShowPos, TurnShowSize, background);
    m_turnShow->setFontColor(Qt::white);
    m_turnShow->setFontSize(19);
    m_turnShow->setText("UNSTARTED");
    m_turnShow->setCenter();

    //上一轮结果的显示
    m_gameRoundResultShow=new text(GameRoundResultShowPos, GameRoundResultShowSize, background);
    m_gameRoundResultShow->setBackgroundColor(Qt::white);
    m_gameRoundResultShow->setFontSize(28);
    m_gameRoundResultShow->setCenter();

    //当前是第几局
    m_gameRoundShow=new text(GameRoundShowPos, GameRoundShowSize, background);
    m_gameRoundShow->setFontSize(22);
    m_gameRoundShow->setFontColor(Qt::yellow);

}

void Game::setDeckId(int deckId1, int deckId2)//传入两个玩家选择的卡组编号
{
    m_deckId[0]=deckId1;
    m_deckId[1]=deckId2;

    //玩家选择牌组，该过程同时将牌组里的牌初始化到卡库汇总
    if(m_userId[0]==m_userIdOfDialog)
    {
        m_player[OURSIDE]->chooseDeck(m_deckId[0]);
        m_player[ENEMY]->chooseDeck(m_deckId[1]);
    }else if(m_userId[1]==m_userIdOfDialog)
    {
        m_player[OURSIDE]->chooseDeck(m_deckId[1]);
        m_player[ENEMY]->chooseDeck(m_deckId[0]);
    }else
    {
        return;
    }

    //连接玩家发牌结束的信号
    connect(m_player[OURSIDE], SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));
    connect(m_player[ENEMY], SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));

    //连接玩家卡库里的所有牌和游戏背景的交互（比如显示卡牌信息）
    connectCardHoverEvents();
}

void Game::setDeck(Deck* enemyDeck, Deck* ourDeck)
{
    m_player[OURSIDE]->setDeck(ourDeck);
    m_player[ENEMY]->setDeck(enemyDeck);

    //连接玩家发牌结束的信号
    connect(m_player[OURSIDE], SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));
    connect(m_player[ENEMY], SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));

    //连接玩家卡库里的所有牌和游戏背景的交互（比如显示卡牌信息）
    connectCardHoverEvents();

}

void Game::connectCardHoverEvents()
{
    for(int i=0; i<m_player[0]->library->getSize(); i++)
    {
        connect(m_player[0]->library->getNthCard(i), SIGNAL(cardHover(Card*)), this, SLOT(on_cardHover(Card*)));
    }
    for(int i=0; i<m_player[1]->library->getSize(); i++)
    {
        connect(m_player[1]->library->getNthCard(i),SIGNAL(cardHover(Card*)), this, SLOT(on_cardHover(Card*)));
    }
}

void Game::saveGame(const QString gameFile)
{
    QMutex mutex;
    mutex.lock();

    //QFile file(QDir::currentPath()+QString("/")+gameFile);
    //QFile file("/Users/jiangjunguang/Library/Mobile Documents/com~apple~CloudDocs/CodeProject/QT/GWENT_WHOLE/GwentClient/GWENT/Game1.dat");

    QFile file(GameFilePrefix);

    //QFile file(QDir::currentPath()+QString("/Game")+QString::number(m_gameId)+QString(".dat"));
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"error writing";
    }
    QDataStream out(&file);
    out << *(this);
    file.close();

    mutex.unlock();
}

void Game::updateGame(const QString gameFile)
{
    QMutex mutex;
    mutex.lock();

    QFile file(GameFilePrefix);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"error reading";
        return;
    }

    QDataStream in(&file);
    in>>(*this);

    file.close();
    mutex.unlock();
}

void Game::saveGame()
{
    qDebug()<<"save game";
}


void Game::on_cardPressed(Card *card)//对卡牌点击事件作出响应
{

}

void Game::on_cardHover(Card *card)//对卡牌上方有鼠标悬浮事件作出响应
{
    if(card->isSeen())
    {
        m_bigCardImage->changeImagePath(QString::fromStdString(card->getImagePath()));
        m_cardName->setText(card->getName());
        m_cardDescription->setText(card->getDescription());
        m_bigCardImage->update();
        m_cardName->update();
        m_cardDescription->update();
    }
}

void Game::on_battleFieldPressed(COMBAT_ROW combatRow)//对战排点击事件作出响应
{

}


void Game::on_buttonPressed()//当pass按钮按下时
{
    if(m_isDispatching)
    {
        endDispatchingCard();
    }
    else
    {
        if(m_player[OURSIDE]->isOnTurn())//只有我方轮到出牌时，才能按pass按钮
        {
            qDebug()<<"We choose pass";

            m_player[OURSIDE]->choosePassed();
            m_player[OURSIDE]->loseTurn();
        }
    }

}

void Game::on_oneSecondGone()//当1s中过去时
{
    //更新时间显示
    updateTime();
}

void Game::startGame()//玩家开始玩游戏
{
    m_player[OURSIDE]->shuffleCards();
    m_player[OURSIDE]->drawInitCards();
    enterDispatchingCard();
    /*
    updateRound();

    if(m_userId[0]==m_userIdOfDialog)
    {
        m_currentRound=0;//第一回合是0
        m_gameRoundStatus[m_currentRound]=GameStatus::PLAYING;

        //---洗牌
       for(int i=0; i<2; i++)
        {
            m_player[i]->shuffleCards();//洗牌
            m_player[i]->drawInitCards();//抽牌
        }

       enterDispatchingCard();

        //decideOrderOfCards();//等概率决定先后手

        saveGame(GameFileName);
    }else if(m_userId[1]==m_userIdOfDialog)
    {
        updateGame(GameFileName);

        m_player[m_currentPlayingUserNumber]->getTurn();

        updateTime();
    }*/
}


void Game::enterDispatchingCard()//进入调度
{
    for(int i=1; i<m_player[OURSIDE]->getSize(); i++)//领袖不需要调度
    {
        m_player[OURSIDE]->getNthCard(i)->setIsDispatching(true);//每张卡都属于调度期
        connect(m_player[OURSIDE]->getNthCard(i), SIGNAL(cardDispatched(Card*)), m_player[OURSIDE], SLOT(dispatchCard(Card*)));
    }
    connect(m_player[OURSIDE], SIGNAL(endDispatchingCard()), this, SLOT(endDispatchingCard()));
    m_player[OURSIDE]->setIsDispatchingCard(true);
    m_isDispatching=true;
}

void Game::endDispatchingCard()
{
    for(int i=1; i<m_player[OURSIDE]->getSize(); i++)//领袖不需要调用
    {
        m_player[OURSIDE]->getNthCard(i)->setIsDispatching(false);//每张卡都结束调度期
        disconnect(m_player[OURSIDE]->getNthCard(i), SIGNAL(cardDispatched(Card*)), m_player[OURSIDE], SLOT(dispatchCard(Card*)));
    }
    disconnect(m_player[OURSIDE], SIGNAL(endDispatchingCard()), this, SLOT(endDispatchingCard()));
    m_player[OURSIDE]->setIsDispatchingCard(false);
    m_isDispatching=false;

    //结束调度时进入第一局游戏
    m_currentRound=0;

    if(m_userIdOfDialog==m_userId[1])//由第二个玩家的game来决定发牌顺序
    {
        decideOrderOfCards();
        qDebug()<<"decide order";
        m_gameRoundStatus[m_currentRound]=GameStatus::PLAYING;
    }
    else
    {
        emit uploadGamePackage();
        qDebug()<<"upload game package";
        m_gameRoundStatus[m_currentRound]=GameStatus::UNSTARTED;
    }
}

void Game::decideOrderOfCards()//随机决定发牌顺序
{
    int rand=qrand()%2;

    if(rand==OURSIDE)
    {
        qDebug()<<"We first";
        m_player[OURSIDE]->getTurn();
        updateTime();

    }else if(rand==ENEMY)
    {
        qDebug()<<"Enemy first";
        emit uploadGamePackage();
    }else
    {
        qDebug()<<"Error";
    }
}

void Game::on_playerLoseTurn()//当当前选手结束发牌时
{
    //如果还不能判断游戏胜负
    bool roundOver=judgeOfGameRound();
    if(!roundOver)
    {
        //则轮到另外一方发牌
        emit uploadGamePackage();
    }
    else//假如当前局结束
    {
        showGameRoundResult();//显示上一局的结果
        bool gameOver=judgeOfGame();//判断整场游戏是否结束
        if(!gameOver)//没有结束，
        {
            enterANewRound();//则进入新的一回合
        }
        else//结束的话
        {
            emit uploadGamePackage();
            stopGame();//结束游戏
        }
    }

}

void Game::enterANewRound()//进入新的一回合
{
    m_player[OURSIDE]->enterANewRound();
    m_currentRound++;

    qDebug()<<"enter round:"<<QString::number(m_currentRound);

    if(m_lastWinner==OURSIDE)//上一局赢的玩家先开始发牌
    {
        m_player[OURSIDE]->getTurn();
    }
    else
    {
        emit uploadGamePackage();
    }
    //m_player[m_lastWinner]->getTurn();
}

bool Game::judgeOfGameRound()//判断当前局是否分出胜负，已分出胜负则返回true
{
    if(m_player[0]->getHasChosenPassed() &&
            m_player[1]->getHasChosenPassed())//如果两方都已pass
    {
        if((m_player[0]->getTotalStrength()) > (m_player[1]->getTotalStrength()))
        {
            m_gameRoundStatus[m_currentRound]=GameStatus::PLAYER_0_WIN;
            winningTimes[0]+=1;
            m_lastWinner=0;
            qDebug()<<"You lose";
        }
        else if((m_player[0]->getTotalStrength()) < (m_player[1]->getTotalStrength()))
        {
            m_gameRoundStatus[m_currentRound]=GameStatus::PLAYER_1_WIN;
            winningTimes[1]+=1;
            m_lastWinner=1;
            qDebug()<<"You win";
        }
        else
        {
            m_gameRoundStatus[m_currentRound]=GameStatus::END_IN_DRAW;
            winningTimes[0]+=1;
            winningTimes[1]+=1;
            m_lastWinner=rand()%2;//平局情况下随机生成一个上一局赢的玩家，以确定下一局开始的次序
            qDebug()<<"In draw";
        }
        return true;
    }
    else//否则当前局继续
    {
        m_gameRoundStatus[m_currentRound]=GameStatus::PLAYING;
        return false;
    }
}

bool Game::judgeOfGame()//判断整场游戏是否分出胜负,分出返回true
{
    if(winningTimes[0]==2)
    {
        if(winningTimes[1]<2)
        {
            m_gameStatus=GameStatus::PLAYER_0_WIN;
        }
        else
        {
            m_gameStatus=GameStatus::END_IN_DRAW;
        }
        return true;
    }
    else if(winningTimes[1]==2)
    {
        m_gameStatus=GameStatus::PLAYER_1_WIN;
        return true;
    }
    else
    {
        m_gameStatus=GameStatus::PLAYING;
        return false;
    }
}
/*
void Game::continueGame()//弃用
{
    updateGame(GameFileName);

    m_player[m_currentPlayingUserNumber]->getTurn();

    updateTime();
}*/

void Game::stopGame()//停止游戏
{
    qDebug()<<"stop game";
    //显示游戏结果的画面
    exit(0);
}

void Game::updateTime()
{
    //qDebug()<<"currentPlayingNumber:"<<QString::number(m_currentPlayingUserNumber);

    if(m_isDispatching)
    {
        m_turnShow->setText("Dispatching");
        m_leftTimeShow->setText(std::to_string(m_player[OURSIDE]->getLeftTime()));
        //qDebug()<<"Dispatching";
    }
    else
    {
        if(m_player[OURSIDE]->isOnTurn())
        {
            m_turnShow->setText("YOUR TURN");
            m_leftTimeShow->setText(std::to_string(m_player[OURSIDE]->getLeftTime()));
            //qDebug()<<"Your turn";
        }else
        {
            m_turnShow->setText("OPPONENT TURN");
            m_leftTimeShow->setText("");
            //qDebug()<<"openent turn";
        }
    }
    this->m_turnShow->update();

    this->m_leftTimeShow->update();

}

void Game::updateRound()
{
    m_gameRoundShow->setText("Round:"+std::to_string(this->m_currentRound+1));
}

void Game::showGameRoundResult()
{
    //显示上一局的结果
}

QDataStream &operator<<(QDataStream &out, const Game &game)
{
    //out << game.m_gameId;

    out << game.m_enemyId;//向对方发一个包，包的开头是对方的id

    out << *(game.m_player[OURSIDE]) << *(game.m_player[ENEMY]);

    out << game.m_currentRound;//发送当前回合

    for(int i=0; i<3; i++)
    {
        out<<static_cast<int>(game.m_gameRoundStatus[i]);//目前三局的游戏状态
    }
    out<<static_cast<int>(game.m_gameStatus);

    return out;

}

QDataStream &operator>>(QDataStream &in, Game &game)
{
    int destination;
    in >> destination;

    if(game.m_userIdOfDialog==destination)//如果我方就是该包的目标
    {

        if(!game.m_player[ENEMY] || !game.m_player[OURSIDE])
        {
            qDebug()<<"error game player null";
            return in;
        }

        in >> *(game.m_player[ENEMY]) >> *(game.m_player[OURSIDE]);

        in >> game.m_currentRound;

        for(int i=0; i<3; i++)
        {
            int gameRoundStatus;
            in>>gameRoundStatus;
            game.m_gameRoundStatus[i]=static_cast<GameStatus>(gameRoundStatus);
        }
        int gameStatus;
        in>>gameStatus;
        game.m_gameStatus=static_cast<GameStatus>(gameStatus);

        if(game.m_currentRound==0 && game.m_gameRoundStatus[game.m_currentRound]==GameStatus::UNSTARTED)//如果游戏还没有开始
        {
            game.startGame();//那么我方开始游戏
        }
        else
        {
            game.m_player[OURSIDE]->getTurn();//否则轮到我方出牌
        }
        return in;
    }//否则丢弃该包
    else
    {
        return in;
    }
}














