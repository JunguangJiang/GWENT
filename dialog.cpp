#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include "card.h"
#include <QTextCodec>
#include <iostream>
#include "game.h"

Dialog::Dialog(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);//一定要放在开头

    m_myUserId=userId;

    this->resize(1000,750);

    ui->graphicsView->resize(this->width(),this->height());
    ui->graphicsView->setStyleSheet("padding:0px;border:0px");

    mainGameScene=new QGraphicsScene(this);

    //modifyDeck=new Deck(3);
    //mainGameScene->addItem(modifyDeck);

    ui->graphicsView->setScene(mainGameScene);

    //----测试样例----

    long long gameId=0;
    int playerId1=0;
    int playerId2=1;
    playGame(gameId, playerId1, playerId2);

}

void Dialog::uploadGame()
{

}

void Dialog::downloadGame()
{

}

void Dialog::playGame(long long gameId, int playerId1, int playerId2)
{
    game1=new Game(0,0,1,this);
    mainGameBackground=new GraphicsItem(0,0,1,1,MainBackgroundImagePath);
    mainGameScene->addItem(mainGameBackground);

    game1->playGameIn(m_myUserId,mainGameBackground);

    game1->setDeckId(3,2);

    game1->startGame();

}

Dialog::~Dialog()
{
    if(ui)
        delete ui;

    if(game1)
        delete game1;



}

void Dialog::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->resize(this->size());

    mainGameScene->setSceneRect(ui->graphicsView->geometry().left(),ui->graphicsView->geometry().top(),
                        ui->graphicsView->size().width(),ui->graphicsView->size().height());


}


