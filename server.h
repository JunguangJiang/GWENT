#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <vector>
#include "user.h"
#include "game.h"
using namespace gwent;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

public slots:

private:
    std::vector<User*> m_users;//维护一个用户的集合，按照用户的游戏积分进行排序
    std::vector<Game*> m_games;//维护一个已经开始，尚未结束的游戏集合

public:
    User* getUserById(int userId){return m_users[userId];}
    void registerUserData();//注册用户信息，这个函数名是默认生成的，可能存在问题
    void loginOfUser(const int id);//接受账号为id的用户的登陆

    void startGameBetween(int userId1, int userId2);//开始账号分别为userId1和userId2的用户之间的一场对战
    void stopGame(int gameId);//结束编号为gameId的游戏
    void saveGame(int gameId);//暂存编号为gameId的游戏

    void updateRankOfUsers();//更新用户集合的排序
    void getRankOfUsers();//返回用户集合的排序，具体返回什么？


};

#endif // SERVER_H
