#ifndef CARDDATABASE_H
#define CARDDATABASE_H

#include <vector>

#include "card.h"
#include "battle.h"
#include "graphicsitem.h"
#include <vector>
#include "game.h"
using namespace gwent;

class CardDatabase//卡牌数据库，用来存储各种卡信息
{
private:
    //std::vector<Card *> cards;//卡族
    int m_size;
public:
    CardDatabase();
    ~CardDatabase();
    Card* getCardWithIdOfDatabase(int idOfDatabase) const;//返回m_idOfDatabase为idOfDatabase的卡牌
    int getSize()const {return m_size;}//返回的大小是能够加入卡组中的大小，衍生物统一没有算进大小里，但是同样可以通过衍生物的idOfDatabase找到衍生物
};

class CardDerived: public Card
{
public:
    CardDerived(const RACE race,
                const std::string name,
                const std::string imagePath,
                const std::string description,
                const int initStrenth, const TYPE initType,
                const COMBAT_ROW initCombatRow, const bool loyalty
                   );//一般卡的初始化

    CardDerived(const RACE race,
         const std::string name,
         const std::string imagePath,
         const std::string description,
         const TYPE initType);//特殊卡的初始化（没有战斗力和站位）
    virtual void on_handToBattleField(COMBAT_ROW combatRow);
    virtual void battleFieldToGraveyard();
    virtual void on_changeStatusByWeather(CLIMATE climate,BattleField* battleField){}//由于某种天气效果，进入战排或离开战排
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void showSpecialCard();//展现特殊卡
    void setGame(Game *game);//设置游戏指针
};

class CardDagon: public CardDerived
{
public:
    CardDagon();
    void on_handToBattleField(COMBAT_ROW combatRow);
};

class CardFoglet: public CardDerived
{
public:
    CardFoglet();
    void on_changeStatusByWeather(CLIMATE climate, BattleField *battleField);
    void on_addToLibrary();
private:
    bool m_callByWeather;//打到战排上的方式，0代表从牌组中打出，1代表通过天气召唤出
};

class CardGeels: public CardDerived
{
public:
    CardGeels();
    void on_handToBattleField(COMBAT_ROW combatRow);
};

class CardCelaenoHarpy: public CardDerived
{
public:
    CardCelaenoHarpy();
    void on_handToBattleField(COMBAT_ROW combatRow);
};

class CardWoodlandSpirit:public CardDerived
{
public:
    CardWoodlandSpirit();
    void on_handToBattleField(COMBAT_ROW);
};

class CardEarthElemental:public CardDerived
{
public:
    CardEarthElemental();
    void on_handToBattleField(COMBAT_ROW);
    void battleFieldToGraveyard();
};

class CardCroneWeavess:public CardDerived
{
public:
    CardCroneWeavess();
    void on_handToBattleField(COMBAT_ROW);
};

class CardCroneWhispess:public CardDerived
{
public:
    CardCroneWhispess();
    void on_handToBattleField(COMBAT_ROW);
};

class CardCroneBrewess:public CardDerived
{
public:
    CardCroneBrewess();
    void on_handToBattleField(COMBAT_ROW);
};

class CardArchgriffin:public CardDerived
{
public:
    CardArchgriffin();
    void on_handToBattleField(COMBAT_ROW);
};

class CardCaranthir:public CardDerived
{
public:
    CardCaranthir();
    void on_handToBattleField(COMBAT_ROW);
    void on_CardPressed(Card *card);
    void on_playerLoseTurn();
private:
    int pressCount=0;
    BattleField* finalBattle;
};

class CardFrighterner: public CardDerived
{
public:
    CardFrighterner();
    void on_handToBattleField(COMBAT_ROW);
    void on_CardPressed(Card *card);//当点击了其他一张卡时，将该卡加入畏惧者的同一排
    void on_playerLoseTurn();
};

class CardUnseenElder:public CardDerived
{
public:
    CardUnseenElder();
    void on_handToBattleField(COMBAT_ROW);
    void swallow(Card* card);
    void on_playerLoseTurn();

private:
    int foodCount=0;
};

class CardArachas:public CardDerived
{
public:
    CardArachas();
    void on_handToBattleField(COMBAT_ROW);
};

class CardVranWarrior:public CardDerived
{
public:
    CardVranWarrior();
    void on_handToBattleField(COMBAT_ROW combatRow);
    void on_playerGetTurn();//当我方选手轮到出牌时响应
    void swallow(Card *food);
private:
    bool shouldSwallow=true;//用来判断该回合是否应该吞噬右侧单位
};

class CardWildHuntRider:public CardDerived
{
public:
    CardWildHuntRider();
    void on_handToBattleField(COMBAT_ROW combatRow);
};

class CardArachasBehemoth:public CardDerived
{
public:
    CardArachasBehemoth();
    void on_handToBattleField(COMBAT_ROW combatRow);
    void produce();
};

class CardFirstLight: public CardDerived
{
public:
    CardFirstLight();
    void on_handToBattleField(COMBAT_ROW combatRow);
    void on_battlePressed(BattleField *battleField);
    void on_libraryPressed();
    void on_playerLoseTurn();
};

class CardBitingFrost: public CardDerived
{
public:
    CardBitingFrost();
    void on_handToBattleField(COMBAT_ROW combatRow);
    void changeWeather(BattleField *battleField);
    void on_playerLoseTurn();
};

class CardImpenetrableFog: public CardDerived
{
public:
    CardImpenetrableFog();
    void on_handToBattleField(COMBAT_ROW combatRow);
    void changeWeather(BattleField *battleField);
    void on_playerLoseTurn();
};

class CardTorrentialRain: public CardDerived
{
public:
    CardTorrentialRain();
    void on_handToBattleField(COMBAT_ROW combatRow);
    void changeWeather(BattleField *battleField);
    void on_playerLoseTurn();

};

class CardLacerate: public CardDerived
{
public:
    CardLacerate();
    void on_handToBattleField(COMBAT_ROW);
    void on_battlePressed(BattleField *battleField);
    void on_playerLoseTurn();

};

class CardCommandersHorn: public CardDerived
{
public:
    CardCommandersHorn();
    void on_handToBattleField(COMBAT_ROW);
    void on_battlePressed(BattleField *battleField);
    void on_playerLoseTurn();

};

class CardBekkersTwistedMirror: public CardDerived
{
public:
    CardBekkersTwistedMirror();
    void on_handToBattleField(COMBAT_ROW combatRow);
};

class CardGeraltIgni :public CardDerived
{
public:
    CardGeraltIgni();
    void on_handToBattleField(COMBAT_ROW);
};

class CardThunderboltPotion: public CardDerived
{
public:
    CardThunderboltPotion();
    void on_handToBattleField(COMBAT_ROW combatRow);
    void on_CardPressed(Card *card);
    void on_playerLoseTurn();

};

class CardRoach: public CardDerived
{
public:
    CardRoach();
    void on_handToBattleField(COMBAT_ROW combatRow);
    void on_addToLibrary();
};

class CardHarpyEgg: public CardDerived
{
public:
    CardHarpyEgg();
    void beforeBeSwallowed();
};

class CardRabidWolf:public CardDerived
{
public:
    CardRabidWolf();

};

class CardLesserEarthElemental:public CardDerived
{
public:
    CardLesserEarthElemental();
};




#endif // CARDDATABASE_H
