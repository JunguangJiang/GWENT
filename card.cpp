#include "card.h"
#include <QCursor>
#include <QDebug>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
using namespace gwent;
class Game;
//---------------------公有的操作-------------------------------
Card::Card(const RACE race,//一般卡的初始化
     const std::string name,
     const std::string imagePath,
     const std::string description,
     const int initStrenth, const TYPE initType,
     const COMBAT_ROW initCombatRow, const bool loyalty,
     GraphicsItem *parent):
    m_race(race),
    m_name(name),
    m_imagePath(imagePath),
    m_description(description),
    m_initStrength(initStrenth),m_initType(initType),
    m_initCombatRow(initCombatRow), m_loyalty(loyalty),
    GraphicsItem(1.0,1.0,cardWidth,cardHeight,QString::fromStdString(imagePath),parent)
{
    initialize();//卡牌的初始化
    setAcceptHoverEvents(true);//卡牌接受悬浮事件
}

Card::Card(const RACE race,//特殊卡的初始化（没有战斗力和站位）
     const std::string name,
     const std::string imagePath,
     const std::string description,
     const TYPE initType,
     GraphicsItem *parent):
    m_race(race),
    m_name(name),
    m_imagePath(imagePath),
    m_description(description),
    m_initStrength(NO_STRENGTH),m_initType(initType),
    m_initCombatRow(COMBAT_ROW::NO_COMBATROW), m_loyalty(true),
    GraphicsItem(1.0,1.0,cardWidth,cardHeight,QString::fromStdString(imagePath),parent)
{
    initialize();
    setAcceptHoverEvents(true);
}

Card::Card(const Card& oldCard, GraphicsItem *parent):
    m_race(oldCard.m_race),
    m_name(oldCard.m_name),
    m_imagePath(oldCard.m_imagePath),
    m_description(oldCard.m_description),
    m_initStrength(oldCard.m_initStrength), m_initType(oldCard.m_initType),
    m_initCombatRow(oldCard.m_initCombatRow), m_loyalty(oldCard.m_loyalty),
    m_idOfDatabase(oldCard.m_idOfDatabase),
  GraphicsItem(1.0,1.0,cardWidth,cardHeight,QString::fromStdString(oldCard.m_imagePath),parent)
{
    //复制构造函数
    //note:复制构造函数的主要作用是，从卡牌数据库中取得卡牌，放到当前场景的游戏背景上，需要设置这些卡牌的父亲是游戏背景。
    initialize();
    setAcceptHoverEvents(true);
}

Card::Card(GraphicsItem *parent):
    m_race(RACE::NEUTRAL),
    m_name(""),
    m_imagePath(""),
    m_description(""),
    m_initStrength(0), m_initType(TYPE::BRONZE),
    m_initCombatRow(COMBAT_ROW::NO_COMBATROW), m_loyalty(true),
    m_idOfDatabase(0),
  GraphicsItem(1.0,1.0,cardWidth,cardHeight,QString::fromStdString(""),parent)
{
    initialize();
}

void Card::initialize()//为了使构造函数看上去更加简洁
{
    m_actualStrength=m_initStrength;
    m_actualType=m_initType;
    m_hasShield=false;
    m_armor=0;
    m_status=STATUS::DECK;
    m_isSeen=true;
    setFlag(ItemIsMovable,false);
    setFlag(ItemIsFocusable,true);

    m_strengthShow=new text(UnseenPos, CardStrengthSize,this);
    m_strengthShow->setFontSize(17);
    m_armorShow=new text(UnseenPos, CardArmorSize, this);
    m_armorShow->setFontSize(11);
    m_armorShow->setFontColor(Qt::blue);
    m_shieldShow=new text(UnseenPos, CardShieldSize,this);
    m_shieldShow->setFontSize(11);
    m_shieldShow->setFontColor(Qt::white);

    m_game=Q_NULLPTR;
    m_oursizePlayer=Q_NULLPTR;
    m_enemyPlayer=Q_NULLPTR;

    m_amountInDeck=0;
    m_showAmountInDeck=false;
    m_amountShow=new text(UnseenPos,AmountInDeckSize,this);//设置卡牌在卡组中数量显示的位置和大小,正常情况下不可见
    m_amountShow->setFontColor(Qt::red);
    m_amountShow->setFontSize(17);

    m_leaderShow=new text(UnseenPos,LeaderShowSize, this);//显示卡牌是否为领袖
    m_leaderShow->setFontColor(Qt::yellow);
    m_leaderShow->setFontSize(10);
    m_isLeader=false;

    m_showGoalLine=false;

    m_isDispatching=false;
}

