#include <algorithm>
#include "battle.h"
#include <QRgb>
#include "parameter.h"
#include <QDebug>

using namespace gwent;

//--------------------------外部调用接口----------------------------------

BattleField::BattleField(const COMBAT_ROW type, GraphicsItem *parent):
    GraphicsItem(BattleFieldLeftTopPoint[static_cast<int>(type)],
    BattleFieldSize, parent),
    m_type(type)
{
    this->setFlag(ItemIsFocusable, true);
    m_climate=CLIMATE::SUNNY;//初始时天气为晴空
    m_showBorder=false;//不显示边界

    m_currentCard.clear();
    m_transformData.clear();

    //设置战排战力显示
    m_totalStrength=new text(BattleStrengthShowPos[static_cast<int>(type)], BattleStrengthShowSize,this);
    m_totalStrength->setFontSize(18);
    m_totalStrength->setCenter();
    switch (type) {
    case COMBAT_ROW::ENEMY_CLOSE:
    case COMBAT_ROW::ENEMY_REMOTE:
    case COMBAT_ROW::ENEMY_SIEGE:
        m_totalStrength->setBackgroundColor(Qt::darkRed);
        break;
    default:
        m_totalStrength->setBackgroundColor(Qt::darkBlue);
        break;
    }
    m_frostHarm=2;
}

BattleField::~BattleField()
{
}

CLIMATE BattleField::getClimate()//得到当前排的天气
{
    return m_climate;
}

int BattleField::getTotalStrength()               //返回战排的总分
{
    int totalStrength=0;
    for(size_t i=0; i<m_currentCard.size(); i++)
    {
        totalStrength+=m_currentCard.at(i)->getActualStrength();
    }
    return totalStrength;
}

bool BattleField::checkTypeOf(Card *newCard)//检查新卡牌的站位属性，如果与当前战排相符，则返回true
{
    switch (newCard->getInitCombatRow()) {
    case COMBAT_ROW::ANY://假如新卡牌为站位任意牌
    case COMBAT_ROW::LEADER:
        if((m_type==COMBAT_ROW::CLOSE)||//则放在我方场上任意位置皆可
                (m_type==COMBAT_ROW::REMOTE)||
                (m_type==COMBAT_ROW::SIEGE))
        {
            return true;
        }else{
            return false;
        }
    case COMBAT_ROW::CLOSE://如果是近战卡、
    case COMBAT_ROW::REMOTE://远程卡、
    case COMBAT_ROW::SIEGE://攻城卡，
        return ((m_type) == (newCard->getInitCombatRow()) );//都必须放在我方场上对应位置
    default:
        return false;
    }
}

Card *BattleField::getLeftCard(Card *card)
{
    if(!card)
    {
        return Q_NULLPTR;
    }
    if(m_currentCard.size()<=1)
    {
        return Q_NULLPTR;
    }

    auto iter=find(m_currentCard.begin(), m_currentCard.end(), card);
    if(iter!=m_currentCard.end())
    {
        iter--;
        if(*iter)
        {
            return *iter;
        }
    }
    return Q_NULLPTR;
}

Card *BattleField::getRightCard(Card *card)
{
    if(!card)
    {
        return Q_NULLPTR;
    }
    if(m_currentCard.size()<=1)
    {
        return Q_NULLPTR;
    }
    auto iter=find(m_currentCard.begin(), m_currentCard.end(), card);
    if(iter!=m_currentCard.end())
    {
        iter++;//指向找到的卡牌的右边
        if(*iter)
        {
            return *iter;
        }
    }
    return Q_NULLPTR;
}


void BattleField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//战排的绘画
{
    GraphicsItem::paint(painter,option,widget);

    m_totalStrength->setText(std::to_string(getTotalStrength()));
    m_totalStrength->update();
    emit updateBattleStrengthShow();//不管战排有没有改变战斗力，都会发送这个信号，去更新玩家的总战斗力显示

    if(m_showBorder)
        showBorder(painter);//确定此时是否需要绘制边框
    showAllCards();//显示战排上的所有卡牌
    showWeather(painter);//显示战排的天气
}

