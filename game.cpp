#include "game.h"
#include "deck.h"
#include <QTimer>
#include "parameter.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QMutex>
#include <string>

Game::Game(long long gameId,  int userId0, int userId1,  QObject *parent) :
    QObject(parent), m_gameId(gameId)
{ 
    m_userId[0]=userId0;
    m_userId[1]=userId1;

    m_player[0]=Q_NULLPTR;
    m_player[1]=Q_NULLPTR;

    m_gameStatus=GameStatus::UNSTARTED;//初始时，游戏未开始
    for(int i=0; i<3; i++)
    {
      m_gameRoundStatus[i]=GameStatus::UNSTARTED;
    }
    winningTimes[ENEMY]=0;//两个玩家都没有赢过
    winningTimes[OURSIDE]=0;

    m_background=Q_NULLPTR;
    m_bigCardImage=Q_NULLPTR;
    m_cardName=Q_NULLPTR;
    m_cardDescription=Q_NULLPTR;
    m_passButton=Q_NULLPTR;
    m_leftTimeShow=Q_NULLPTR;
    m_turnShow=Q_NULLPTR;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    srand(time(NULL));//根据时间生成随机数种子,存疑

    m_isDispatching=false;//刚开始我方没有在发牌
    m_currentRound=0;//一开始的回合数是0
    m_shouldUpdateGame=true;//一开始应该不断去查询当前的游戏状态

}

Game::~Game()
{
    QFile::remove(GameFilePrefix+QString::number(m_gameId)+QString(".dat"));
}

void Game::playGameIn(int userId, GraphicsItem* background)//调用game的dialog的用户账号是userId，需要将game映射到background上
{
    //根据userId，来判断敌我方
    if(m_userId[0]==userId)
    {
        m_player[OURSIDE]=new Player(m_userId[0], this);
        m_player[ENEMY]=new Player(m_userId[1],this);
        m_enemyId=m_userId[1];
    }else if(m_userId[1]==userId)
    {
        m_player[OURSIDE]=new Player(m_userId[1], this);
        m_player[ENEMY]=new Player(m_userId[0],this);
        m_enemyId=m_userId[0];
    }else
    {
        return;
    }

    m_userIdOfDialog=userId;
    m_background=background;

    //玩家选择游戏背景
    m_player[OURSIDE]->chooseBackgroud(background,OURSIDE);
    m_player[ENEMY]->chooseBackgroud(background,ENEMY);

    //布置游戏背景上的
    //卡牌大图
    m_bigCardImage=new GraphicsItem(BigCardImagePos,BigCardImageSize, background);

    //卡牌名字
    m_cardName=new text(CardNamePos, CardNameSize, 16, Qt::black, QColor(122,122,0,100), background);
    m_cardName->setCenter();

    //卡牌描述
    m_cardDescription=new text(CardDescriptionPos, CardDescriptionSize,14, Qt::black, Qt::lightGray, background);
    m_cardDescription->setLeft();

    //放弃按钮
    m_passButton=new Button(PassButtonPos, PassButtonSize, PassButtonImagePath,background);
    connect(m_passButton,SIGNAL(buttonPressed()),this,SLOT(on_buttonPressed()));

    //剩余时间显示
    m_leftTimeShow=new text(LeftTimeShowPos, LeftTimeShowSize, background);
    m_leftTimeShow->setFontColor(Qt::yellow);
    m_leftTimeShow->setFontSize(23);
    m_leftTimeShow->setCenter();
    m_leftTimeShow->setText("");
    connect(m_player[OURSIDE]->getTimer(), SIGNAL(timeout()), this, SLOT(on_oneSecondGone()));

    //当前发牌玩家显示
    m_turnShow=new text(TurnShowPos, TurnShowSize, background);
    m_turnShow->setFontColor(Qt::white);
    m_turnShow->setFontSize(19);
    m_turnShow->setText("UNSTARTED");
    m_turnShow->setCenter();

    //上一轮结果的显示
    m_gameRoundResultShow=new text(GameRoundResultShowPos, GameRoundResultShowSize, background);
    m_gameRoundResultShow->setFontSize(28);
    m_gameRoundResultShow->setCenter();
    showGameRoundResult(false);//则显示当前局游戏的结果

    //当前是第几局
    m_gameRoundShow=new text(GameRoundShowPos, GameRoundShowSize, background);
    m_gameRoundShow->setFontSize(22);
    m_gameRoundShow->setFontColor(Qt::yellow);


}

