#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include <QObject>
#include <vector>
#include "card.h"
#include "text.h"
#include "graphicsitem.h"


class Graveyard : public QObject,public GraphicsItem
{
    Q_OBJECT
public:
    explicit Graveyard(int standPoint, GraphicsItem *background);
    ~Graveyard();
    void addCard(Card* card);
    void removeCard(Card* card);
    int getSize()const{return static_cast<int>(m_cards.size());}
    void clear(){m_cards.clear();}//只是清空m_cards
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //std::vector<int> m_cardIds;
    std::vector<TransformData> m_transformData;//当前墓地的卡牌在卡组中的编号

    friend QDataStream &operator<<(QDataStream &out,const Graveyard &graveyard);
    friend QDataStream &operator>>(QDataStream &in , Graveyard &graveyard);

signals:

public slots:

private:
    std::vector<Card*> m_cards;
    int m_standPoint;
    GraphicsItem* m_background;
    text* m_sizeShow;
};

#endif // GRAVEYARD_H
