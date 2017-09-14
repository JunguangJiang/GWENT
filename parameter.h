#ifndef GEOGRAPHICALPARAMETER_H
#define GEOGRAPHICALPARAMETER_H
#include <vector>
#include <QPoint>
#include <QSize>
//定义了一些游戏界面中用到的参数

namespace gwent {
//-------------------界面编号--------------------------------
const int InitialInterface=0;//初始化界面
const int MainGameInterface=1;//游戏界面
const int ModifyDeckInterface=2;//编辑卡组界面

//------------------------存储格式-----------------------------
const QString GameFilePrefix=QString("/Users/jiangjunguang/Desktop/GwentClient2/GWENT2/Game");//目前不是前缀
const QString DeckFilePrefix=QString("/Users/jiangjunguang/Desktop/GwentClient2/GWENT2/Deck");
//--------------------------主游戏---------------------------------
//---调试用---
const QString GameFileName=QString("Game1.dat");

//----------------------------逻辑部分------------------------------
const int ENEMY=0;//敌方
const int OURSIDE=1;//我方

const int GOLD=0;//金卡
const int SILVER=1;//银卡
const int BRONZE=2;//铜卡

const QPointF UnseenPos=QPointF(1,1);//不可见的位置
const QSizeF WholeSize=QSizeF(1,1);//整个界面的大小
//--------------------------背景部分-------------------------
const QString BlankBackgroundImagePath=QString(":/img/ui/res/uiPicture/Blank.png");//空边背景的图像路径

const QString MainBackgroundImagePath=QString(":/img/ui/res/uiPicture/6_mainWindow.png");//主要游戏的界面图片路径

//右方大图
const QPointF BigCardImagePos=QPointF(0.78,0.14);
const QSizeF BigCardImageSize=QSizeF(0.21,0.42);
//当前卡牌的名字
const QPointF CardNamePos=QPointF(0.8,0.55);
const QSizeF CardNameSize=QSizeF(0.17,0.04);
//当前卡牌的描述
const QPointF CardDescriptionPos=QPointF(0.78, 0.6);
const QSizeF CardDescriptionSize=QSizeF(0.21,0.2);

//放弃按钮的位置和尺寸,图片路径
const QPointF PassButtonPos=QPointF(0.062,0.43);
const QSizeF PassButtonSize=QSizeF(0.08,0.13);
const QString PassButtonImagePath=QString(":/img/ui/res/uiPicture/passBotton.png");

//当前轮到出牌玩家信息的显示
const QPointF TurnShowPos=QPointF(0.02,0.56);
const QSizeF TurnShowSize=QSizeF(0.2,0.06);

//当前出牌玩家的剩余时间的显示
const QPointF LeftTimeShowPos=QPointF(0.14, 0.5);
const QSizeF LeftTimeShowSize=QSizeF(0.055, 0.085);

//当前局数的显示
const QPointF GameRoundShowPos=QPointF(0.1,0.8);
const QSizeF GameRoundShowSize=QSizeF(0.1,0.1);

//上一局结果的显示
const QPointF GameRoundResultShowPos=QPointF(0.8,0.7);
const QSizeF GameRoundResultShowSize=QSizeF(0.2,0.2);

//整场游戏的结果
const QPointF GameResultShowPos[2]={
    QPointF(0.3, 0.4),
    QPointF(0.3, 0.6)
};
const QSizeF GameResultShowSize=QSizeF(0.4,0.2);

const QString GameResultShowImagePath=QString("://res/uiPicture/GameEnding.png");
//----------------------------玩家部分----------------------------


const int PlayerDealTime=30;//玩家的发牌时间

const QPointF PlayerStrengthShowPos[2]=//玩家总战斗力的显示位置
{
    QPointF(0.14, 0.28),
    QPointF(0.14, 0.63)
};
const QSizeF PlayerStrengthShowSize=QSizeF(0.055, 0.085);//玩家总战斗力的显示部分的尺寸


//----------------------------战排部分---------------------------

const QPointF BattleFieldLeftTopPoint[6]//定义图形界面中六个战排各自的左上端点的坐标
={
    QPointF(0.260,0.14),
    QPointF(0.260, 0.251),
    QPointF(0.260, 0.362),
    QPointF(0.260, 0.505),
    QPointF(0.260, 0.616),
    QPointF(0.260, 0.727)
};

const QPointF BattleStrengthShowPos[6]//战排总战斗力的显示位置
={
    QPointF(0.214, 0.177),
    QPointF(0.214, 0.287),
    QPointF(0.214, 0.397),
    QPointF(0.214, 0.529),
    QPointF(0.214, 0.639),
    QPointF(0.214, 0.749)
};
const QSizeF BattleStrengthShowSize=QSizeF(0.045,0.075);//战排总战斗力的显示部分的尺寸

const QSizeF BattleFieldSize=QSizeF(0.476, 0.111);//战排的尺寸

const QString BattleFieldImagePath[6]=
{
  QString(":/img/ui/res/uiPicture/enmySeigeBattle.png"),
    QString(":/img/ui/res/uiPicture/enmyRemoteBattle.png"),
    QString(":/img/ui/res/uiPicture/enmyCloseBattle.png"),
    QString(":/img/ui/res/uiPicture/myCloseBattle.png"),
    QString(":/img/ui/res/uiPicture/myRemoteBattle.png"),
    QString(":/img/ui/res/uiPicture/mySeigeBattle.png")
};

const qreal cardHorizontalDistance=0.07;//卡牌摆放时的水平距离

const QPointF SpecialCardPos=QPointF(0.8, 0.7);//特殊卡牌在发动时的位置

//----------------------------手牌部分---------------------------


const QPointF LeaderLeftTopPoint[2]={//领袖的左上方点的位置，0号位置在上方，1号位置在下方
    QPointF(0.259,0.0),
    QPointF(0.259,0.856)
};

const QPointF HandCardLeftTopPoint[2]={//手牌的左上方点的位置，0号位置在上方，1号位置在下方
    QPointF(0.33,0.0),
    QPointF(0.33,0.856)
};

const QSizeF HandCardSize=QSizeF(0.35,0.14);//手牌区的尺寸，其中宽度width指的其实是两张手牌直接最远的水平距离


//----------------------------墓地部分---------------------------
const QPointF GraveyardShowPos[2]=//墓地中卡牌数量显示区的位置和尺寸
{
    QPointF(0.79,0.035),
    QPointF(0.79,0.94)
};
const QSizeF GraveyardShowSize=QSizeF(0.02,0.027);
//----------------------------牌库部分---------------------------

const QPointF LibraryShowPos[2]=//牌库中卡牌数量显示区的位置和尺寸
{
    QPointF(0.93,0.035),
    QPointF(0.93,0.94)
};
const QSizeF LibraryShowSize=QSizeF(0.02,0.03);

//牌库图片
const QPointF LibararyPos[2]={QPointF(0.88,0.01),QPointF(0.88,0.873)};
const QSizeF LibararySize=QSizeF(0.06,0.11);

const QString LibraryImagePath=QString(":/img/ui/res/uiPicture/unknownCard.png");

//----------------------------卡牌部分---------------------------

const int NO_STRENGTH=-1;//特殊牌没有战斗力

//未知卡牌
const QString UnknownCardImagePath=QString(":/img/ui/res/uiPicture/unknownCard.png");
const QSizeF UnknownCardImageSize=QSizeF(0.06,0.11);

//卡牌的尺寸
const qreal cardWidth=0.08;
const qreal cardHeight=0.14;
const QSizeF CardSize=QSizeF(0.08, 0.14);

//卡牌的当前战斗力显示
const qreal CardStrengthOffsetX=0.03;
const qreal CardStrengthOffsetY=0.03;
const QSizeF CardStrengthSize=QSizeF(0.04, 0.03);

//卡组的护甲
const QSizeF CardArmorSize=QSizeF(0.07,0.03);
const qreal CardArmorOffsetX=0.01;
const qreal CardArmorOffsetY=0.06;

//卡组是否有护盾
const QSizeF CardShieldSize=QSizeF(0.07,0.03);
const qreal CardShieldOffsetX=0.01;
const qreal CardShieldOffsetY=0.09;


//以下数据未测量
const QPointF GraveyardPos[2]={QPointF(0,0), QPointF(0,0)};
const QSizeF GraveyardSize=QSizeF(0,0);


//-------------


//--------------------------构建牌组界面--------------------------------

const QString ModifyDeckImagePath=QString(":/img/ui/res/uiPicture/ModifyDeck.png");//修改卡组的界面图像路径

//卡牌总数量显示
const QPointF DeckTotalNumberPos=QPointF(0.06, 0.12);

//不同类型的卡牌数量显示
const QPointF DeckTitlePos[3]={
    QPointF(0.12, 0.27),
    QPointF(0.12,0.43),
    QPointF(0.12, 0.59)
};
const QSizeF DeckTitleSize=QSizeF(0.1, 0.2);

//不同类型的卡牌
const QPointF DeckCardPos[3]={
    QPointF(0.2,0.3),
    QPointF(0.2,0.46),
    QPointF(0.2, 0.63),
};
const QSizeF DeckCardSize=QSizeF(0.75, 0.2);

//保存按钮
const QPointF DeckSavePos=QPointF(0.6, 0.8);
const QSizeF DeckSaveSize=QSizeF(0.07, 0.05);
const QString SaveButtonImagePath=QString(":/img/ui/res/uiPicture/SaveButton.png");//保存按钮的图像路径

//退出按钮
const QPointF DeckExitPos=QPointF(0.8, 0.8);
const QSizeF DeckExitSize=QSizeF(0.07, 0.05);
const QString ExitButtonImagePath=QString(":/img/ui/res/uiPicture/ExitButton.png");//退出按钮的图像路径

//同类卡牌在卡组中的数量
const qreal AmountInDeckOffsetX=0.03;
const qreal AmountInDeckOffsetY=0.07;
const QSizeF AmountInDeckSize=QSizeF(0.02, 0.03);

//是否是卡组中的领袖
const QSizeF LeaderShowSize=QSizeF(0.04,0.03);
const qreal LeaderShowOffsetX=0.01;
const qreal LeaderShowOffsetY=0.09;


//----------------------------调度界面-------------------------------

const QString RedrawBackgroundImagePath=QString(":/img/ui/res/uiPicture/RedrawCards.png");//调度画面的图像路径
const QPointF RedrawCardsPos[5]=
{//调度卡牌的位置
    QPointF(0,0.3),
    QPointF(0.2,0.3),
    QPointF(0.4,0.3),
    QPointF(0.6,0.3),
    QPointF(0.8, 0.3)
};
const QSizeF RedrawCardsSize=QSizeF(0.2,0.4);//调度卡牌的大小

}