void Game::setDeckId(int deckId1, int deckId2)//传入两个玩家选择的卡组编号
{
    m_deckId[0]=deckId1;
    m_deckId[1]=deckId2;

    //玩家选择牌组，该过程同时将牌组里的牌初始化到卡库汇总
    if(m_userId[0]==m_userIdOfDialog)
    {
        m_player[OURSIDE]->chooseDeck(m_deckId[0]);
        m_player[ENEMY]->chooseDeck(m_deckId[1]);
    }else if(m_userId[1]==m_userIdOfDialog)
    {
        m_player[OURSIDE]->chooseDeck(m_deckId[1]);
        m_player[ENEMY]->chooseDeck(m_deckId[0]);
    }else
    {
        return;
    }

    //连接玩家发牌结束的信号
    connect(m_player[OURSIDE], SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));
    connect(m_player[ENEMY], SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));

    //连接玩家卡库里的所有牌和游戏背景的交互（比如显示卡牌信息）
    connectCardHoverEvents();
}

void Game::setDeck(Deck* enemyDeck, Deck* ourDeck)
{
    m_player[OURSIDE]->setDeck(ourDeck);
    m_player[ENEMY]->setDeck(enemyDeck);

    //连接玩家发牌结束的信号
    connect(m_player[OURSIDE], SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));
    connect(m_player[ENEMY], SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));

    //连接玩家卡库里的所有牌和游戏背景的交互（比如显示卡牌信息）
    connectCardHoverEvents();

}

void Game::connectCardHoverEvents()
{
    for(int i=0; i<m_player[0]->library->getSize(); i++)
    {
        connect(m_player[0]->library->getNthCard(i), SIGNAL(cardHover(Card*)), this, SLOT(on_cardHover(Card*)));
    }
    for(int i=0; i<m_player[1]->library->getSize(); i++)
    {
        connect(m_player[1]->library->getNthCard(i),SIGNAL(cardHover(Card*)), this, SLOT(on_cardHover(Card*)));
    }
}

void Game::saveGame(const QString gameFile)
{
    QMutex mutex;
    mutex.lock();

    QFile file(GameFilePrefix+QString::number(m_gameId)+QString(".dat"));

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"error writing";
    }
    qDebug()<<"save game";
    QDataStream out(&file);
    out << *(this);
    file.close();
    mutex.unlock();

    m_shouldUpdateGame=true;
}

void Game::updateGame(const QString gameFile)
{
    QMutex mutex;
    mutex.lock();

    QFile file(GameFilePrefix+QString::number(m_gameId)+QString(".dat"));

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"error reading";
        return;
    }

    QDataStream in(&file);
    in>>(*this);

    file.close();
    mutex.unlock();
}


void Game::on_cardHover(Card *card)//对卡牌上方有鼠标悬浮事件作出响应
{
    if(card->isSeen())
    {
        m_bigCardImage->changeImagePath(QString::fromStdString(card->getImagePath()));
        m_cardName->setText(card->getName());
        m_cardDescription->setText(card->getDescription());
        m_bigCardImage->update();
        m_cardName->update();
        m_cardDescription->update();
    }
}

void Game::on_battleFieldPressed(COMBAT_ROW combatRow)//对战排点击事件作出响应
{

}


void Game::on_buttonPressed()//当pass按钮按下时
{
    if(m_isDispatching)
    {
        endDispatchingCard();
    }
    else
    {
        if(m_player[OURSIDE]->isOnTurn())//只有我方轮到出牌时，才能按pass按钮
        {
            qDebug()<<"We choose pass";

            m_player[OURSIDE]->choosePassed();
            m_player[OURSIDE]->loseTurn();
        }
    }

}

