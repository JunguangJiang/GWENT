#include "library.h"
#include <algorithm>
#include <QDebug>
Library::Library(int standPoint, GraphicsItem *background):
    GraphicsItem(LibararyPos[standPoint], LibararySize, LibraryImagePath, background),
    m_standPoint(standPoint)
{
    m_sizeShow=new text(LibraryShowPos[standPoint], LibraryShowSize, background);
    m_sizeShow->setFontSize(16);
    m_sizeShow->setBackgroundColor(Qt::black);
    m_sizeShow->setFontColor(Qt::gray);
    m_cardIds.clear();
    m_cards.clear();
    qDebug()<<this->boundingRect();
    this->show();
}

Library::~Library()
{
    if(m_sizeShow)
    {
        delete m_sizeShow;
    }
}

void Library::addCard(Card *card)
{
    if(!card)
        return;

    auto iter=find(m_cards.begin(), m_cards.end(), card);
    if(iter==m_cards.end())
    {
        m_cards.push_back(card);
        card->setStatus(STATUS::DECK);
    }
    this->update();
}

void Library::removeCard(Card *card)
{
    if(!card)
        return;

    auto iter=find(m_cards.begin(), m_cards.end(), card);
    if(iter==m_cards.end())
    {
        return;
    }

    if(*iter)
    {
        m_cards.erase(iter);
    }
    this->update();
}

Card* Library::drawACard()
{
    if(m_cards.empty())
    {
        return Q_NULLPTR;
    }
    Card* card=m_cards.back();
    m_cards.pop_back();
    this->update();
    return card;
}

void Library::shuffleCards()//洗牌
{
    for(int i=m_cards.size()-1; i>0; i--)
    {
        int randNum=rand()%(i+1);
        std::swap(m_cards[i],m_cards[randNum]);
    }
    qDebug()<<"after shulffing";
    for(int i=0; i<m_cards.size(); i++)
    {
        if(m_cards[i])
        {
            qDebug()<<i<<": "<<QString::fromStdString(m_cards[i]->getName());
        }
    }

}

Card* Library::getCardOfType(TYPE type)
{
    for(auto iter=m_cards.rbegin(); iter!=m_cards.rend(); iter++)//从牌组顶端出发遍历,调试阶段用的是从底部出发遍历
    {
        if((*iter)){
            if((*iter)->getInitType()==type)//如果找到某张牌的类型符合
            {
                Card *card=*iter;
                removeCard(*iter);//则从牌库删除这张牌
                return card;//并且返回该牌的指针
            }
        }
    }
    return Q_NULLPTR;
}

Card* Library::getCardOfName(std::string name)
{
    if(m_cards.empty())
    {
        return Q_NULLPTR;
    }
    if(name=="")
    {
        return Q_NULLPTR;
    }

    for(auto iter=m_cards.begin(); iter!=m_cards.end(); iter++)
    {
        if(*iter){
            if((*iter)->getName()==name)//如果找到某张牌的名字符合
            {
                qDebug()<<"find:"<<QString::fromStdString((*iter)->getName());
                Card* card=*iter;
                m_cards.erase(iter);
                //removeCard(*iter);//则从牌库删除这张牌
                return card;//并且返回该牌的指针
            }
        }
    }
    return Q_NULLPTR;
}

void Library::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItem::paint(painter,option,widget);

    if(m_sizeShow)
    {
        m_sizeShow->setText(std::to_string(m_cards.size()));
        m_sizeShow->update();
    }
}

void Library::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit LibraryPressed();
}

void Library::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit LibraryPressed();
}

QDataStream &operator<<(QDataStream &out,const Library &library)
{

    out <<library.getSize();
    qDebug()<<"libary out size"<<library.getSize();

    for(int i=0; i<library.getSize(); i++)
    {
        if(library.m_cards[i])
        {
            out<<(library.m_cards[i]->getId());
        }
    }

    return out;
}

QDataStream &operator>>(QDataStream &in , Library &library)
{
    int size;
    in>>size;

    qDebug()<<"library in size"<<size;

    library.m_cardIds.clear();

    for(int i=0; i<size; i++)
    {
        int cardId;
        in>>cardId;
        library.m_cardIds.push_back(cardId);
    }

    return in;
}