//定义了卡牌和战排的分类

namespace gwent {

    enum class STATUS             //卡牌的当前状态
    {
        DECK,               //在牌库中
        HAND,               //在手牌中
        BATTLE_FIELD,       //在战排上
        GRAVEYARD           //在墓地里
    };

    enum class RACE              //卡牌的种族
    {
        MONSTERS,           //怪物
        NEUTRAL,            //中立
        NILFGAARD,          //尼弗迦德
        NORTHERNRREALMS,    //北方领域
        SCOIATAEL           //松鼠党
    };

    enum class TYPE              //卡牌的等级类型
    {
        GOLD,               //金牌
        SILVER,             //银牌
        BRONZE              //铜牌
    };

    enum class COMBAT_ROW        //卡牌在战场上摆放的位置
    {
        ENEMY_SIEGE,        //敌方的工程排
        ENEMY_REMOTE,       //敌方的远战排
        ENEMY_CLOSE,        //敌方的近战排
        CLOSE,              //近战排
        REMOTE,             //远战排
        SIEGE,              //攻城排
        ANY,                 //任意排
        LEADER,               //首领
        NO_COMBATROW          //没有战排，对应于特殊卡

    };

    enum class CLIMATE           //战场排的天气效果
    {
        SUNNY,              //晴空
        FOG,                //蔽日浓雾
        FROST,              //刺骨冰霜
        RAIN                //倾盆大雨
    };

    enum class GameStatus   //游戏运行状态
    {
        UNSTARTED,          //还未开始
        PLAYING,            //正在进行中
        PAUSE,               //游戏暂停了
        OVER                //游戏结束了
    };

    const int NoWinner=-1;//打成平手

}

#endif // GEOGRAPHICALPARAMETER_H