void Game::on_oneSecondGone()//当1s中过去时
{
    //更新时间显示
    updateTime();

    if(m_player[OURSIDE]->isOnTurn()
            ||m_player[OURSIDE]->getIsDispatchingCard()
            || !m_shouldUpdateGame)
        return;

    //qDebug()<<m_shouldUpdateGame;

    updateGame(GameFileName);//下载游戏进度

}

void Game::startGame()//玩家开始玩游戏
{
    m_shouldUpdateGame=false;

    m_player[OURSIDE]->shuffleCards();//洗牌
    m_player[OURSIDE]->drawInitCards();//抽牌
    enterDispatchingCard();//进入调度
}

void Game::enterDispatchingCard()//进入调度
{
    for(int i=1; i<m_player[OURSIDE]->getSize(); i++)//领袖不需要调度
    {
        m_player[OURSIDE]->getNthCard(i)->setIsDispatching(true);//每张卡都属于调度期
        connect(m_player[OURSIDE]->getNthCard(i), SIGNAL(cardDispatched(Card*)), m_player[OURSIDE], SLOT(dispatchCard(Card*)));
    }
    connect(m_player[OURSIDE], SIGNAL(endDispatchingCard()), this, SLOT(endDispatchingCard()));//时间到了，点击pass，调度了3张卡，都会引发结束调度
    m_player[OURSIDE]->setIsDispatchingCard(true);
    m_isDispatching=true;
}

void Game::endDispatchingCard()
{
    for(int i=1; i<m_player[OURSIDE]->getSize(); i++)//领袖不需要调用
    {
        m_player[OURSIDE]->getNthCard(i)->setIsDispatching(false);//每张卡都结束调度期
        disconnect(m_player[OURSIDE]->getNthCard(i), SIGNAL(cardDispatched(Card*)), m_player[OURSIDE], SLOT(dispatchCard(Card*)));
    }
    disconnect(m_player[OURSIDE], SIGNAL(endDispatchingCard()), this, SLOT(endDispatchingCard()));
    m_player[OURSIDE]->setIsDispatchingCard(false);
    m_isDispatching=false;

    //结束调度
    //m_shouldUpdateGame=true;

    updateRound();//更新当前的回合显示

    if(m_userIdOfDialog==m_userId[1])//由第二个玩家掷筛子来决定发牌顺序
    {
        m_gameStatus=GameStatus::PLAYING;
        decideOrderOfCards();
    }
    else//对于第一个玩家则需要上传游戏包，让第二个玩家进入调度
    {
        saveGame(GameFileName);
    }
}

void Game::decideOrderOfCards()//随机决定发牌顺序
{
    int rand=qrand()%2;

    if(rand==OURSIDE)
    {
        qDebug()<<"We first";
        m_player[OURSIDE]->getTurn();
        updateTime();
    }else if(rand==ENEMY)
    {
        qDebug()<<"Enemy first";
        saveGame(GameFileName);//另外一个玩家先发牌
    }else
    {
        qDebug()<<"Error";
    }
}

void Game::on_playerLoseTurn()//当当前选手结束发牌时
{
    //如果还不能判断游戏胜负
    bool roundOver=judgeOfGameRound();//判决游戏结果
    if(!roundOver)//如果当前一局没有结束
    {
        saveGame(GameFileName);//则轮到另外一方发牌
    }
    else//假如当前局结束
    {
        m_player[OURSIDE]->updateFinalStrength(m_currentRound);
        m_player[ENEMY]->updateFinalStrength(m_currentRound);//记录上一局的总分

        m_currentRound++;//当前局加一
        qDebug()<<"current round"<<QString::number(m_currentRound-1)<<"is over";
        updateRound();

        m_player[OURSIDE]->enterANewRound();//进入新的一轮,清空战排上的卡牌

        bool gameOver=judgeOfGame();//判断整场游戏是否结束
        if(gameOver)
        {
            m_gameStatus=GameStatus::OVER;
            stopGame();
            qDebug()<<"stop game before lose turn";
            saveGame(GameFileName);//上传游戏
        }
        saveGame(GameFileName);//上传游戏
    }
}

