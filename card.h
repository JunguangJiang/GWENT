#ifndef CARD_H
#define CARD_H

#include <string>
#include <QObject>
#include "graphicsitem.h"
#include "parameter.h"
#include "text.h"
#include <QDebug>
using namespace gwent;

class Player;
class BattleField;
class HandCard;
class Game;

struct TransformData//传输的数据结构
{
    int id;//在卡组中的id
    bool loyalty;//忠诚度
};


//----------------------------卡牌类-----------------------------


class Card:public QObject, public GraphicsItem
{
    Q_OBJECT
protected:
    //--------------------私有的属性-----------------------------
    int m_id;                 //卡牌在卡组或者游戏中编号，是卡牌在玩家中的唯一标志物
    int m_idOfDatabase;             //卡牌在数据库中的编号，在卡组中可能重复
    const RACE m_race;              //卡牌的种族
    const std::string m_name;       //卡牌的名字
    const std::string m_imagePath;       //卡牌图片的存储路径
    const std::string m_description;     //卡牌的说明
    const int m_initStrength;       //卡牌初始时的基础战力
    int m_actualStrength;           //实际战力
    const TYPE m_initType;          //卡牌的初始等级类型
    TYPE m_actualType;              //卡牌的实际等级类型
    const COMBAT_ROW m_initCombatRow;   //卡牌在战场上摆放的可能位置
    COMBAT_ROW m_actualCombatRow;   //卡牌在战场上摆放的实际位置
    const bool m_loyalty;           //卡牌的忠诚度
    bool m_hasShield;               //是否有护盾
    int m_armor;                      //卡牌的护甲，暂时认为是可以累加的
    STATUS m_status;                  //卡牌的当前状态
    bool m_isSeen;                      //卡牌是否可见,比如对手的手牌就是不可见的

    bool m_showGoalLine;            //是否显示目标指示线

    bool m_isDispatching;//当前是否正在调度

    //-----------------在游戏中用于显示卡牌当前信息的文本框------------
    text *m_strengthShow;
    text *m_armorShow;
    text *m_shieldShow;

    //----------------在卡牌派生类中用到的属性-----------------
    Player *m_oursizePlayer;        //对于卡牌而言的己方玩家
    Player *m_enemyPlayer;          //对于卡牌而言的对方玩家
    Game *m_game;                   //卡牌所在的游戏

    //----------------在组成卡组界面中用到的属性----------------
    bool m_showAmountInDeck;        //是否显示在卡组中的数量
    bool m_isLeader;//在卡组中是否是领袖


public:
    //---------------------公有的操作-------------------------------
    Card(GraphicsItem *parent=Q_NULLPTR);
    Card(const RACE race,
         const std::string name,
         const std::string imagePath,
         const std::string description,
         const int initStrenth, const TYPE initType,
         const COMBAT_ROW initCombatRow, const bool loyalty,
         GraphicsItem *parent=Q_NULLPTR
            );//一般卡的初始化

    Card(const RACE race,
         const std::string name,
         const std::string imagePath,
         const std::string description,
         const TYPE initType,
         GraphicsItem *parent=Q_NULLPTR);//特殊卡的初始化（没有战斗力和站位）

    Card(const Card& oldCard, GraphicsItem *parent=Q_NULLPTR);//复制构造函数

    void initialize();//卡牌每次重新使用之前都需要初始化
    void setLeftTop(qreal left, qreal top); //设置卡牌的位置，left和top是卡牌左上方点的横纵坐标
    void setLeftTop(QPointF pos);
    void setMoveable(bool moveable);//设置卡牌是否可移动
    void setUnseen();//设置卡牌可见
    void setSeen();//设置卡牌不可见
    bool isSeen()const{return m_isSeen;}//检查卡牌是否可见

    void setActualCombatRow(const COMBAT_ROW combatRow){m_actualCombatRow=combatRow;}//设置卡牌的实际站位
    void setStatus(const STATUS status);//改变卡牌的状态
    static Card *getWeakerCard(Card *card1, Card *card2);//返回两张卡中的实际战力较小的一张
    static Card *getStrongerCard(Card *card1, Card *card2);//返回两张卡中实际战力较大的一张

    void setId(int id){m_id=id;}//设置卡牌在卡组中的id
    void setIdOfDatabase(int id){m_idOfDatabase=id;}//设置卡牌在数据库中的id

    void showGoalLine(bool show){m_showGoalLine=show;}//是否显示目标指示线
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//卡牌的绘画

    void setIsDispatching(bool isDispatching){m_isDispatching=isDispatching;}//设置
    bool getIsDispatching()const{return m_isDispatching;}//与查询当前是否正在调度

    //---------------------在派生类中用到的函数----------------------
    virtual void setGame(Game* game){qDebug()<<"set game virtual";}//设置当前卡牌是在哪场游戏中
    void setOursidePlayer(Player *player){m_oursizePlayer=player;}//设置当前卡牌的拥有者
    void setEnemyPlayer(Player *player){m_enemyPlayer=player; }//设置卡牌拥有者的对手

