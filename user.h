#ifndef USER_H
#define USER_H

#include <QObject>
#include <vector>
#include <string>

#include "deck.h"
#include "game.h"

using namespace gwent;

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(int id, QObject *parent = nullptr);
    ~User();
signals:

public slots:

private:
    const int m_id;//用户的账户
    std::string m_name;//用户的名字
    std::string m_password;//用户的密码
    std::vector<int> m_friends;//用户的好友

    std::vector<Deck*> m_decks;//每个用户可以有多个卡组
    int m_gameCredit;//游戏积分

    long long m_currentGameId;//我当前游戏的编号，假如没有则-1

public:
    void setName(std::string newName);//改名字
    void setPassword(std::string newPassword);//改密码
    void insertNewFriend(int friendId);//通过账户添加好友
    void insertNewFriend(std::string friendName);//通过名字添加好友
    void removeOldFriend(int friendId);//删除好友
    void createNewDesk();//创建新的卡组
    void removeOldDesk(int i);//删除第i个卡组
    void modifyDesk(int i);//修改第i个卡组

    int getId() const;//获取自己的id
    int getName()const;//获取自己的名字
    int getNthFriend(int i)const;//获取第i个好友的id
    Deck* getNthDeck(int i)const;//获取第i个卡牌的地址
    int getGameCredit()const;//获取自己的游戏积分

    void inquryRankOfCredit() const;//查询本服务器的用户积分榜
    void sendInvitationOfGameTo(int id);//向用户id发送比赛请求
    void sendInvitationOfWatchingGameTo(int id);//向用户id发送旁观请求

    void playGameWith(int id);//请求与id玩游戏,设立某些特殊的id为AI的id
    void stopGame();//请求终止游戏
    void saveGame();//请求存储游戏进度

};

#endif // USER_H
