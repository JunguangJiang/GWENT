#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "player.h"
#include "carddatabase.h"
#include "parameter.h"
#include "button.h"
class Game : public QObject
{
    Q_OBJECT
public:
    //--------------------外部访问的接口----------------------
    explicit Game(long long gameId,  int userId1, int userId2,  QObject *parent = nullptr);//一场新的游戏的初始化，需要游戏的编号和两个用户的id
    ~Game();
    void setDeckId(int deckId1, int deckId2);//确定两个玩家的卡组编号
    void playGameIn(int userId, GraphicsItem* background);//调用它的用户id是userId，以background为背景开始玩游戏
    void startGame();//开始玩游戏
    void stopGame();//终止游戏
    void saveGame();//存储游戏进度
    void continueGame();//继续游戏

    void saveGame(const QString gameFile);
    void updateGame(const QString gameFile);

    Player* getPlayer(int i)const{return m_player[i];}

    friend QDataStream &operator<<(QDataStream &out,const Game &game);
    friend QDataStream &operator>>(QDataStream &in , Game &game);

signals:
    
public slots:
    //void on_cardReleaseAt(QPointF point, Card* card);//对卡牌释放的事件作出响应
    //void on_cardMoveBy(QPointF point, Card* card);//对卡牌拖动的事件作出响应
    void on_cardPressed(Card *card);//对卡牌点击事件作出响应
    void on_cardHover(Card *card);//对卡牌上方有鼠标悬浮事件作出响应
    void on_battleFieldPressed(COMBAT_ROW combatRow);//对战排点击事件作出响应
    void on_oneSecondGone();//计时器每过1s响应一次
    void on_playerLoseTurn();//当玩家失去一次机会时响应

private:
    const long long m_gameId;//游戏的id
    int m_userId[2];//两个玩家的id
    int m_deckId[2];//两个玩家的卡组编号
    int m_userIdOfDialog;//调用game的dialog类的用户id
    
    Player* m_player[2]; //两个玩家的信息
    int m_currentPlayingUserNumber; //当前正在发牌的玩家的编号，我方OURSIDE，敌方ENEMY
    int m_currentRound;//当前是第几局，有0,1，2三种取值
    
    GameStatus m_gameStatus;  //全局游戏运行状态
    GameStatus m_gameRoundStatus[3]; //小局游戏运行状态
    int winningTimes[2];//两个玩家各自赢的次数
    
    void decideOrderOfCards();//决定出牌顺序

    void enterANewRound();//进入新的一个回合
    bool judgeOfGameRound();//判断小局的胜负
    bool judgeOfGame();//判断正常游戏的胜负

    //void setTimerForHandCard(int seconds);//为发手牌的时间提供一个计时函数，超过seconds，则丢弃当前玩家的任意一张手牌

    GraphicsItem* m_bigCardImage;//卡牌的右方大图片
    text* m_cardName;//卡牌的右方名字
    text* m_cardDescription;//卡牌的右方描述

    Button *m_passButton;//放弃按钮
    text* m_leftTimeShow;//显示剩余的时间
    text* m_turnShow;//显示当前轮到哪位玩家发牌


    GraphicsItem* m_background;//游戏背景
    COMBAT_ROW getBattleFieldOfPoint(QPointF point)const;//判断point在哪个战排内，如果不在任何一个战排内则返回-1
    void connectAll();//连接所有的信号
    void updateTime();//更新界面的元素（显示剩余的时间、显示当前轮到哪位玩家发牌）

    int m_lastWinner;//记录上一局赢的玩家

    GraphicsItem* m_redrawBackground;//调度的背景

private slots:
    void on_buttonPressed();//当按下放弃按钮时响应

};

#endif // GAME_H