    //---------------------用于流化和网络编程的函数--------------------
    friend QDataStream &operator<<(QDataStream &out,const Card &card);
    friend QDataStream &operator>>(QDataStream &in , Card &card);

    //---------------------用于构建卡组界面的属性和操作-----------------
    int m_amountInDeck;//在卡组中的数量
    void showAmountInDeck(bool show){m_showAmountInDeck=show;}//设置是否在卡组图片上显示数量
    text* m_amountShow;//显示数量的文本框
    text* m_leaderShow;//显示是否是领袖的文本框

    //--------------------查询私有属性的方法接口--------------------------
    int getId() const{return m_id;}
    int getIdOfDatabase() const{return m_idOfDatabase;}
    RACE getRace() const{return m_race; }
    std::string getName() const{return m_name;}
    int getActualStrength() const { return m_actualStrength;}
    TYPE getInitType()const{return m_initType;}
    TYPE getActualType() const {return m_actualType; }
    COMBAT_ROW getInitCombatRow() const { return m_initCombatRow;}
    COMBAT_ROW getActualCombatRow() const {return m_actualCombatRow; }
    bool getLoyalty() const {return m_loyalty;}
    STATUS getStatus() const {return m_status;}
    std::string getImagePath()const {return m_imagePath;}
    std::string getDescription()const {return m_description;}
    bool hasShield()const{return m_hasShield;}//是否有护盾
    int hasArmor()const{return m_armor;}//拥有的护甲值
    bool isGoldenCard()const{return m_actualType==TYPE::GOLD;}//是否是金卡

    bool canBeLeader()const {return m_initCombatRow==COMBAT_ROW::LEADER;}//判断是否为领袖卡(即具有成为领袖资质的卡)
    bool isLeader()const{return m_isLeader;}//判断在当前卡组中是否为领袖
    void setLeader(bool isLeader){if(canBeLeader())  m_isLeader=isLeader;}//设置其成为领袖
    bool isDead() const {return (m_actualStrength<=0);}//判断是否死亡
    QPointF getCenterPoint(qreal left, qreal top)const//将左上端点转化为卡牌的中心点的坐标
    {
        return QPointF(left+0.5*cardWidth, top+0.5*cardHeight);
    }

    //----------------------卡牌特殊技能实现的接口----------------------------
    void getShield();//获得护盾
    void loseShield();//使用一次护盾后即失去
    void getHarm(const int harm);//获得伤害
    void getGain(const int gain);//获得增益
    void getArmor(const int armor);//获得护甲
    void setStrength(const int strength);//改变战力
    virtual void showSpecialCard(){}//展现特殊卡
    virtual void battleFieldToGraveyard(bool isOurside){}//从战场进入墓地时响应
    void backToOriginState();//回到初始状态，进入墓地时调用
    virtual void beforeBeSwallowed(){}//在被吞噬前触发，因为鹰身女妖蛋可以有吞噬加成

    //-----------------------卡牌与用户交互时的直接操作-----------------------
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);//鼠标悬浮
    void mousePressEvent(QGraphicsSceneMouseEvent *event);//鼠标点击
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event){}//鼠标释放
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event){}//鼠标移动
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){}//鼠标双击，用于特殊卡的发动

public slots:
    //----------------------卡牌的特殊效果接口----------------------------
    virtual void on_changeStatusByWeather(CLIMATE climate,BattleField* battleField){}//由于某种天气效果，进入战排或离开战排
    virtual void on_handToBattleField(COMBAT_ROW combatRow){}//从手牌进入战场时响应

    virtual void changeWeather(BattleField* battleField){}//改变某个战排的天气
    virtual void on_CardPressed(Card *card){}//当其他某张card被点击时做出响应
    virtual void swallow(Card *food){}//吞噬掉卡food
    virtual void on_playerGetTurn(){}//当我方选手轮到出牌时响应
    virtual void produce(){}//生成一些东西
    virtual void on_battlePressed(BattleField *battleField){}//当其他战排被点击时做出响应
    virtual void on_addToLibrary(){}//当被加入卡库时触发
    virtual void on_libraryPressed(){}//当我方的卡库被点击时触发
    virtual void on_playerLoseTurn(){}//当我方选手失去发牌机会时触发
signals:
    void swallowFriend();//每当有友军单位吞噬1张牌，则发送该信号
    void handToBattleField(COMBAT_ROW combatRow, Card *card);//从手牌进入战排
    void battleFieldToBattleField(COMBAT_ROW oleBattle, COMBAT_ROW newBattle, Card *card);//从战排到战排
    void addToLibrary();//加入牌库的信号
    //------------------卡牌与用户交互时向外发送的信号--------------------------
    void cardReleaseAt(QPointF point, Card* card);//卡牌中心位置在point点处释放
    void cardMoveBy(QPointF point, Card* card);//卡牌移动到point点
    void cardPressed(Card *card);//鼠标点击卡牌
    void cardHover(Card *card);//鼠标移动到卡牌上方

    void cardDispatched(Card *card);//这张卡将被调度
};



#endif // CARD_H
