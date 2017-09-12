#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"
#include <QObject>
#include "graphicsitem.h"
#include "carddatabase.h"
#include "text.h"
#include "button.h"
#include <QDataStream>

using namespace gwent;

class Deck : public QObject, public GraphicsItem //卡组类
{
    Q_OBJECT
public:
    //explicit Deck(GraphicsItem *parent = nullptr);
    Deck (int deckId, GraphicsItem *parent=nullptr);
signals:

public slots:
    void on_cardPressed(Card *card);
    void on_saveButtonPressed();
    void on_exitButtonPressed();

private:
    int m_deckId;//我的卡组编号
    std::vector<int> m_cardId;//完成卡组的创建后，该卡组的所有卡牌的id，同名牌的id也不同

    std::vector<int> m_CardIdOfType[3];
    int m_leader;  //卡组的领袖
    bool m_hasLeader;

    int m_cardNumberOfType[3];//不同种类卡的数量

    int m_totalCardNumber;//包括领袖在内所有卡牌的数量
    CardDatabase* cardDatabase;
    Card *newCard[30];
    text *m_cardNumberShow[3];//显示不同卡牌类型的数量
    text *m_totalCardNumberShow;//显示卡牌总数

    Button *m_saveButton;
    Button *m_exitButton;

    void showAllCards(QPainter *painter);
    void countCardNumber();

public:

    void complete();//完成一个卡组的创建

    int getSize() const{return m_cardId.size();}//返回卡牌的总数
    int getNthCardId(int i)const{return m_cardId[i];}//返回卡组中第i张卡的idOfDatabase

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    friend QDataStream &operator<<(QDataStream &out,const Deck &deck);
    friend QDataStream &operator>>(QDataStream &in , Deck &deck);
};

#endif // DECK_H