void Card::setLeftTop(qreal left, qreal top)//设置卡牌的位置，left和top是卡牌左上方点的横纵坐标
{
    m_left=left;
    m_top=top;
    update();
    //this->setPos(0,0);
}

void Card::setLeftTop(QPointF pos)
{
    setLeftTop(pos.x(), pos.y());
}

void Card::setMoveable(bool moveable)
{
    if(moveable)
    {
        this->setFlag(ItemIsMovable,true);
     }
    else
    {
        this->setFlag(ItemIsMovable, false); ;//设置不可移动，这样可以吗？？？
        //this->setEnabled(false);//这句的作用存疑
    }
}

void Card::setUnseen()
{
    m_isSeen=false;
    this->changeImagePath(UnknownCardImagePath);
    this->resize(UnknownCardImageSize);
}

void Card::setSeen()
{
    qDebug()<<"setSeen";
    m_isSeen=true;
    this->changeImagePath(QString::fromStdString(m_imagePath));
    this->resize(CardSize);
}

void Card::setStatus(const STATUS status)//改变卡牌的状态
{
    m_status=status;
    if(status==STATUS::DECK)
    {
        emit addToLibrary();
    }
}

Card* Card::getWeakerCard(Card *card1, Card *card2)//优先返回前面那张卡,不会返回金卡
{
    if(card1 && card2)
    {
        if(!card1->isGoldenCard() && !card2->isGoldenCard())
        {
            if(card1->getActualStrength() <= card2->getActualStrength())
            {
                return card1;
            }else
            {
                return card2;
            }
        }else if(!card1->isGoldenCard())
        {
            return card1;
        }else if(!card2->isGoldenCard())
        {
            return card2;
        }else
        {
            return Q_NULLPTR;
        }
    }else if(card1 && !card1->isGoldenCard())
    {
        return card1;
    }else if(card2 && !card2->isGoldenCard())
    {
        return card2;
    }
    return Q_NULLPTR;
}

Card* Card::getStrongerCard(Card *card1, Card *card2)//优先返回前面那张卡，不会返回金卡
{
    if(card1 && card2)
    {
        if(!card1->isGoldenCard() && !card2->isGoldenCard())
        {
            if(card1->getActualStrength() >= card2->getActualStrength())
            {
                return card1;
            }else
            {
                return card2;
            }
        }else if(!card1->isGoldenCard())
        {
            return card1;
        }else if(!card2->isGoldenCard())
        {
            return card2;
        }else
        {
            return Q_NULLPTR;
        }
    }else if(card1 && !card1->isGoldenCard())
    {
        return card1;
    }else if(card2 && !card2->isGoldenCard())
    {
        return card2;
    }
    return Q_NULLPTR;
}

//----------------------卡牌特殊技能实现的接口----------------------------

void Card::getShield()//获得护盾
{
    m_hasShield=true;
    update();
}

void Card::loseShield()//使用一次护盾后即失去
{
    m_hasShield=false;
    update();
}

void Card::getHarm(const int harm)//获得伤害
{
    if(this->isGoldenCard())//金卡不接受伤害
    {
        return;
    }

    if(m_hasShield)
    {
        loseShield();
        return;
    }

    if(harm>=m_armor)
    {
        m_armor=0;
        m_actualStrength -= (harm-m_armor);
    }else
    {
        m_armor-=harm;
    }

    if(isDead())//如果死亡，则从战场进入墓地
    {
        this->battleFieldToGraveyard();
    }
    update();
}

void Card::getGain(const int gain)//获得增益
{
    m_actualStrength += gain;
    update();
}

void Card::getArmor(const int armor)//获得护甲
{
    m_armor+=armor;
    update();
}

void Card::setStrength(const int strength)//改变战力
{
    if(isGoldenCard())
        return;//金卡不接受效果
    m_actualStrength=strength;
    update();
}

void Card::backToOriginState()
{
    m_actualStrength=m_initStrength;
    m_armor=0;
    m_hasShield=false;
}


