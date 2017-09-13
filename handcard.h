#ifndef HANDCARD_H
#define HANDCARD_H

#include <QObject>
#include "graphicsitem.h"
#include <vector>
#include "card.h"
#include "carddatabase.h"
//--------------------手牌类----------------------------------
class HandCard : public QObject, public GraphicsItem
{
    Q_OBJECT
public:
    //-----------------外部调用接口---------------------------
    explicit HandCard(const int standPoint, GraphicsItem *parent = nullptr);//手牌初始化时，需要确定这是我发的手牌还是敌方的手牌
    ~HandCard();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//手牌的绘制

    void setLeader(Card* card);//确定领袖
    void useLeader();//使用领袖，未写
    void addCard(Card* newCard);//向手牌中加入新的卡牌
    void removeCard(Card* oldCard);//从手牌中移除卡牌
    void setMoveable(bool moveable);//设置所有的手牌可动
    Card* discardByRandom();//随意丢弃一张手牌
    void setUnseen();//设置手牌不可见
    int getSize()const{return static_cast<int>(m_cards.size());}
    Card *getNthCard(int i)const{return m_cards[i];}
    void clear(){m_cards.clear();}
    void showPass(bool hasPassed){m_hasPassed=hasPassed;}//显示是否让过

    std::vector<int> m_cardIds;
    int m_leaderId;

    friend QDataStream &operator<<(QDataStream &out,const HandCard &handCard);
    friend QDataStream &operator>>(QDataStream &in , HandCard &handCard);

    //------------------内部属性的查询------------------------
    bool isEmpty(){return m_cards.empty();}//查询手牌是否为空
    Card* getLeader()const{return m_leader;}//返回领袖

protected:
    //-------------------paint方法中被调用--------------------
    void showAllCards(QPainter *painter);//显示手牌中的所有卡牌

signals:

public slots:

private:
    //---------------------内部私有属性------------------------
    const int m_standPoint;//0代表是敌方的手牌，1代表是己方的手牌
    std::vector<Card*> m_cards;//手牌中所有的卡牌

    Card* m_leader;//领袖
    bool m_isSeen;//是否看得到卡牌
    bool m_hasPassed;//是否让过
    //bool m_hasUsedLeader;//是否已经使用了leader
};

#endif // HANDCARD_H