Card *BattleField::getWeakestCard()const//优先返回每一排靠左的卡
{
    if(m_currentCard.empty())
        return Q_NULLPTR;

    if(m_currentCard.size()==1)
    {
        if(!m_currentCard[0]->isGoldenCard())
        {
            return m_currentCard[0];
        }else
        {
            return Q_NULLPTR;
        }
    }

    Card *weakestCard=m_currentCard[0];
    for(int i=1; i<m_currentCard.size(); i++)
    {
        Card *nextCard=m_currentCard[i];
        weakestCard=Card::getWeakerCard(weakestCard, nextCard);
    }
    return weakestCard;
}


Card *BattleField::getStrongestCard()const//优先返回每一排靠左的卡
{
    if(m_currentCard.empty())
        return Q_NULLPTR;

    if(m_currentCard.size()==1)
    {
        if(!m_currentCard[0]->isGoldenCard())
        {
            return m_currentCard[0];
        }else
        {
            return Q_NULLPTR;
        }
    }

    Card *strongestCard=m_currentCard[0];
    for(int i=1; i<m_currentCard.size(); i++)
    {
        Card *nextCard=m_currentCard[i];
        strongestCard=Card::getStrongerCard(strongestCard, nextCard);
    }
    return strongestCard;
}


//---------------------在paint中调用的内部函数------------------------------

void BattleField::showAllCards()//展示卡牌上所有的卡牌
{
    qreal left=BattleFieldLeftTopPoint[static_cast<int>(m_type)].x();//首先求得当前战排的左上端点值
    qreal top=BattleFieldLeftTopPoint[static_cast<int>(m_type)].y();
    for(auto& i: m_currentCard)//遍历战排中的所有卡牌
    {
        i->setLeftTop(left,top);//设置其当前的位置
        left+=cardHorizontalDistance;//两张卡牌直接间隔一定距离
        i->update();
    }
}

void BattleField::showBorder(QPainter *painter)//展示当前战排的边界
{
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::blue);
    painter->setPen(pen);
    painter->drawRect(boundingRect());//则用蓝笔突出显示当前的战排，之后可以加粗蓝笔
}

