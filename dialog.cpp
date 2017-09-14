#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include "card.h"
#include <QTextCodec>
#include <iostream>
#include "game.h"

#include <QHostInfo>

Dialog::Dialog(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    //-------------------网络相关--------------------
    port=8022;//用于昆特牌的端口
    slotEnter();//连接服务器



    //--------------------游戏相关---------------------
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
    //playGame(gameId, playerId1, playerId2);

}

void Dialog::playGame(long long gameId, int playerId1, int playerId2)//弃用
{
    game1=new Game(0,0,1,this);
    mainGameBackground=new GraphicsItem(0,0,1,1,MainBackgroundImagePath);
    mainGameScene->addItem(mainGameBackground);

    game1->playGameIn(m_myUserId,mainGameBackground);

    game1->setDeckId(3,2);

    game1->startGame();

}

void Dialog::playGameWith(int enemyId, int myDeckId)
{
    game1=new Game(1,m_myUserId, enemyId, this);
    mainGameBackground=new GraphicsItem(0,0,1,1,MainBackgroundImagePath);
    mainGameScene->addItem(mainGameBackground);
    game1->playGameIn(m_myUserId, mainGameBackground);

    game1->setDeckId(3,2);

    connect(this->game1, SIGNAL(uploadGamePackage()), this, SLOT(uploadGame()));//当game类确定要发送game包之后，客户端再向服务器上传game包

    game1->startGame();
}

void Dialog::acceptGame(int enemyId, int myDeckId)
{
    game1=new Game(1,enemyId, m_myUserId, this);
    //game1=new Game(0,m_myUserId, enemyId, this);
    mainGameBackground=new GraphicsItem(0,0,1,1,MainBackgroundImagePath);
    mainGameScene->addItem(mainGameBackground);
    game1->playGameIn(m_myUserId, mainGameBackground);

    game1->setDeckId(3,2);

    connect(this->game1, SIGNAL(uploadGamePackage()), this, SLOT(uploadGame()));//当game类确定要发送game包之后，客户端再向服务器上传game包
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


//------------------网络相关-----------------------

void Dialog::slotEnter()//客户端与服务器连接
{
    qDebug()<<"try to connect";
    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    tcpSocket->connectToHost(QHostAddress::LocalHost, port);//连接到本机
    tcpSocket->waitForConnected();

}

void Dialog::slotConnected()//当与服务器连接成功后
{
    qDebug()<<"succeed connect to server";
    //tcpSocket->waitForReadyRead();
}

void Dialog::uploadGame()//上传游戏
{
    slotSend();
}

void Dialog::slotSend()//发送game数据包
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out<<(*game1);
    int length=tcpSocket->write(datagram, datagram.size());
    tcpSocket->waitForBytesWritten();
    while(length!=datagram.size());
    {
        length=tcpSocket->write(datagram, datagram.size());
        tcpSocket->waitForBytesWritten();
    }
    //tcpSocket->write(datagram, datagram.size());
    //tcpSocket->waitForBytesWritten();

    qDebug()<<"player"<<m_myUserId<<" send the game";
}

void Dialog::slotDisconnected()//当与服务器断开连接后的处理
{
    game1->saveGame();//此处没有完成
    qDebug()<<"player"<<m_myUserId<<" disconnected";
}

void Dialog::dataReceived()//当客户端接受到数据
{
    qDebug()<<"player"<<m_myUserId<<"get a game package";
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());

        QDataStream in(&datagram,QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_9);
        tcpSocket->read(datagram.data(), datagram.size());

        //datagram=tcpSocket->readAll();
        in>>(*game1);//将game包读入，在game类内部会决定是否丢弃该包
    }



    qDebug()<<"player"<<m_myUserId<<"finish read the game";

}

