#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <vector>
#include "battle.h"
#include "parameter.h"
#include "handcard.h"
#include "graveyard.h"
#include "library.h"

#include "graphicsitem.h"
#include "text.h"
#include "carddatabase.h"

#include <QTimer>
#include <QThread>

using namespace gwent;
class Game;
 //--------------------某一局游戏的玩家类----------------------------

class Player : public QObject
{
    Q_OBJECT

public:
    //--------------------外部调用接口------------------------------
    explicit Player(const int userId, QObject *parent = nullptr);//初始时，需确定用户的id
    ~Player();
    //-------------------创建游戏相关--------------------------------
    void chooseBackgroud(GraphicsItem* background, int standPoint);//选择游戏背景,立场standPoint分为我方OURSIDE，敌方ENEMY
    void createCard(Card* card);//生成一张新的卡,然后将卡牌的地址存储在m_card中，同时连接游戏和背景，确定其id
    void chooseDeck(int deckId);//选择自己编号为deckId的卡组

    //--------------------游戏逻辑相关--------------------------------
    void shuffleCards();//洗牌
    void drawInitCards();//游戏初始时抽手牌，实质上就是从牌库中抽10张牌
    void drawACardFromLibrary();//从牌库中抽一张牌
    //void dispatchCardFromTo(Card* oldCard, Card* newCard);//调度第i个选手的一张卡牌
    void dispatchCard(Card* oldCard);

    void getTurn();         //获得出牌机会，由game类通知后获得
    void loseTurn();        //失去出牌机会
    //note::失去出牌机会的4中可能：
        //1.时间到了没发牌
        //2.发牌但没有发动卡牌效果+时间到了
        //3.选择pass
        //4.发牌并且发动完卡牌效果

    void addCardFromHandToBattle(Card* card, COMBAT_ROW combatRow); //从手牌中发出一张牌到战排上
    void enterANewRound();  //进入新的一个回合

    void choosePassed();    //选择让过
    void loseOneHandcardByRandom();//随机丢弃一张手牌

    void turnOnTimer(){m_timerSwitch=true;}//打开定时器
    void turnOffTimer(){m_timerSwitch=false;}//关闭定时器

    void hideBordersOfAllBattles();//所有的战排的边框都不显示
    void updateAllBorders();//刷新所有的战排

    friend QDataStream &operator<<(QDataStream &out,const Player &player);
    friend QDataStream &operator>>(QDataStream &in , Player &player);

    //--------------------内部属性查询接口--------------------------
    int getTotalStrength() const;//计算玩家的总分
    bool canMoveCard() const {return m_isOnTurn;}//此时是否可以移动手牌
    BattleField *getBattle(COMBAT_ROW combatRow)const;//根据combatrow返回相应的战排指针
    COMBAT_ROW getBattleFieldOfPoint(QPointF point) const;//返回与坐标相对应的战排
    int getCardsSize()const{return m_card.size();}//获得玩家的总卡片数大小
    //int getCardsSize()const{return cardSize;}//获得玩家的总卡片数大小
    Card* getNthCard(int i)const{return m_card[i];}//获得玩家总卡片中的第i张
    Card *getWeakestCard()const;//返回玩家战排上的最弱卡
    Card *getStrongestCard()const;//返回玩家战排上的最强卡

    bool isOnTurn()const{return m_isOnTurn;}//判断玩家当前是否轮到出牌

    int getLeftTime()const{return m_leftTime;}//返回玩家出牌的剩余时间
    QTimer* getTimer(){return m_timer;}//返回时钟

    void setHasDealed(bool hasDeal){m_hasDealed=hasDeal;}//设置当前是否已经发牌了
    bool getHasDealed()const{return m_hasDealed;}//查询当前局是否已经发牌

    void setIsDispatchingCard(bool isDispatchingCard){m_isDispatchingCard=isDispatchingCard;}//设置
    bool getIsDispatchingCard()const{return m_isDispatchingCard;}//与查询当前是否正在调度

    void setHasChosenPassed(bool hasChosenPassed){m_hasChosenPassed=hasChosenPassed;}
    bool getHasChosenPassed() const{return m_hasChosenPassed;}//是否选择了让过

    void updatePassShow();//更新是否让过的状态显示

signals:
    void playerGetTurn();//每次该选手轮到出牌时，发送该信号
    void playerLoseTurn();//每次选手出牌时间用完时，发送该信号

public slots:
    //------------------外部响应接口-------------------------------
    void on_cardReleaseAt(QPointF point, Card* card);//对卡牌释放的事件作出响应
    void on_cardMoveBy(QPointF point, Card* card);//对卡牌拖动的事件作出响应

    void updateTotalStrengthShow();//更新玩家总分的显示
    void on_oneSecondGone();//每过1s响应一次

public:
    //-----------------玩家类所拥有的物品---------------------------
    BattleField *closeBattle, *remoteBattle, *siegeBattle;//每个玩家的领土上有三个不同的战排
    HandCard* handCard;//手牌
    Library* library;//牌库
    Graveyard* graveyard;//墓地
    text* m_totalStrengthShow;//我的总分显示

private:
    //------------------玩家类的私有属性-----------------------------
    const int m_userId;//用户的id
    int m_standPoint;//我的立场

    bool m_hasDealed;//当前局是否已经发牌
    QTimer* m_timer;//我的定时器
    QThread *m_timerThread;//我的定时器线程

    int m_leftTime;//我剩余的时间
    bool m_isOnTurn;//是否轮到发牌
    bool m_timerSwitch;//定时器的开关

    bool m_isDispatchingCard;//当前是否正在调度
    bool m_hasChosenPassed;        //是否选择了让过

    //--------------------调度过程中用到的私有变量-------------
    Card* m_dispatchingOldCard[3];//调度中丢掉的3张卡
    int m_dispatchingCardNumber;//目前已经调度了几张卡

public:
    //我的卡牌
    std::vector<Card*> m_card;

    GraphicsItem* m_background;//游戏背景
    Game *m_game;//游戏指针    
};



#endif // PLAYER_H