void Game::enterANewRound()//进入新的一回合
{
    qDebug()<<"enter a new round";

    //qDebug()<<"my siegebattle size "<<m_player[OURSIDE]->siegeBattle->getSize();
    //qDebug()<<"enemy siegebattle size"<<m_player[ENEMY]->siegeBattle->getSize();
    m_player[OURSIDE]->enterANewRound();//进入新的一轮,清空战排上的卡牌
    //m_player[ENEMY]->enterANewRound();

    if(m_lastWinner==m_userIdOfDialog)//上一局赢的玩家先开始发牌
    {
        showGameRoundResult(false);
        m_player[OURSIDE]->getTurn();
    }
    else if(m_lastWinner==m_enemyId)
    {
        saveGame(GameFileName);
    }
    else//平局情况下
    {
        int randNumber=rand()%2;//下随机生成一个上一局赢的玩家，以确定下一局开始的次序
        if(randNumber==0)
        {
            m_player[OURSIDE]->getTurn();
        }else
        {
            saveGame(GameFileName);
        }
    }
}

bool Game::judgeOfGameRound()//判断当前局是否分出胜负，已分出胜负则返回true
{
    if(m_player[ENEMY]->getHasChosenPassed() &&
            m_player[OURSIDE]->getHasChosenPassed())//如果两方都已pass
    {
        if((m_player[ENEMY]->getTotalStrength()) > (m_player[OURSIDE]->getTotalStrength()))
        {
            winningTimes[ENEMY]+=1;
            m_lastWinner=m_enemyId;
            qDebug()<<"You lose";
        }
        else if((m_player[ENEMY]->getTotalStrength()) < (m_player[OURSIDE]->getTotalStrength()))
        {
            winningTimes[OURSIDE]+=1;
            m_lastWinner=m_userIdOfDialog;
            qDebug()<<"You win";
        }
        else
        {
            m_lastWinner=NoWinner;//平局
            winningTimes[OURSIDE]+=1;
            winningTimes[ENEMY]+=1;
            qDebug()<<"In draw";
        }
        showGameRoundResult(true);
        qDebug()<<"judge of game round--show game round result";
        return true;
    }
    else//否则当前局继续
    {
        m_gameRoundStatus[m_currentRound]=GameStatus::PLAYING;
        return false;
    }
}

bool Game::judgeOfGame()//判断整场游戏是否分出胜负,分出返回true
{
    if(m_currentRound==3)
    qDebug()<<"User"<<m_userIdOfDialog<<"win"<<winningTimes[OURSIDE];
    if(winningTimes[OURSIDE]==2)
    {
        if(winningTimes[ENEMY]<2)
        {
            qDebug()<<"you win the whole game";
        }
        else
        {
            qDebug()<<"in draw the whole game";
        }
        m_gameStatus=GameStatus::OVER;
        return true;
    }
    else if(winningTimes[ENEMY]==2)
    {
        qDebug()<<"you lose the whole game";
        m_gameStatus=GameStatus::OVER;
        return true;
    }
    else
    {
        m_gameStatus=GameStatus::PLAYING;
        return false;
    }
}

void Game::stopGame()//停止游戏
{
    qDebug()<<"stop game";
    //m_player[OURSIDE]->loseTurn();

    showGameResult();
    //显示游戏结果的画面
}

void Game::updateTime()
{
    if(m_isDispatching)
    {
        m_turnShow->setText("Dispatching");
        m_leftTimeShow->setText(std::to_string(m_player[OURSIDE]->getLeftTime()));
    }
    else
    {
        if(m_player[OURSIDE]->isOnTurn())
        {
            m_turnShow->setText("YOUR TURN");
            m_leftTimeShow->setText(std::to_string(m_player[OURSIDE]->getLeftTime()));
        }else
        {
            m_turnShow->setText("OPPONENT TURN");
            m_leftTimeShow->setText("");
        }
    }
    this->m_turnShow->update();

    this->m_leftTimeShow->update();

}

void Game::updateRound()//显示当前局
{
    m_gameRoundShow->setText("Round:"+std::to_string(this->m_currentRound+1));
}

