#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QResizeEvent>
#include "graphicsitem.h"
#include "battle.h"
#include "carddatabase.h"
#include "user.h"
#include "game.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int userId, QWidget *parent = 0);
    ~Dialog();

    void playGame(long long gameId, int playerId1, int playerId2);//由服务器发送来的信号开始游戏

public slots:
    //void on_cardHover(Card* card);
    void uploadGame();//上传游戏
    void downloadGame();//下载游戏

private:
    Ui::Dialog *ui;
    QGraphicsScene *mainGameScene;//游戏主界面
    GraphicsItem *mainGameBackground;//游戏主界面的背景


    int m_myUserId;

    Game *game1;


    GraphicsItem* modifyDeck;//修改卡组的界面



protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // DIALOG_H
