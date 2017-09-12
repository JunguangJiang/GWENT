#ifndef BATTLE_H
#define BATTLE_H

#include <vector>
#include "card.h"
#include "graphicsitem.h"
#include "text.h"
#include <QObject>
#include <QDataStream>
using namespace gwent;

class Player;

struct TransformData//传输的数据结构
{
    int id;//在卡组中的id
    bool loyalty;//忠诚度
};

//-----------------------------战排类------------------------------------
class BattleField:public QObject, public GraphicsItem
{
    Q_OBJECT

public:
    //--------------------------外部调用接口----------------------------------
    BattleField(const COMBAT_ROW type, GraphicsItem *parent = Q_NULLPTR);//战排初始化是需要说明战排的类型
    ~BattleField();
    CLIMATE getClimate();               //得到当前排的天气
    int getTotalStrength();               //返回战排的总分
    bool checkTypeOf(Card *newCard);    //检查新卡牌的站位属性，如果与当前战排相符，则返回true
    COMBAT_ROW getType()const{return m_type;}//返回战排的类型

    //---------------查询卡牌------------------------------------
    Card *getNthCard(int i)const{return m_currentCard[i];}//返回战排第i张卡牌
    int getSize()const{return static_cast<int>(m_currentCard.size());}//返回战排上的总卡牌数

    Card *getLeftCard(Card *card);//得到card在该排中左边的一张卡，如果card不在该排或者右边没有卡，则返回空
    Card *getRightCard(Card *card);//得到card在该排中右边的一张卡，如果card不在该排或者右边没有卡，则返回空

    Card *getWeakestCard()const;//返回最弱的牌
    Card *getStrongestCard() const;//返回最强的牌

    //--------------------------绘图相关----------------------
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//战排的绘画
    void showBorder(){m_showBorder=true;}
    void hideBorder(){m_showBorder=false;}

    //--------------------对战排的操作------------------------------------
    bool changeClimate(CLIMATE climate);//改变排的天气
    int increaseFrostHarmBy(int harmIncrease){m_frostHarm+=harmIncrease;}//增加刺骨冰霜的伤害
    bool addCard(Card *newCard);        //向战排末尾中加入新的卡牌
    bool removeCard(Card *oldCard);     //从战排中删除卡牌
    void insert(Card *oldCard, Card* newCard);//在oldCard之前插入newCard

    //bool addCard(Card *newCard, int rank);//在第rank位置之前加入新的卡牌，插入后变成第rank张卡牌
    //bool removeCard(int rank);              //删去第rank位置的卡牌
    void clearAll();                       //清空所有卡牌，同时清除天气效果

    //------------------------战排的流化----------------------------------
    friend QDataStream &operator<<(QDataStream &out,const BattleField &battleFeild);
    friend QDataStream &operator>>(QDataStream &in , BattleField &battleField);
    std::vector<TransformData> m_currentCardId;//当前战排上的卡牌在卡组中的编号
    std::vector<Card *> m_currentCard;   //当前战排上的牌

protected:
    //----------------------战排的私有变量-------------------------------------
    const COMBAT_ROW m_type;  //战排的类型，分为近场、远程、攻城
    CLIMATE m_climate;  //战排的天气效果
    bool m_showBorder;//是否显示边界
    text* m_totalStrength;//总战斗力

    int m_frostHarm;//刺骨冰霜的伤害

    //---------------------在paint中调用的内部函数------------------------------
    void showAllCards();//展示卡牌上所有的卡牌
    void showBorder(QPainter *painter);//展示当前战排是否被拖动的卡牌movingCard选中
    void showWeather(QPainter *painter);    //展现不同的天气效果

public slots:
    void mouseDoubleClickEvent(QGraphicsSceneEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void getDemagedByWeather();//由于天气原因，给场上的卡牌造成损害。当场上有特殊天气，并且对手出牌时接受到信号

signals:
    void battleFeildPressed(BattleField* battleField);//当战排被点击时发送信号
    void changeClimate(CLIMATE climate, BattleField* battleField);//当战排天气改变时发送信号
    void updateBattleStrengthShow();//当战排总战力显示更新时发送信号，note:战排的战斗力可能并没有发生改变
};




#endif // BATTLE_H