//-----------------------卡牌与用户交互时的直接操作-----------------------

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)//鼠标点击卡牌
{
    setCursor(Qt::ClosedHandCursor);
    emit cardPressed(this);//发送卡牌被点击的信号
}


void Card::hoverEnterEvent(QGraphicsSceneHoverEvent *event)//鼠标悬停在卡牌时
{
    if(m_isSeen)//只有在该卡牌可见时
        emit cardHover(this);//发送信号，显示该卡牌的各种信息
}


QDataStream &operator<<(QDataStream &out, const Card &card)
{
    out<<card.m_actualStrength;
    out<<static_cast<int>(card.m_actualType) ;
    out<<static_cast<int>(card.m_actualCombatRow);
    out<<card.m_hasShield;
    out<<card.m_armor;
    out<<static_cast<int>(card.m_status);

    out<<card.m_idOfDatabase;
    out<<card.m_id;
    return out;
}

QDataStream &operator>>(QDataStream &in , Card &card)
{
    in>>card.m_actualStrength;

    int type;
    in>>type;
    card.m_actualType=static_cast<TYPE>(type);

    int combatRow;
    in>>combatRow;
    card.m_actualCombatRow=static_cast<COMBAT_ROW>(combatRow);

    in>>card.m_hasShield;
    in>>card.m_armor;

    int status;
    in>>status;
    card.m_status=static_cast<STATUS>(status);

    in>>card.m_idOfDatabase;
    in>>card.m_id;
    return in;
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItem::paint(painter, option, widget);

    //----------------------以下用于游戏界面------------------------------------

    if(m_strengthShow && m_armorShow && m_shieldShow && m_status==STATUS::BATTLE_FIELD)
    {
        //显示当前的战斗力
        if(m_actualStrength==m_initStrength)
        {
            m_strengthShow->setText("");
            m_strengthShow->update();
        }
        else
        {
            if(m_actualStrength<m_initStrength)
            {
                m_strengthShow->setFontColor(Qt::red);
            }
            else
            {
                m_strengthShow->setFontColor(Qt::green);
            }
            m_strengthShow->setText(std::to_string(m_actualStrength));
            m_strengthShow->setLeftTop(this->m_left+CardStrengthOffsetX, this->m_top+CardStrengthOffsetY);
            m_strengthShow->update();
        }

        //显示是否有护甲
        if(m_armor>0)
        {
            m_armorShow->setText("Armor "+std::to_string(m_armor));
            m_armorShow->setLeftTop(this->m_left+CardArmorOffsetX, this->m_top+CardArmorOffsetY);
            m_armorShow->update();
        }else
        {
            m_armorShow->setText("");
            m_armorShow->update();
        }

        //显示是否有护盾
        if(m_hasShield)
        {
            m_shieldShow->setText("Shield");
            m_shieldShow->setLeftTop(this->m_left+CardShieldOffsetX, this->m_top+CardShieldOffsetY);
            m_shieldShow->update();
        }else
        {
            m_shieldShow->setText("");
            m_shieldShow->update();
        }
    }

    //----------------------以下用于修改卡组界面---------------------------------
    if(m_showAmountInDeck)//是否显示在卡组中的数量
    {
        m_amountShow->setText(std::to_string(m_amountInDeck));
        m_amountShow->setLeftTop(this->m_left+AmountInDeckOffsetX, this->m_top+AmountInDeckOffsetY);
        m_amountShow->update();
    }else
    {
        m_amountShow->setText("");
    }

    if(isLeader()&&m_showAmountInDeck)//标识卡组的领袖
    {
        m_leaderShow->setText("Leader");
        m_leaderShow->setLeftTop(this->m_left+LeaderShowOffsetX, this->m_top+LeaderShowOffsetY);
        m_leaderShow->update();
    }else
    {
        m_leaderShow->setText("");
    }
    //---------------------------------------------------------------------------

    if(m_showGoalLine)
    {
        QPen pen;
        pen.setColor(Qt::blue);
        pen.setWidth(15);
        pen.setStyle(Qt::DotLine);
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pen);
        qreal x=boundingRect().x()+50;
        qreal y=boundingRect().y()+50;
        QPointF cursorPos=this->scene()->views().at(0)->mapFromGlobal(cursor().pos());
        QPointF cardPos=QPointF(x,y);
        painter->drawLine(cursorPos, cardPos);
        this->setZValue(10);
        this->parentItem()->update();
    }
}


