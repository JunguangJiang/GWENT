#include "graveyard.h"
#include <QDebug>

Graveyard::Graveyard(int standPoint, GraphicsItem *background):
    GraphicsItem(GraveyardPos[standPoint], GraveyardSize, background),
  m_standPoint(standPoint)
{

    m_sizeShow=new text(GraveyardShowPos[standPoint], GraveyardShowSize, background);
    m_sizeShow->setFontSize(16);
    m_sizeShow->setBackgroundColor(Qt::black);
    m_sizeShow->setFontColor(Qt::gray);
    //m_cardIds.clear();
    m_transformData.clear();
    m_cards.clear();
}

Graveyard::~Graveyard()
{
}

void Graveyard::addCard(Card *card)
{
    if(!card)
        return;

    auto iter=find(m_cards.begin(), m_cards.end(), card);
    if(iter!=m_cards.end())
        return;

    //回到墓地后，战斗力、护甲等回到初始状态
    card->backToOriginState();
    card->setStatus(STATUS::GRAVEYARD);

    m_cards.push_back(card);
    this->update();
}

void Graveyard::removeCard(Card *card)
{
    if(!card)
        return;

    auto iter=find(m_cards.begin(), m_cards.end(), card);
    if(*iter)
    {
        if(iter!=m_cards.end())
        {
            m_cards.erase(iter);
        }
    }
}

void Graveyard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItem::paint(painter,option,widget);

    for(int i=0; i<m_cards.size(); i++)
    {
        if(m_cards[i])
        {
            m_cards[i]->setLeftTop(1,1);
        }
    }
    if(m_sizeShow)
    {
        m_sizeShow->setText(std::to_string(m_cards.size()));
        m_sizeShow->update();
    }
}

QDataStream &operator<<(QDataStream &out,const Graveyard &graveyard)
{

    out <<graveyard.getSize();

    qDebug()<<"out gravayard size"<<graveyard.getSize();

    for(int i=0; i<graveyard.getSize(); i++)
    {
        if(graveyard.m_cards[i])
        {
            out<<(graveyard.m_cards[i]->getId()) << graveyard.m_cards[i]->getLoyalty();
        }
    }

    return out;
}

QDataStream &operator>>(QDataStream &in , Graveyard &graveyard)
{
    int size;
    in>>size;

    //graveyard.m_cardIds.clear();
    graveyard.m_transformData.clear();

    qDebug()<<" in graveyard size"<<size;

    for(int i=0; i<size; i++)
    {
        int cardId;
        in>>cardId;
        bool loyalty;
        in>>loyalty;
        struct TransformData data={cardId, loyalty};
        graveyard.m_transformData.push_back(data);
        //graveyard.m_cardIds.push_back(cardId);
    }

    return in;
}