void Game::showGameRoundResult(bool show)
{
    if(show)
    {
        //显示上一局的结果
        if(m_lastWinner==m_userIdOfDialog)
        {
            m_gameRoundResultShow->setText("You win!");
            m_gameRoundResultShow->setFontColor(Qt::yellow);
        }else if(m_lastWinner==m_userIdOfDialog)
        {
            m_gameRoundResultShow->setText("You fail!");
            m_gameRoundResultShow->setFontColor(Qt::red);
        }else if(m_lastWinner==NoWinner)
        {
            m_gameRoundResultShow->setText("In draw");
        }else
        {
            m_gameRoundResultShow->setText("");
        }
        m_gameRoundResultShow->update();
    }
    else {
        m_gameRoundResultShow->setText("");
        m_gameRoundResultShow->update();
    }
    return;

}

void Game::showGameResult()
{
    m_background->changeImagePath(GameResultShowImagePath);
    m_background->setZValue(20);
    for(int i=0; i<m_background->childItems().size(); i++)
    {
        m_background->childItems().at(i)->hide();
    }
    //显示结果比分
    std::string result[2];
    result[OURSIDE]="Our score:";
    result[ENEMY]="Enemy's score:";
    for(int i=0; i<2; i++)
    {
        m_gameResultShow[i]=new text(GameResultShowPos[i], GameResultShowSize, m_background);
        m_gameResultShow[i]->setFontColor(Qt::yellow);
        m_gameResultShow[i]->setFontSize(30);

        for(int j=0; j<3; j++)
        {
            result[i]+=" ";
            result[i]+=(std::to_string(m_player[i]->m_finalStrength[j]));
        }
        m_gameResultShow[i]->setText(result[i]);
    }
}

QDataStream &operator<<(QDataStream &out, const Game &game)
{
    out << game.m_enemyId;//向对方发一个包，包的开头是对方的id

    out << *(game.m_player[OURSIDE]) << *(game.m_player[ENEMY]);

    out<<game.winningTimes[OURSIDE]<<game.winningTimes[ENEMY];

    out << game.m_lastWinner;//上传上一局赢的玩家

    out << game.m_currentRound;//发送当前回合

    out<<static_cast<int>(game.m_gameStatus);

    return out;

}

QDataStream &operator>>(QDataStream &in, Game &game)
{
    int destination;
    in >> destination;

    qDebug()<<"trying to read";

    if(game.m_userIdOfDialog==destination)//如果我方就是该包的目标，接受该包
    {
        game.m_shouldUpdateGame=false;//在我方保存游戏进度前，不再接受游戏数据包

        if(!game.m_player[ENEMY] || !game.m_player[OURSIDE])
        {
            qDebug()<<"error game player null";
            return in;
        }

        qDebug()<<"read game package";

        in >> *(game.m_player[ENEMY]) >> *(game.m_player[OURSIDE]);//输入玩家信息

        in >> game.winningTimes[ENEMY] >> game.winningTimes[OURSIDE];//输入两方赢的次数

        in >> game.m_lastWinner;//输入上一局赢的玩家

        int round;
        in >> round;//输入当前回合

        int gameStatus;
        in>>gameStatus;//输入当前游戏状态
        game.m_gameStatus=static_cast<GameStatus>(gameStatus);

        if(game.m_gameStatus==GameStatus::OVER)
        {
            game.stopGame();
            qDebug()<<"stop game by the game package";
            return in;
        }

        if(round>=3)
        {
            game.stopGame();
            qDebug()<<"stop game by the game package2";
            return in;

        }

        if(round>game.m_currentRound)//如果发现传过来的游戏进入了新的回合
        {
            qDebug()<<"find the round increase";
            game.m_currentRound=round;//我方也进入新的一轮
            game.updateRound();//更新回合显示
            game.enterANewRound();
            return in;
        }

        if(game.m_currentRound==0 && game.m_gameStatus==GameStatus::UNSTARTED)//如果游戏还没有开始
        {
            game.startGame();//那么我方开始游戏
        }
        else
        {
            game.showGameRoundResult(false);
            game.m_player[OURSIDE]->getTurn();//否则轮到我方出牌
        }

        return in;
    }//否则丢弃该包
    else
    {
        return in;
    }
}














