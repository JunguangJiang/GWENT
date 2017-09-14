#include "handcard.h"
#include "parameter.h"
#include <algorithm>
#include <QDebug>

//-----------------外部调用接口---------------------------

//手牌初始化时，需要确定这是我发的手牌还是敌方的手牌
HandCard::HandCard(int standPoint, GraphicsItem *parent) : m_standPoint(standPoint),
    GraphicsItem(HandCardLeftTopPoint[standPoint],HandCardSize, parent)
{
    m_leader=nullptr;
    m_cards.clear();
    m_isSeen=true;
    //m_hasUsedLeader=false;
    m_cardIds.clear();
    m_cards.clear();

    m_hasPassed=false;
}

HandCard::~HandCard()
{
}

void HandCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{//手牌的绘制
    showAllCards(painter);
    GraphicsItem::paint(painter, option, widget);

    if(m_hasPassed)
    {
        //brush.setStyle(Qt::SolidPattern);
        qreal x=boundingRect().x()-0.3*boundingRect().width();
        qreal y=boundingRect().y();
        qreal width=boundingRect().width()*1.6;
        qreal height=boundingRect().height();

        qreal centerX=x+0.5*width;
        qreal centerY=y+0.5*height;
        qreal radius=width*0.5;
        QRadialGradient radialGradient(centerX,centerY, radius, centerX, centerY);

        radialGradient.setColorAt(0.0,Qt::transparent);
        radialGradient.setColorAt(1.0,Qt::black);
        painter->setBrush(radialGradient);
        painter->drawRect(QRectF(x,y,width, height));

        QFont font;
        font.setPointSize(28);
        painter->setFont(font);

        QPen pen;
        pen.setColor(Qt::yellow);
        painter->setPen(pen);
        painter->drawText(boundingRect(), Qt::AlignCenter,"Passed");
        this->setZValue(10);
    }
}

void HandCard::setLeader(Card *card)
{
    if(!card)
    {
        m_leader=Q_NULLPTR;
        return;
    }
    m_leader=card;
    card->setSeen();
    card->setLeader(true);
    card->setStatus(STATUS::HAND);
    card->setMoveable(true);
}

void HandCard::addCard(Card* newCard)//向手牌中加入新的卡牌
{
    if(!newCard)
        return;

    if(!m_cards.empty())
    {
        auto iter=find(m_cards.begin(), m_cards.end(), newCard);
        if(iter!=m_cards.end())
        {
            return;
        }
    }

    if(!m_isSeen)
    {
        newCard->setUnseen();
    }
    else
    {
        newCard->setMoveable(true);
    }
    m_cards.push_back(newCard);
    newCard->setStatus(STATUS::HAND);

    update();

}

void HandCard::removeCard(Card* oldCard)//从手牌中移除卡牌
{
    if(!oldCard)
        return;

    if(!m_isSeen)
        oldCard->setSeen();

    if(oldCard->isLeader())
    {
        m_leader=Q_NULLPTR;
        oldCard->setLeader(false);
        oldCard->setStatus(STATUS::BATTLE_FIELD);
        qDebug()<<"remove leader";
        update();
        if(m_leader)
        {
            "m_leader still exists";
        }
        return;
    }

    auto iter=std::find(m_cards.begin(), m_cards.end(),oldCard);
    if(*iter)
    {
        if(iter!=m_cards.end())
        {
            (*iter)->setMoveable(false);
            m_cards.erase(iter);
        }
        update();
    }
}

void HandCard::setMoveable(bool moveable)//设置所有的手牌可动
{
    for(int i=0; i<m_cards.size(); i++)
    {
        //qDebug()<<QString::fromStdString(m_cards[i]->getName());
        //qDebug()<<QString::number(m_cards[i]->getId());
        m_cards[i]->setMoveable(moveable);
    }

    //if(!m_hasUsedLeader)//如果领袖还没有用过
    if(m_leader)
    {
        m_leader->setMoveable(moveable);
    }
}

void HandCard::setUnseen()
{
    m_isSeen=false;
}

Card* HandCard::discardByRandom()//随意丢弃一张手牌
{
    if(isEmpty())
        return nullptr;
    int i=rand()%m_cards.size();
    Card* discardedCard=*(m_cards.begin()+i);
    m_cards.erase(m_cards.begin()+i);
    update();
    return discardedCard;
}

void HandCard::showAllCards(QPainter* painter)//展示卡牌上所有的卡牌
{
    qreal left, top;

    //----显示领袖----
    if(m_leader)
    {
        left=LeaderLeftTopPoint[m_standPoint].x();
        top=LeaderLeftTopPoint[m_standPoint].y();
        m_leader->setLeftTop(left,top);
    }


    left=HandCardLeftTopPoint[m_standPoint].x();
    top=HandCardLeftTopPoint[m_standPoint].y();


    if(isEmpty())//如果手牌区为空，则返回
    {
        return;
    }
    qreal handCardHorizontalDistance=HandCardSize.width()/m_cards.size();//否则根据当前的手牌数调整手牌间距

    for(int i=0; i<m_cards.size(); i++)
    {
        m_cards[i]->setLeftTop(left, top);
        left+=handCardHorizontalDistance;
        m_cards[i]->setZValue(i);
        m_cards[i]->update();
    }

}


QDataStream &operator<<(QDataStream &out,const HandCard &handCard)
{
    if(handCard.m_leader)
    {
        out<<handCard.m_leader->getId();
    }
    else//在不存在领袖的情况下，传输的id值为-1
    {
        out<<-1;
    }

    out <<handCard.getSize();

    qDebug()<<"out handcard size"<<handCard.getSize();

    for(int i=0; i<handCard.getSize(); i++)
    {
        if(handCard.m_cards[i])
        {
            out<<(handCard.m_cards[i]->getId());
        }
    }

    return out;
}

QDataStream &operator>>(QDataStream &in , HandCard &handCard)
{
    in>>handCard.m_leaderId;

    int size;
    in>>size;

    qDebug()<<"in handcard size"<<size;

    handCard.m_cardIds.clear();

    for(int i=0; i<size; i++)
    {
        int cardId;
        in>>cardId;
        handCard.m_cardIds.push_back(cardId);
    }

    return in;
}