void BattleField::showWeather(QPainter *painter)    //展现不同的天气效果,该函数未完成，后期加动画
{
    painter->setPen(Qt::NoPen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    qreal centerX=boundingRect().x()+0.5*boundingRect().width();
    qreal centerY=boundingRect().y()+0.5*boundingRect().height();
    qreal radius=boundingRect().width()*0.5;
    QRadialGradient radialGradient(centerX,centerY, radius, centerX, centerY);
    switch (m_climate) {
    case CLIMATE::SUNNY:
        //do nothing
        break;
    case CLIMATE::FOG:
        radialGradient.setColorAt(0.0,Qt::transparent);
        radialGradient.setColorAt(1.0,Qt::darkGray);
        painter->setBrush(radialGradient);
        painter->drawRect(boundingRect());
        break;
    case CLIMATE::FROST:
        radialGradient.setColorAt(0.0,Qt::transparent);
        radialGradient.setColorAt(1.0,QColor(255,250,250));
        painter->setBrush(radialGradient);
        painter->drawRect(boundingRect());
        break;
    case CLIMATE::RAIN:
        radialGradient.setColorAt(0.0,Qt::transparent);
        radialGradient.setColorAt(1.0,QColor(135, 206, 235));
        painter->setBrush(radialGradient);
        painter->drawRect(boundingRect());
        break;
    default:
        break;
    }
}

//--------------------战排的信号响应接口------------------------------------

bool BattleField::changeClimate(CLIMATE climate)//改变排的天气
{
    m_climate=climate;
    emit changeClimate(climate, this);
    update();
    return true;
}

bool BattleField::addCard(Card *newCard)//向战排中加入新的卡牌
{
    if(newCard){
        auto iter=find(m_currentCard.begin(), m_currentCard.end(), newCard);
        if(iter!=m_currentCard.end())
            return false;
        newCard->setSeen();
        newCard->setActualCombatRow(this->m_type);
        newCard->setStatus(STATUS::BATTLE_FIELD);
        m_currentCard.push_back(newCard);
        update();
        return true;
    }
    else
        return false;
}

bool BattleField::removeCard(Card *oldCard)//从战排中删除卡牌
{
    if(!oldCard)
        return false;

    auto iter=find(m_currentCard.begin(), m_currentCard.end(), oldCard);
    if(iter!=m_currentCard.end()){
        m_currentCard.erase(iter);
        update();
        return true;
    }else
    {
        return false;
    }

}

void BattleField::insert(Card *oldCard, Card *newCard)
{
    if(!oldCard || !newCard)
        return;

    auto iter=find(m_currentCard.begin(), m_currentCard.end(), newCard);
    if(iter!=m_currentCard.end())
        return;

    iter=find(m_currentCard.begin(), m_currentCard.end(), oldCard);//找到oldcard的位置
    m_currentCard.insert(iter, newCard);//在这之前插入newcard

    newCard->setSeen();
    newCard->setActualCombatRow(this->m_type);
    newCard->setStatus(STATUS::BATTLE_FIELD);
}

void BattleField::clearAll()//清空所有卡牌，同时清除天气效果
{
    for(auto &i : m_currentCard)
    {
        i->battleFieldToGraveyard();//将所有卡牌放入墓地
    }
    this->changeClimate(CLIMATE::SUNNY);//同时清除天气效果
}

void BattleField::mouseDoubleClickEvent(QGraphicsSceneEvent *event)
{
    emit battleFeildPressed(this);
}

void BattleField::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit battleFeildPressed(this);
}

void BattleField::getDemagedByWeather()
{
    Card *weakestCard=getWeakestCard();
    Card *strongestCard=getStrongestCard();
    switch (m_climate) {
    case CLIMATE::SUNNY:
        return;
    case CLIMATE::FROST:
        if(weakestCard)
        {
            weakestCard->getHarm(m_frostHarm);
        }
        break;
    case CLIMATE::FOG:
        if(strongestCard)
        {
            strongestCard->getHarm(2);
        }
        break;
    case CLIMATE::RAIN:
        if(weakestCard)
        {
            int weakestStrength=weakestCard->getActualStrength();
            int count=0;
            for(int i=0; i<m_currentCard.size(); i++)
            {
                if(m_currentCard[i]->getActualStrength()==weakestStrength)
                {
                    m_currentCard[i]->getHarm(1);
                    count++;
                }
                if(count==5)//最多伤害5只
                    break;
            }
        }
        break;
    }
    update();
}

QDataStream &operator<<(QDataStream &out, const BattleField &battleField)
{
    out << static_cast<int>(battleField.m_climate) ;

    out <<battleField.getSize();

    for(int i=0; i<battleField.getSize(); i++)
    {
        if(battleField.getNthCard(i))
        {
            out<<(battleField.getNthCard(i)->getId())<<battleField.getNthCard(i)->getLoyalty();
        }
    }

    return out;
}

QDataStream &operator>>(QDataStream &in,  BattleField &battleField)
{
    int climate;
    in >> climate;
    battleField.m_climate=static_cast<CLIMATE>(climate);

    int size;
    in>>size;

    battleField.m_transformData.clear();

    for(int i=0; i<size; i++)
    {
        int cardId;
        in>>cardId;
        bool loyalty;
        in>>loyalty;
        struct TransformData data={cardId, loyalty};
        battleField.m_transformData.push_back(data);
    }

    return in;
}


















