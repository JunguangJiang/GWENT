#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <vector>
#include "card.h"
#include "graphicsitem.h"
#include "text.h"
//------牌库类------
class Library :public QObject, public GraphicsItem
{
    Q_OBJECT
public:
    explicit Library(int standPoint, GraphicsItem* background);
    ~Library();
    void addCard(Card* card);
    void removeCard(Card* card);
    int getSize()const{return static_cast<int>(m_cards.size());}
    Card* getNthCard(int i) {return m_cards[i];}
    Card* drawACard();//抽一张牌，该过程已经将该牌移出牌库
    Card* drawACardByRandom();//随机抽一张卡
    void shuffleCards();//洗牌
    Card* getCardOfType(TYPE type);//从牌组顶端抽一张type类型的卡牌，该过程已经将牌移出牌库
    Card* getCardOfName(std::string name);//根据名字找牌,该过程不将该牌移出卡牌
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void clear(){m_cards.clear();}

    std::vector<int> m_cardIds;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    friend QDataStream &operator<<(QDataStream &out,const Library &library);
    friend QDataStream &operator>>(QDataStream &in , Library &library);

signals:
    void LibraryPressed();

public slots:

private:
    std::vector<Card*> m_cards;//越靠后的牌越在顶端！！！
    int m_standPoint;
    text *m_sizeShow;
};

#endif // LIBRARY_H
