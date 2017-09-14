#include "carddatabase.h"
#include <QDebug>
#include "player.h"
#include "game.h"
#include "battle.h"
#include <QCursor>
/*
 CardDatabase::CardDatabase()
 {
 int i=0;
 Game *databaseGame=(Game *)Q_NULLPTR;
 //战排和卡片需要分别按照卡片id的顺序加入，如果不按照顺序加入，记得重新排序
 Card *card=new Card(RACE::MONSTERS,"Dagon",":/img/card/res/cardPicture/Dagon.png",
 "部署：生成“刺骨冰霜”、“蔽日浓雾”或“倾盆大雨”",6,TYPE::GOLD,COMBAT_ROW::LEADER,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS,"Foglet",":/img/card/res/cardPicture/Foglet.png",
 "每当己方“蔽日浓雾”在敌排生效，便从牌组打出，或复活至己方同排。若场上不再存在“蔽日浓雾”效果，则被摧毁。",
 2, TYPE::BRONZE, COMBAT_ROW::ANY,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Ge'els",":/img/card/res/cardPicture/Ge'els.png",
 "部署：从牌组顶端各抽1张金色牌和银色牌。打出1张，将另1张置于牌组顶端。",
 2,TYPE::GOLD, COMBAT_ROW::ANY, true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Celaeno_Harpy", ":/img/card/res/cardPicture/Celaeno_Harpy .png",
 "部署：在自身左侧生成2个“鹰身女妖蛋”。",
 3,TYPE::BRONZE,COMBAT_ROW::ANY,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Woodland_Spirit",":/img/card/res/cardPicture/Woodland Spirit.png",
 "部署：生成3只“暴怒的狼”，并在对方同排降下“蔽日浓雾”。",
 5,TYPE::GOLD,COMBAT_ROW::ANY,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS,"Earth_Elemental",":/img/card/res/cardPicture/Earth_Elemental.png",
 "部署：获得护盾。遗愿：在该排末位生成2个“次级土元素”。",
 6, TYPE::BRONZE, COMBAT_ROW::CLOSE,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Crone:_Weavess",":/img/card/res/cardPicture/Crone_Weavess.png",
 "部署：从牌组打出“煮婆”和“呢喃婆”。",
 6,TYPE::SILVER,COMBAT_ROW::SIEGE,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Crone:_Whispess",":/img/card/res/cardPicture/Crone_Whispess.png",
 "部署：从牌组打出“煮婆”和“织婆”。",
 6,TYPE::SILVER,COMBAT_ROW::SIEGE,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Crone:_Brewess",":/img/card/res/cardPicture/Crone_Brewess.png",
 "部署：从牌组打出“呢喃婆”和“织婆”。",
 8,TYPE::SILVER, COMBAT_ROW::SIEGE, true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS,"Archgriffin",":/img/card/res/cardPicture/Archgriffin.png",
 "部署：移除所在排的天气效果。",
 7, TYPE::BRONZE, COMBAT_ROW::ANY, true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Caranthir",":/img/card/res/cardPicture/Caranthir.png",
 "部署：将3个敌军单位移至对方同排，并在此排降下“刺骨冰霜”。",
 9,TYPE::GOLD,COMBAT_ROW::ANY, true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Frightener",":/img/card/res/cardPicture/Frightener.png",
 "部署：从牌组顶端抽1张牌。将所在战场其他排的1个单位移至自身的同一排。",
 10,TYPE::SILVER,COMBAT_ROW::ANY,false);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Unseen_Elder",":/img/card/res/cardPicture/Unseen Elder.png",
 "部署：吞噬3个友军单位，吸收它们的战力为自身的基础战力。",
 5,TYPE::GOLD,COMBAT_ROW::LEADER,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS,"Arachas",":/img/card/res/cardPicture/Arachas.png",
 "部署：从牌组打出所有“蟹蜘蛛”。",
 3,TYPE::BRONZE,COMBAT_ROW::REMOTE,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS,"Vran_Warrior",":/img/card/res/cardPicture/Vran_Warrior.png",
 "部署：吞噬右侧单位。每2回合，己方回合开始时，吞噬右侧单位。",
 5,TYPE::BRONZE,COMBAT_ROW::ANY, true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS,"Wild_Hunt_Rider",":/img/card/res/cardPicture/Wild_Hunt_Rider.png",
 "使对方此排的“刺骨冰霜”伤害提高 1 点。",
 8,TYPE::BRONZE, COMBAT_ROW::ANY, true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::MONSTERS, "Arachas_Behemoth",":/img/card/res/cardPicture/Arachas_Behemoth.png",
 "每当有友军单位吞噬1张牌，便生成1只“蟹蜘蛛”，随后受到1点伤害（无视护甲）。部署：获得2点护甲。",
 6, TYPE::BRONZE, COMBAT_ROW::SIEGE,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL,"First_Light",":/img/card/res/cardPicture/First_Light.png",
 "生成“晴空”或“调遣”。",
 TYPE::BRONZE);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL, "Biting_Frost",":/img/card/res/cardPicture/Biting_Frost.png",
 "在对方单排降下“刺骨冰霜”。刺骨冰霜：每当己方回合开始时，对所在排最弱的单个单位造成2点伤害",
 TYPE::BRONZE);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL,"Impenetrable_Fog",":/img/card/res/cardPicture/Impenetrable_Fog.png",
 "在对方单排降下“蔽日浓雾”。蔽日浓雾：每当己方回合开始时，对所在排最强的单位造成2点伤害。",
 TYPE::BRONZE);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL,"Torrential_Rain",":/img/card/res/cardPicture/Torrential_Rain.png",
 "在对方单排降下“倾盆大雨”。倾盆大雨：每当己方回合开始时，对所在排最多5个最弱的单位造成1点伤害。",
 TYPE::BRONZE);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL, "Lacerate",":/img/card/res/cardPicture/Lacerate.png",
 "对单排所有单位造成3点伤害。",
 TYPE::BRONZE);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL,"Commander's_Horn",":/img/card/res/cardPicture/Commander's_Horn.png",
 "使5个相邻单位获得4点增益。",
 TYPE::SILVER);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL,"Bekker's_Twisted_Mirror",":/img/card/res/cardPicture/Bekker's_Twisted_Mirror.png",
 "将最强和最弱单位的战力互换",
 TYPE::SILVER);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL,"Geralt:_Igni",":/img/card/res/cardPicture/Geralt_Igni.png",
 "部署：若对方同排总战力不低于20，则摧毁其上所有最强的单位。",
 4,TYPE::GOLD,COMBAT_ROW::ANY,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL,"Thunderbolt_Potion",":/img/card/res/cardPicture/Thunderbolt_Potion.png",
 "使 3 个相邻单位获得 2 点护甲和 3 点增益。",
 TYPE::BRONZE);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 card=new Card(RACE::NEUTRAL,"Roach",":/img/card/res/cardPicture/Roach.png",
 "己方每次从手牌打出金色牌时（领袖牌除外），便将牌组中的“萝卜”在其能力结算之前召唤至随机位置。",
 4,TYPE::BRONZE,COMBAT_ROW::ANY,true);
 card->setIdOfDatabase(i++);
 cards.push_back(card);
 
 
 }*/

CardDatabase::CardDatabase()
{/*
  int i=0;
  Card *cardDagon=new CardDagon();
  cardDagon->setIdOfDatabase(i++);
  cards.push_back(cardDagon);
  
  Card *cardFoglet=new CardFoglet();
  cardFoglet->setIdOfDatabase(i++);
  cards.push_back(cardFoglet);
  
  Card *cardGeels=new CardGeels();
  cardGeels->setIdOfDatabase(i++);
  cards.push_back(cardGeels);
  
  Card *cardCelaenoHarpy=new CardCelaenoHarpy();
  cardCelaenoHarpy->setIdOfDatabase(i++);
  cards.push_back(cardCelaenoHarpy);
  
  Card *cardWoodlandSpirit=new CardWoodlandSpirit();
  cardWoodlandSpirit->setIdOfDatabase(i++);
  cards.push_back(cardWoodlandSpirit);
  
  Card *cardEarthElemental=new CardEarthElemental();
  cardEarthElemental->setIdOfDatabase(i++);
  cards.push_back(cardEarthElemental);
  
  Card *cardCroneWeavess=new CardCroneWeavess();
  cardCroneWeavess->setIdOfDatabase(i++);
  cards.push_back(cardCroneWeavess);
  
  Card *cardCroneWhispess=new CardCroneWhispess();
  cardCroneWhispess->setIdOfDatabase(i++);
  cards.push_back(cardCroneWhispess);
  
  Card *cardCroneBrewess=new CardCroneBrewess();
  cardCroneBrewess->setIdOfDatabase(i++);
  cards.push_back(cardCroneBrewess);
  
  Card *cardArchgriffin=new CardArchgriffin();
  cardArchgriffin->setIdOfDatabase(i++);
  cards.push_back(cardArchgriffin);
  
  Card *cardCaranthir=new CardCaranthir();
  cardCaranthir->setIdOfDatabase(i++);
  cards.push_back(cardCaranthir);
  
  Card *cardFrighterner=new CardFrighterner();
  cardFrighterner->setIdOfDatabase(i++);
  cards.push_back(cardFrighterner);
  
  Card *cardUnseenElder=new CardUnseenElder();
  cardUnseenElder->setIdOfDatabase(i++);
  cards.push_back(cardUnseenElder);
  
  Card *cardArachas=new CardArachas();
  cardArachas->setIdOfDatabase(i++);
  cards.push_back(cardArachas);
  
  Card *cardVranWarrior=new CardVranWarrior();
  cardVranWarrior->setIdOfDatabase(i++);
  cards.push_back(cardVranWarrior);
  
  Card *cardWildHuntRider=new CardWildHuntRider();
  cardWildHuntRider->setIdOfDatabase(i++);
  cards.push_back(cardWildHuntRider);
  
  Card *cardArachasBehemoth=new CardArachasBehemoth();
  cardArachasBehemoth->setIdOfDatabase(i++);
  cards.push_back(cardArachasBehemoth);
  
  Card *cardFirstLight=new CardFirstLight();
  cardFirstLight->setIdOfDatabase(i++);
  cards.push_back(cardFirstLight);
  
  Card *cardBitingFrost=new CardBitingFrost();
  cardBitingFrost->setIdOfDatabase(i++);
  cards.push_back(cardBitingFrost);
  
  Card *cardImpenetrableFog=new CardImpenetrableFog();
  cardImpenetrableFog->setIdOfDatabase(i++);
  cards.push_back(cardImpenetrableFog);
  
  Card *cardTorrentialRain=new CardTorrentialRain();
  cardTorrentialRain->setIdOfDatabase(i++);
  cards.push_back(cardTorrentialRain);
  
  Card *cardLacerate=new CardLacerate();
  cardLacerate->setIdOfDatabase(i++);
  cards.push_back(cardLacerate);
  
  Card *cardCommandersHorn=new CardCommandersHorn();
  cardCommandersHorn->setIdOfDatabase(i++);
  cards.push_back(cardCommandersHorn);
  
  Card *cardBekkersTwistedMirror=new CardBekkersTwistedMirror();
  cardBekkersTwistedMirror->setIdOfDatabase(i++);
  cards.push_back(cardBekkersTwistedMirror);
  
  Card *cardGeraltIgni=new CardGeraltIgni();
  cardGeraltIgni->setIdOfDatabase(i++);
  cards.push_back(cardGeraltIgni);
  
  Card *cardThunderboltPotion=new CardThunderboltPotion();
  cardThunderboltPotion->setIdOfDatabase(i++);
  cards.push_back(cardThunderboltPotion);
  
  Card *cardRoach=new CardRoach();
  cardRoach->setIdOfDatabase(i++);
  cards.push_back(cardRoach);*/
    m_size=27;
}

CardDatabase::~CardDatabase()
{/*
  for(auto &i : cards)
  {
  if(i)
  delete i;
  }*/
}

Card* CardDatabase::getCardWithIdOfDatabase(int idOfDatabase) const
{
    switch (idOfDatabase) {
        case 0:
            return new CardDagon();
        case 1:
            return new CardFoglet();
        case 2:
            return new CardGeels();
        case 3:
            return new CardCelaenoHarpy();
        case 4:
            return new CardWoodlandSpirit();
        case 5:
            return new CardEarthElemental();
        case 6:
            return new CardCroneWeavess();
        case 7:
            return new CardCroneWhispess();
        case 8:
            return new CardCroneBrewess();
        case 9:
            return new CardArchgriffin();
        case 10:
            return new CardCaranthir();
        case 11:
            return new CardFrighterner();
        case 12:
            return new CardUnseenElder();
        case 13:
            return new CardArachas();
        case 14:
            return new CardVranWarrior();
        case 15:
            return new CardWildHuntRider();
        case 16:
            return new CardArachasBehemoth();
        case 17:
            return new CardFirstLight();
        case 18:
            return new CardBitingFrost();
        case 19:
            return new CardImpenetrableFog();
        case 20:
            return new CardTorrentialRain();
        case 21:
            return new CardLacerate();
        case 22:
            return new CardCommandersHorn();
        case 23:
            return new CardBekkersTwistedMirror();
        case 24:
            return new CardGeraltIgni();
        case 25:
            return new CardThunderboltPotion();
        case 26:
            return new CardRoach();
        case 27:
            return new CardHarpyEgg();
        case 28:
            return new CardRabidWolf();
        case 29:
            return new CardLesserEarthElemental();
    }
}


//------------------------卡牌类的派生类，作为具体卡牌的基类-------------------------

CardDerived::CardDerived(const RACE race,//一般卡的初始化
                         const std::string name,
                         const std::string imagePath,
                         const std::string description,
                         const int initStrenth, const TYPE initType,
                         const COMBAT_ROW initCombatRow, const bool loyalty):
Card(race, name, imagePath,description, initStrenth, initType, initCombatRow, loyalty)
{
}

CardDerived::CardDerived(const RACE race,//特殊卡的初始化（没有战斗力和站位）
                         const std::string name,
                         const std::string imagePath,
                         const std::string description,
                         const TYPE initType):
Card( race, name, imagePath, description, initType)
{
}

//----------------------卡牌响应位置的改变----------------------------

void CardDerived::on_handToBattleField(COMBAT_ROW combatRow)//从手牌进入战场
{
    if(!m_game)
        return;
    emit handToBattleField(combatRow, this);//对于普通卡牌而言，从手牌进入战场后，只需要向外界发送一个信号即可
    this->m_oursizePlayer->loseTurn();//然后我方选手就失去回合了（但是有些卡牌还需要等待用户的输入才能结束回合，通过虚函数的多态机制实现）
}

void CardDerived::battleFieldToGraveyard()//从战场进入墓地
{
    if(!m_game)
        return;
    this->m_oursizePlayer->getBattle(this->getActualCombatRow())->removeCard(this);//一般卡牌直接从战场进入墓地即可，如果卡牌有遗愿则需要重载
    this->m_oursizePlayer->graveyard->addCard(this);
    qDebug()<<QString::fromStdString(this->getName())<<"to battlefield";
}

void CardDerived::mouseMoveEvent(QGraphicsSceneMouseEvent *event)//鼠标移动时
{
    if(!m_game)
        return;

    if(m_isDispatching)
    {
        return;//调度环节不响应其他信号
    }
    
    if(this->m_oursizePlayer->isOnTurn())//只有在我方选手轮到发牌时才响应
    {
        QGraphicsItem::mouseMoveEvent(event);
        setCursor(Qt::ClosedHandCursor);
        update();
        qreal left=(this->boundingRect().x()+this->pos().x()-this->parentItem()->x())/this->parentItem()->boundingRect().width();
        qreal top=(this->boundingRect().y()+this->pos().y()-this->parentItem()->y())/this->parentItem()->boundingRect().height();
        emit cardMoveBy(getCenterPoint(left, top),this);//发送此时卡牌中心点的位置
    }
    
}

void CardDerived::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)//鼠标双击可以直接发动站位确定的卡和没有站位的卡
{
    if(!m_game)
        return;

    if(m_isDispatching)//调度环节不响应其他信号
    {
        emit cardDispatched(this);
        return;
    }

    emit cardPressed(this);
    
    qDebug()<<"mouse double clicked outside handcard";
    

    
    if(this->m_oursizePlayer->isOnTurn())//如果我方选手在出牌阶段
    {
        if(this->m_status==STATUS::HAND)//如果这张被点击的卡是手牌
        {
            qDebug()<<"mouse double clicked in handcard";
            
            if(this->m_initCombatRow==COMBAT_ROW::NO_COMBATROW||//如果卡牌没有站位，
               this->m_initCombatRow==COMBAT_ROW::CLOSE||//或者站位确定
               this->m_initCombatRow==COMBAT_ROW::SIEGE||
               this->m_initCombatRow==COMBAT_ROW::REMOTE)
            {
                this->m_oursizePlayer->addCardFromHandToBattle(this, m_initCombatRow);//则发动这张卡
                return;
            }
        }
    }
}

void CardDerived::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)//释放鼠标时
{
    //emit cardPressed(this);
    
    if(m_isDispatching)
    {
        return;//调度环节不响应
    }

    qDebug()<<"mouse release";
    
    setCursor(Qt::OpenHandCursor);
    update();//重新绘制
    
    if(!m_game)
        return;
    
    if(this->m_oursizePlayer->isOnTurn())//如果我方选手在出牌
    {
        if(this->m_status==STATUS::HAND)//如果这种牌是手牌
        {
            /*
            qDebug()<<"mouse release";
            if(this->m_initCombatRow==COMBAT_ROW::NO_COMBATROW||//如果卡牌没有站位，
               this->m_initCombatRow==COMBAT_ROW::CLOSE||//或者站位确定
               this->m_initCombatRow==COMBAT_ROW::SIEGE||
               this->m_initCombatRow==COMBAT_ROW::REMOTE)
            {
                this->m_oursizePlayer->addCardFromHandToBattle(this, m_initCombatRow);//则发动这张卡
                return;
            }
            */
            //否则发送此时的位置，由
            qreal left=(this->boundingRect().x()+this->pos().x()-this->parentItem()->x())/this->parentItem()->boundingRect().width();
            qreal top=(this->boundingRect().y()+this->pos().y()-this->parentItem()->y())/this->parentItem()->boundingRect().height();
            
            this->m_oursizePlayer->on_cardReleaseAt(getCenterPoint(left,top),this);
            //emit cardReleaseAt(getCenterPoint(left,top),this);//发送此时卡牌中心点的位置
        }
    }
    this->setPos(0,0);//卡牌回到自身坐标系的原点
}

void CardDerived::showSpecialCard()//表现特殊卡的使用路径， 同时将其从手牌移动到墓地，note：这个方法已经弃用
{
    if(m_game)
    {
        qDebug()<<"show special card";
        this->m_oursizePlayer->handCard->removeCard(this);
        //特效，待加
        this->m_oursizePlayer->graveyard->addCard(this);
    }
}

void CardDerived::setGame(Game* game){//设置当前卡牌是在哪场游戏中，之后就可以调用游戏指针和敌我方玩家的指针
    if(game)
    {
        m_game=game;
        setOursidePlayer(m_game->getPlayer(OURSIDE));
        setEnemyPlayer(m_game->getPlayer(ENEMY));
    }
}


//------------------------------------具体的卡牌类------------------------------------------

//------------------------达冈-------------------------------------------------------------

CardDagon::CardDagon():
CardDerived(RACE::MONSTERS,"Dagon",":/img/card/res/cardPicture/Dagon.png",
            "部署：生成“刺骨冰霜”、“蔽日浓雾”或“倾盆大雨”",6,TYPE::GOLD,COMBAT_ROW::LEADER,true)
{
    m_idOfDatabase=0;
}

void CardDagon::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    int randNumber=qrand()%3;
    Card* newCard;
    switch (randNumber) {
        case 0:
            newCard=new CardBitingFrost();
            break;
        case 1:
            newCard=new CardImpenetrableFog();
            break;
        case 2:
            newCard=new CardTorrentialRain();
            break;
    }
    qDebug()<<"create"<<QString::fromStdString(newCard->getName());
    this->m_oursizePlayer->createCard(newCard);
    this->m_oursizePlayer->addCardFromHandToBattle(newCard, COMBAT_ROW::NO_COMBATROW);
    
    emit handToBattleField(combatRow,this);//发送发动卡牌的信号
    this->m_oursizePlayer->loseTurn();//然后玩家失去回合
}

//------------------------小雾妖-------------------------------------------------------------

CardFoglet::CardFoglet():
CardDerived(RACE::MONSTERS,"Foglet",":/img/card/res/cardPicture/Foglet.png",
            "每当己方“蔽日浓雾”在敌排生效，便从牌组打出，或复活至己方同排。若场上不再存在“蔽日浓雾”效果，则被摧毁。",
            2, TYPE::BRONZE, COMBAT_ROW::ANY,true)
{
    m_idOfDatabase=1;
    m_callByWeather=false;
    connect(this, SIGNAL(addToLibrary()), this, SLOT(on_addToLibrary()));
}

void CardFoglet::on_addToLibrary()//加入牌库时，说明此时游戏和玩家都已经存在了，则将敌方排的天气信号和小雾妖连接起来
{
    if(!m_game)
        return;
    qDebug()<<"foglet add to library";
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE), SIGNAL(changeClimate(CLIMATE,BattleField*)), this, SLOT(on_changeStatusByWeather(CLIMATE,BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE), SIGNAL(changeClimate(CLIMATE,BattleField*)), this, SLOT(on_changeStatusByWeather(CLIMATE,BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE), SIGNAL(changeClimate(CLIMATE,BattleField*)), this, SLOT(on_changeStatusByWeather(CLIMATE,BattleField*)));
}

void CardFoglet::on_changeStatusByWeather(CLIMATE climate, BattleField *battleField)//climate是敌方战排battleField的天气
{
    if(!m_game)
        return;
    
    if(climate==CLIMATE::FOG)//假如敌方某一排天气是雾
    {
        qDebug()<<"call by weather";
        switch (this->m_status) {
            case STATUS::DECK:
                this->m_oursizePlayer->library->removeCard(this);
                this->m_oursizePlayer->getBattle(battleField->getType())->addCard(this);//则从牌库
                this->m_callByWeather=true;
                break;
            case STATUS::GRAVEYARD:
                this->m_oursizePlayer->graveyard->removeCard(this);
                this->m_oursizePlayer->getBattle(battleField->getType())->addCard(this);//或者墓地召唤卡牌到相应排
                this->m_callByWeather=true;
                break;
            default://其他情况则不召唤
                break;
        }
    }
    else if(m_callByWeather && climate==CLIMATE::SUNNY)//只有当小雾妖是有天气召唤出来的情况下，
    {
        if(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE)->getClimate()!=CLIMATE::FOG &&
           this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE)->getClimate()!=CLIMATE::FOG &&
           this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE)->getClimate()!=CLIMATE::FOG)//当敌方不存在雾
        {
            this->m_oursizePlayer->getBattle(this->getActualCombatRow())->removeCard(this);
            this->m_oursizePlayer->graveyard->addCard(this);//则将该卡送回墓地
        }
    }
}


//------------------------盖尔-------------------------------------------------------------

CardGeels::CardGeels():
CardDerived(RACE::MONSTERS, "Ge'els",":/img/card/res/cardPicture/Ge'els.png",
            "部署：从牌组顶端各抽1张金色牌和银色牌。打出1张，将另1张置于牌组顶端。",
            2,TYPE::GOLD, COMBAT_ROW::ANY, true)
{
    m_idOfDatabase=2;
}

void CardGeels::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    Card* goldCard=this->m_oursizePlayer->library->getCardOfType(TYPE::GOLD);//找到牌库最顶端的金卡
    Card* silverCard=this->m_oursizePlayer->library->getCardOfType(TYPE::SILVER);//和银卡
    //此处的策略是将金卡放回牌库顶端，银卡打在战排上，之后可以进一步改进
    if(silverCard){
        if(this->getInitCombatRow()==COMBAT_ROW::ANY)
        {
            this->m_oursizePlayer->getBattle(combatRow)->addCard(silverCard);
        }else
        {
            this->m_oursizePlayer->getBattle(this->getInitCombatRow())->addCard(silverCard);
        }
    }
    if(goldCard){
        this->m_oursizePlayer->library->addCard(goldCard);
    }
    
    this->m_oursizePlayer->loseTurn();//然后我方玩家就失去回合了
}

//------------------------赛尔伊诺鹰身女妖-------------------------------------------------------------

CardCelaenoHarpy::CardCelaenoHarpy():
CardDerived(RACE::MONSTERS, "Celaeno_Harpy", ":/img/card/res/cardPicture/Celaeno_Harpy .png",
            "部署：在自身左侧生成2个“鹰身女妖蛋”。",
            3,TYPE::BRONZE,COMBAT_ROW::ANY,true)
{
    m_idOfDatabase=3;
}

void CardCelaenoHarpy::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    Card* cardHarpyEgg[2];
    for(int i=0; i<2; i++)//在自身左侧生成两个蛋
    {
        cardHarpyEgg[i]=new CardHarpyEgg();
        this->m_oursizePlayer->createCard(cardHarpyEgg[i]);
        this->m_oursizePlayer->getBattle(combatRow)->insert(this,cardHarpyEgg[i]);
    }
    
    this->m_oursizePlayer->loseTurn();
}

//------------------------林精-------------------------------------------------------------

CardWoodlandSpirit::CardWoodlandSpirit():
CardDerived(RACE::MONSTERS, "Woodland_Spirit",":/img/card/res/cardPicture/Woodland Spirit.png",
            "部署：生成3只“暴怒的狼”，并在对方同排降下“蔽日浓雾”。",
            5,TYPE::GOLD,COMBAT_ROW::ANY,true)
{
    m_idOfDatabase=4;
    
}

void CardWoodlandSpirit::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    //在自身右侧生成3只暴怒的狼
    Card *cardRabidWolf[3];
    for(int i=0; i<3; i++)
    {
        cardRabidWolf[i]=new CardRabidWolf();
        this->m_oursizePlayer->createCard(cardRabidWolf[i]);
        this->m_oursizePlayer->getBattle(cardRabidWolf[i]->getInitCombatRow())->addCard(cardRabidWolf[i]);
    }
    
    this->m_enemyPlayer->getBattle(combatRow)->changeClimate(CLIMATE::FOG);

    this->m_oursizePlayer->loseTurn();
}

//------------------------土元素-------------------------------------------------------------

CardEarthElemental::CardEarthElemental():
CardDerived(RACE::MONSTERS,"Earth_Elemental",":/img/card/res/cardPicture/Earth_Elemental.png",
            "部署：获得护盾。遗愿：在该排末位生成2个“次级土元素”。",
            6, TYPE::BRONZE, COMBAT_ROW::CLOSE,true)
{
    m_idOfDatabase=5;
}

void CardEarthElemental::on_handToBattleField(COMBAT_ROW combatRow)
{
    emit handToBattleField(combatRow,this);
    
    this->getShield();//获得护盾
    qDebug()<<"has shield"<<this->m_hasShield;
    
    this->m_oursizePlayer->loseTurn();
}

void CardEarthElemental::battleFieldToGraveyard()
{
    if(!m_game)
        return;
    
    this->m_oursizePlayer->getBattle(this->getActualCombatRow())->removeCard(this);
    this->m_oursizePlayer->graveyard->addCard(this);
    
    //在该排末尾生成2只次级土元素
    Card* cardLesserEarthElemental[2];
    for(int i=0; i<2; i++)
    {
        cardLesserEarthElemental[i]=new CardLesserEarthElemental();
        this->m_oursizePlayer->createCard(cardLesserEarthElemental[i]);
        this->m_oursizePlayer->getBattle(this->getActualCombatRow())->addCard(cardLesserEarthElemental[i]);
    }
}

//------------------------老巫妪：织婆-------------------------------------------------------------

CardCroneWeavess::CardCroneWeavess():
CardDerived(RACE::MONSTERS, "Crone:_Weavess",":/img/card/res/cardPicture/Crone_Weavess.png",
            "部署：从牌组打出“煮婆”和“呢喃婆”。",
            6,TYPE::SILVER,COMBAT_ROW::SIEGE,true)
{
    m_idOfDatabase=6;
    
}

void CardCroneWeavess::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    Card* crone1=this->m_oursizePlayer->library->getCardOfName("Crone:_Whispess");
    if(crone1)
    {
        this->m_oursizePlayer->getBattle(combatRow)->addCard(crone1);
    }
    Card* crone2=this->m_oursizePlayer->library->getCardOfName("Crone:_Brewess");
    if(crone2)
    {
        this->m_oursizePlayer->getBattle(combatRow)->addCard(crone2);
    }
    
    this->m_oursizePlayer->loseTurn();
}

//------------------------老巫妪：呢喃婆-------------------------------------------------------------

CardCroneWhispess::CardCroneWhispess():
CardDerived(RACE::MONSTERS, "Crone:_Whispess",":/img/card/res/cardPicture/Crone_Whispess.png",
            "部署：从牌组打出“煮婆”和“织婆”。",
            6,TYPE::SILVER,COMBAT_ROW::SIEGE,true)
{
    m_idOfDatabase=7;
}

void CardCroneWhispess::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    Card* crone1=this->m_oursizePlayer->library->getCardOfName("Crone:_Weavess");
    if(crone1)
    {
        this->m_oursizePlayer->getBattle(combatRow)->addCard(crone1);
    }
    Card* crone2=this->m_oursizePlayer->library->getCardOfName("Crone:_Brewess");
    if(crone2)
    {
        this->m_oursizePlayer->getBattle(combatRow)->addCard(crone2);
    }
    
    this->m_oursizePlayer->loseTurn();
}

//------------------------老巫妪：织婆-------------------------------------------------------------

CardCroneBrewess::CardCroneBrewess():
CardDerived(RACE::MONSTERS, "Crone:_Brewess",":/img/card/res/cardPicture/Crone_Brewess.png",
            "部署：从牌组打出“呢喃婆”和“织婆”。",
            8,TYPE::SILVER, COMBAT_ROW::SIEGE, true)
{
    m_idOfDatabase=8;
    
}

void CardCroneBrewess::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    Card* crone1=this->m_oursizePlayer->library->getCardOfName("Crone:_Whispess");
    if(crone1)
    {
        this->m_oursizePlayer->getBattle(combatRow)->addCard(crone1);
    }
    Card* crone2=this->m_oursizePlayer->library->getCardOfName("Crone:_Weavess");
    if(crone2)
    {
        this->m_oursizePlayer->getBattle(combatRow)->addCard(crone2);
    }
    this->m_oursizePlayer->loseTurn();
}

//------------------------大狮鹫-------------------------------------------------------------
CardArchgriffin::CardArchgriffin():
CardDerived(RACE::MONSTERS,"Archgriffin",":/img/card/res/cardPicture/Archgriffin.png",
            "部署：移除所在排的天气效果。",
            7, TYPE::BRONZE, COMBAT_ROW::ANY, true)
{
    m_idOfDatabase=9;
}

void CardArchgriffin::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    this->m_oursizePlayer->getBattle(combatRow)->changeClimate(CLIMATE::SUNNY);
    
    this->m_oursizePlayer->loseTurn();
}

//------------------------卡兰希尔-------------------------------------------------------------

CardCaranthir::CardCaranthir():
CardDerived(RACE::MONSTERS, "Caranthir",":/img/card/res/cardPicture/Caranthir.png",
            "部署：将3个敌军单位移至对方同排，并在此排降下“刺骨冰霜”。",
            9,TYPE::GOLD,COMBAT_ROW::ANY, true)
{
    m_idOfDatabase=10;
    pressCount=0;//点选的卡牌个数
    
}

void CardCaranthir::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    this->showGoalLine(true);//显示目标指示线
    
    BattleField *battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
}

void CardCaranthir::on_CardPressed(Card *card)
{
    if(!m_game)
        return;
    
    pressCount++;
    if(pressCount==1)
    {
        finalBattle=this->m_enemyPlayer->getBattle(card->getActualCombatRow());
        return;
    }
    this->m_enemyPlayer->getBattle(card->getActualCombatRow())->removeCard(card);
    finalBattle->addCard(card);
    
    if(pressCount==3)
    {
        finalBattle->changeClimate(CLIMATE::FROST);
        pressCount=0;
        
        //解除连接
        BattleField *battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE);
        for(int i=0; i<battle->getSize(); i++)
        {
            disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
        }
        
        battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE);
        for(int i=0; i<battle->getSize(); i++)
        {
            disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
        }
        
        battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE);
        for(int i=0; i<battle->getSize(); i++)
        {
            disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
        }
        
        showGoalLine(false);
        
        disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
        
        this->m_oursizePlayer->loseTurn();
    }
    
}

void CardCaranthir::on_playerLoseTurn()
{
    if(!m_game)
        return;
    //解除连接
    BattleField *battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
}

//------------------------畏惧者-------------------------------------------------------------

CardFrighterner::CardFrighterner():
CardDerived(RACE::MONSTERS, "Frightener",":/img/card/res/cardPicture/Frightener.png",
            "部署：从牌组顶端抽1张牌。将所在战场其他排的1个单位移至自身的同一排。",
            10,TYPE::SILVER,COMBAT_ROW::ANY,false)
{
    m_idOfDatabase=11;
}

void CardFrighterner::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    //畏惧者的不忠属性
    this->m_oursizePlayer->getBattle(combatRow)->removeCard(this);
    this->m_enemyPlayer->getBattle(combatRow)->addCard(this);
    
    this->m_oursizePlayer->drawACardFromLibrary();//从牌组顶端抽一张牌
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(true);
    
    if(COMBAT_ROW::CLOSE!=combatRow)//把对方的某张牌移至同一排，未验证
    {
        BattleField *battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE);
        for(int i=0; i<battle->getSize(); i++)
        {
            connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
        }
    }
    
    if(COMBAT_ROW::REMOTE!=combatRow)
    {
        BattleField *battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE);
        for(int i=0; i<battle->getSize(); i++)
        {
            connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
        }
    }
    
    if(COMBAT_ROW::SIEGE!=combatRow)
    {
        BattleField *battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE);
        for(int i=0; i<battle->getSize(); i++)
        {
            connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
        }
    }
    
}

void CardFrighterner::on_CardPressed(Card *card)
{
    if(!m_game)
        return;
    
    this->m_enemyPlayer->getBattle(card->getActualCombatRow())->removeCard(card);
    this->m_enemyPlayer->getBattle(this->getActualCombatRow())->addCard(card);
    
    BattleField *battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    
    
    this->m_oursizePlayer->loseTurn();
}

void CardFrighterner::on_playerLoseTurn()
{
    if(!m_game)
        return;
    
    BattleField *battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    
}

//------------------------暗影长者-------------------------------------------------------------

CardUnseenElder::CardUnseenElder():
CardDerived(RACE::MONSTERS, "Unseen_Elder",":/img/card/res/cardPicture/Unseen Elder.png",
            "部署：吞噬3个友军单位，吸收它们的战力为自身的基础战力。",
            5,TYPE::GOLD,COMBAT_ROW::LEADER,true)
{
    m_idOfDatabase=12;
    foodCount=0;
}

void CardUnseenElder::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    showGoalLine(true);
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    BattleField *battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
    }
}

void CardUnseenElder::swallow(Card *card)
{
    if(!m_game)
        return;
    
    if(!card)
        return;
    
    if(card->isGoldenCard())
        return;
    
    foodCount++;
    
    card->beforeBeSwallowed();//card被吃之前发动
    m_actualStrength+=card->getActualStrength();//吸收友军的力量
    card->battleFieldToGraveyard();//将友军置入墓地
    emit swallowFriend();//发出吃了友军的信号
    
    if(foodCount==3)//吃满3个食物则解除连接
    {
        BattleField *battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE);
        for(int i=0; i<battle->getSize(); i++)
        {
            disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
        }
        
        battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE);
        for(int i=0; i<battle->getSize(); i++)
        {
            disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
        }
        
        battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE);
        for(int i=0; i<battle->getSize(); i++)
        {
            disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
        }
        
        disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
        
        foodCount=0;
        
        showGoalLine(false);
        
        this->m_oursizePlayer->loseTurn();
    }
}

void CardUnseenElder::on_playerLoseTurn()
{
    BattleField *battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(swallow(Card*)));
    }
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    foodCount=0;
    
    showGoalLine(false);
}

//------------------------蟹蜘蛛-------------------------------------------------------------

CardArachas::CardArachas():
CardDerived(RACE::MONSTERS,"Arachas",":/img/card/res/cardPicture/Arachas.png",
            "部署：从牌组打出所有“蟹蜘蛛”。",
            3,TYPE::BRONZE,COMBAT_ROW::REMOTE,true)
{
    m_idOfDatabase=13;
    
}

void CardArachas::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    Library *library=this->m_oursizePlayer->library;
    Card *card=library->getCardOfName(this->getName());
    while(card)
    {
        this->m_oursizePlayer->library->removeCard(card);
        this->m_oursizePlayer->getBattle(combatRow)->addCard(card);
        card=library->getCardOfName(this->getName());
    }
    
    this->m_oursizePlayer->loseTurn();
}

//------------------------蜥蜴人战士-------------------------------------------------------------

CardVranWarrior::CardVranWarrior():
CardDerived(RACE::MONSTERS,"Vran_Warrior",":/img/card/res/cardPicture/Vran_Warrior.png",
            "部署：吞噬右侧单位。每2回合，己方回合开始时，吞噬右侧单位。",
            5,TYPE::BRONZE,COMBAT_ROW::ANY, true)
{
    m_idOfDatabase=14;
}

void CardVranWarrior::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    shouldSwallow=true;
    on_playerGetTurn();
    
    connect(this->m_oursizePlayer, SIGNAL(playerGetTurn()), this, SLOT(on_playerGetTurn()));
    
    this->m_oursizePlayer->loseTurn();
}

void CardVranWarrior::swallow(Card *food)
{
    if(!m_game)
        return;
    
    if(!food)
        return;
    
    food->beforeBeSwallowed();//food被吃之前发动
    m_actualStrength+=food->getActualStrength();
    food->battleFieldToGraveyard();
    emit swallowFriend();
}

void CardVranWarrior::on_playerGetTurn()//这个类的吞噬效果还没有检验过
{
    if(!m_game)
        return;
    
    if(shouldSwallow)//该回合如果应该吞噬
    {
        Card *rightCard=this->m_oursizePlayer->getBattle(this->getActualCombatRow())->getRightCard(this);
        if(rightCard)
        {
            swallow(rightCard);
        }
        shouldSwallow=false;
    }
    else//否则，等下一回合
    {
        shouldSwallow=true;
    }
}

//------------------------狂野骑士-------------------------------------------------------------

CardWildHuntRider::CardWildHuntRider():
CardDerived(RACE::MONSTERS,"Wild_Hunt_Rider",":/img/card/res/cardPicture/Wild_Hunt_Rider.png",
            "使对方此排的“刺骨冰霜”伤害提高 1 点。",
            8,TYPE::BRONZE, COMBAT_ROW::ANY, true)
{
    m_idOfDatabase=15;
    
}

void CardWildHuntRider::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    BattleField * battle=this->m_enemyPlayer->getBattle(combatRow);
    if(battle->getClimate()==CLIMATE::FROST)
    {
        //刺骨冰霜的伤害提高1点
        battle->increaseFrostHarmBy(1);
    }
    
    this->m_oursizePlayer->loseTurn();
}

//------------------------蟹蜘蛛巨兽-------------------------------------------------------------
CardArachasBehemoth::CardArachasBehemoth():
CardDerived(RACE::MONSTERS, "Arachas_Behemoth",":/img/card/res/cardPicture/Arachas_Behemoth.png",
            "每当有友军单位吞噬1张牌，便生成1只“蟹蜘蛛”，随后受到1点伤害（无视护甲）。部署：获得2点护甲。",
            6, TYPE::BRONZE, COMBAT_ROW::SIEGE,true)
{
    m_idOfDatabase=16;
}

void CardArachasBehemoth::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    this->getArmor(2);
    for(int i=0; i<this->m_oursizePlayer->getSize(); i++)
    {
        connect(this->m_oursizePlayer->getNthCard(i), SIGNAL(swallowFriend()), this, SLOT(produce()));
    }
    this->m_oursizePlayer->loseTurn();
}

void CardArachasBehemoth::produce()//每当有友军单位吞噬1张牌，便生成1只“蟹蜘蛛
{
    if(!m_game)
        return;
    
    Card *card=new CardArachas();
    this->m_oursizePlayer->createCard(card);
    this->m_oursizePlayer->getBattle(card->getInitCombatRow())->addCard(card);
    
    //无视护甲，给自己1点伤害
    if(this->hasShield())//在有护甲的情况下
    {
        this->loseShield();//先解除护甲
        this->getHarm(1);//接受伤害
        this->getShield();//然后穿回护甲
    }else
    {
        this->getHarm(1);
    }
}

//------------------------破晓-------------------------------------------------------------

CardFirstLight::CardFirstLight():
CardDerived(RACE::NEUTRAL,"First_Light",":/img/card/res/cardPicture/First_Light.png",
            "生成“晴空”或“调遣”。",
            TYPE::BRONZE)
{
    m_idOfDatabase=17;
}

void CardFirstLight::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    //生成晴空或者调遣
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    connect(this->m_oursizePlayer->library,SIGNAL(LibraryPressed()), this, SLOT(on_libraryPressed()));
    
    showGoalLine(true);
    
}

void CardFirstLight::on_battlePressed(BattleField *battleField)//点击战排则生成晴空
{
    if(!m_game)
        return;
    
    battleField->changeClimate(CLIMATE::SUNNY);
    
    showGoalLine(false);
    
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->library,SIGNAL(LibraryPressed()), this, SLOT(on_libraryPressed()));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
    
}

void CardFirstLight::on_libraryPressed()//点击卡库则再抽一张卡牌
{
    if(!m_game)
        return;
    
    this->m_oursizePlayer->drawACardFromLibrary();
    
    showGoalLine(false);
    
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->library,SIGNAL(LibraryPressed()), this, SLOT(on_libraryPressed()));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
}

void CardFirstLight::on_playerLoseTurn()
{
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->library,SIGNAL(LibraryPressed()), this, SLOT(on_libraryPressed()));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    this->m_oursizePlayer->graveyard->addCard(this);
}

//------------------------刺骨冰霜-------------------------------------------------------------

CardBitingFrost::CardBitingFrost():
CardDerived(RACE::NEUTRAL, "Biting_Frost",":/img/card/res/cardPicture/Biting_Frost.png",
            "在对方单排降下“刺骨冰霜”。刺骨冰霜：每当己方回合开始时，对所在排最弱的单个单位造成2点伤害",
            TYPE::BRONZE)
{
    m_idOfDatabase=18;
}

void CardBitingFrost::on_handToBattleField(COMBAT_ROW combatRow)
{
    qDebug()<<"frost on hand to battleField";
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    showGoalLine(true);
}

void CardBitingFrost::changeWeather(BattleField *battle)
{
    qDebug()<<"frost change weather";
    if(!m_game)
        return;
    
    battle->changeClimate(CLIMATE::FROST);
    connect(this->m_oursizePlayer, SIGNAL(playerGetTurn()),battle,SLOT(getDemagedByWeather()));//每当己方回合开始时，该排收到伤害
    
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
}

void CardBitingFrost::on_playerLoseTurn()
{
    qDebug()<<"frost on player lose turn";
    if(!m_game)
        return;
    
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
}

//------------------------蔽日浓雾-------------------------------------------------------------

CardImpenetrableFog::CardImpenetrableFog():
CardDerived(RACE::NEUTRAL,"Impenetrable_Fog",":/img/card/res/cardPicture/Impenetrable_Fog.png",
            "在对方单排降下“蔽日浓雾”。蔽日浓雾：每当己方回合开始时，对所在排最强的单位造成2点伤害。",
            TYPE::BRONZE)
{
    m_idOfDatabase=19;
}

void CardImpenetrableFog::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    showGoalLine(true);
}

void CardImpenetrableFog::changeWeather(BattleField *battle)
{
    if(!m_game)
        return;
    
    battle->changeClimate(CLIMATE::FOG);
    connect(this->m_oursizePlayer, SIGNAL(playerGetTurn()),battle,SLOT(getDemagedByWeather()));//每当己方回合开始时，该排收到伤害
    
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
}

void CardImpenetrableFog::on_playerLoseTurn()
{
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
}

//------------------------倾盆大雨-------------------------------------------------------------

CardTorrentialRain::CardTorrentialRain():
CardDerived(RACE::NEUTRAL,"Torrential_Rain",":/img/card/res/cardPicture/Torrential_Rain.png",
            "在对方单排降下“倾盆大雨”。倾盆大雨：每当己方回合开始时，对所在排最多5个最弱的单位造成1点伤害。",
            TYPE::BRONZE)
{
    m_idOfDatabase=20;
    
}

void CardTorrentialRain::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    emit handToBattleField(combatRow,this);
    
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    showGoalLine(true);
}

void CardTorrentialRain::changeWeather(BattleField *battle)
{
    if(!m_game)
        return;
    
    battle->changeClimate(CLIMATE::RAIN);
    connect(this->m_oursizePlayer, SIGNAL(playerGetTurn()),battle,SLOT(getDemagedByWeather()));//每当己方回合开始时，该排收到伤害
    
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
}

void CardTorrentialRain::on_playerLoseTurn()
{
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)),this,SLOT(changeWeather(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
}

//------------------------撕裂-------------------------------------------------------------

CardLacerate::CardLacerate():
CardDerived(RACE::NEUTRAL, "Lacerate",":/img/card/res/cardPicture/Lacerate.png",
            "对单排所有单位造成3点伤害。",
            TYPE::BRONZE)
{
    m_idOfDatabase=21;
    
}

void CardLacerate::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    showGoalLine(true);
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
}

void CardLacerate::on_battlePressed(BattleField *battleField)
{
    if(!m_game)
        return;
    
    if(!battleField)
        return;
    
    for(int i=0; i<battleField->getSize(); i++)
    {
        Card *card=battleField->getNthCard(i);
        if(card)
        {
            card->getHarm(3);
        }
    }
    battleField->update();
    
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
}

void CardLacerate::on_playerLoseTurn()
{
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
}


//------------------------指挥号角-------------------------------------------------------------

CardCommandersHorn::CardCommandersHorn():
CardDerived(RACE::NEUTRAL,"Commander's_Horn",":/img/card/res/cardPicture/Commander's_Horn.png",
            "使5个相邻单位获得4点增益。",
            TYPE::SILVER)
{
    m_idOfDatabase=22;
    
}

void CardCommandersHorn::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    connect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    showGoalLine(true);
}

void CardCommandersHorn::on_battlePressed(BattleField *battleField)
{
    
    if(!m_game)
        return;
    
    if(!battleField)
        return;
    
    for(int i=0; i<battleField->getSize(); i++)
    {
        int count=0;
        Card *card=battleField->getNthCard(i);
        if(card)
        {
            card->getGain(4);
            count++;
        }
        if(count==5)
            break;
    }
    battleField->update();
    
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
}

void CardCommandersHorn::on_playerLoseTurn()
{
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_enemyPlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    disconnect(this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE),SIGNAL(battleFeildPressed(BattleField*)), this, SLOT(on_battlePressed(BattleField*)));
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
}

//------------------------贝克尔的扭曲之镜-------------------------------------------------------------

CardBekkersTwistedMirror::CardBekkersTwistedMirror():
CardDerived(RACE::NEUTRAL,"Bekker's_Twisted_Mirror",":/img/card/res/cardPicture/Bekker's_Twisted_Mirror.png",
            "将最强和最弱单位的战力互换",
            TYPE::SILVER)
{
    m_idOfDatabase=23;
    
}

void CardBekkersTwistedMirror::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    Card *weakestCard=Card::getWeakerCard(m_oursizePlayer->getWeakestCard(), m_enemyPlayer->getWeakestCard());//优先返回己方的最弱卡
    Card *strongestCard=Card::getStrongerCard(m_enemyPlayer->getStrongestCard(), m_oursizePlayer->getStrongestCard());//优先返回敌方的最强卡
    if(weakestCard && strongestCard)
    {
        int tempStrength=weakestCard->getActualStrength();
        weakestCard->setStrength(strongestCard->getActualStrength());
        strongestCard->setStrength(tempStrength);
    }
    
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
    
}

//------------------------杰洛特：伊格尼法印-------------------------------------------------------------

CardGeraltIgni::CardGeraltIgni():
CardDerived(RACE::NEUTRAL,"Geralt:_Igni",":/img/card/res/cardPicture/Geralt_Igni.png",
            "部署：若对方同排总战力不低于20，则摧毁其上所有最强的单位。",
            4,TYPE::GOLD,COMBAT_ROW::ANY,true)
{
    m_idOfDatabase=24;
}

void CardGeraltIgni::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    BattleField *battle=this->m_enemyPlayer->getBattle(combatRow);//对方同排
    if(battle->getTotalStrength()>=20)
    {
        Card* strongestCard=battle->getStrongestCard();
        if(strongestCard)//如果存在最强的非金卡
        {
            int strongestStrength=strongestCard->getActualStrength();//得到当前排最强战力值
            for(int i=0; i<battle->getSize(); i++)//摧毁其上所有最强单位
            {
                Card *card=battle->getNthCard(i);
                if(card && card->getActualStrength()==strongestStrength && !card->isGoldenCard())
                {
                    this->battleFieldToGraveyard();
                }
            }
        }
        
    }
}

//------------------------雷霆药水-------------------------------------------------------------

CardThunderboltPotion::CardThunderboltPotion():
CardDerived(RACE::NEUTRAL,"Thunderbolt_Potion",":/img/card/res/cardPicture/Thunderbolt_Potion.png",
            "使 3 个相邻单位获得 2 点护甲和 3 点增益。",
            TYPE::BRONZE)
{
    m_idOfDatabase=25;
}

void CardThunderboltPotion::on_handToBattleField(COMBAT_ROW combatRow)
{
    if(!m_game)
        return;
    
    emit handToBattleField(combatRow,this);
    
    connect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    
    BattleField *battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        connect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    showGoalLine(true);
}

void CardThunderboltPotion::on_CardPressed(Card *card)
{
    if(!m_game)
        return;
    
    if(!card)
        return;
    
    BattleField *battle=this->m_oursizePlayer->getBattle(card->getActualCombatRow());
    card->getArmor(2);
    card->getGain(3);
    
    Card *leftCard=battle->getLeftCard(card);
    if(leftCard)
    {
        leftCard->getArmor(2);
        leftCard->getGain(3);
    }
    
    Card *rightCard=battle->getRightCard(card);
    if(rightCard)
    {
        rightCard->getArmor(2);
        rightCard->getGain(3);
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
    this->m_oursizePlayer->loseTurn();
    
}

void CardThunderboltPotion::on_playerLoseTurn()
{
    BattleField* battle;
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::CLOSE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::REMOTE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    battle=this->m_oursizePlayer->getBattle(COMBAT_ROW::SIEGE);
    for(int i=0; i<battle->getSize(); i++)
    {
        disconnect(battle->getNthCard(i),SIGNAL(cardPressed(Card*)), this, SLOT(on_CardPressed(Card*)));
    }
    
    disconnect(this->m_oursizePlayer, SIGNAL(playerLoseTurn()), this, SLOT(on_playerLoseTurn()));//当我方选手失去发牌机会就不能再发动这张卡的效果了
    
    showGoalLine(false);
    this->m_oursizePlayer->graveyard->addCard(this);
}

//------------------------萝卜-------------------------------------------------------------

CardRoach::CardRoach():
CardDerived(RACE::NEUTRAL,"Roach",":/img/card/res/cardPicture/Roach.png",
            "己方每次从手牌打出金色牌时（领袖牌除外），便将牌组中的“萝卜”在其能力结算之前召唤至随机位置。",
            4,TYPE::BRONZE,COMBAT_ROW::ANY,true)
{
    m_idOfDatabase=26;
    connect(this, SIGNAL(addToLibrary()), this, SLOT(on_addToLibrary()));
}

void CardRoach::on_addToLibrary()
{
    if(!m_game)
        return;
    
    for(int i=0; i<this->m_oursizePlayer->getSize(); i++)//则连接所有的牌
    {
        Card *card=this->m_oursizePlayer->getNthCard(i);
        if(card && card->getInitType()==TYPE::GOLD //每当金色牌
           && !card->isLeader())//领袖卡除外
        {
            connect(card, SIGNAL(handToBattleField(COMBAT_ROW,Card*)), this, SLOT(on_handToBattleField(COMBAT_ROW)));//打出时，打出萝卜
        }
    }
}

void CardRoach::on_handToBattleField(COMBAT_ROW combatRow)//响应的其实是其他牌从手牌中发动的信号
{
    if(!m_game)
        return;
    
    if(this->getStatus()==STATUS::DECK)//萝卜此时必须在牌组中
    {
        this->m_oursizePlayer->library->removeCard(this);
        
        //将萝卜召唤至随机位置
        int randomNum=rand()%3;
        COMBAT_ROW combatRow;
        switch (randomNum) {
            case 0:
                combatRow=COMBAT_ROW::CLOSE;
                break;
            case 1:
                combatRow=COMBAT_ROW::REMOTE;
                break;
            case 2:
                combatRow=COMBAT_ROW::SIEGE;
                break;
        }
        this->m_oursizePlayer->getBattle(combatRow)->addCard(this);
    }
}

//------------------------鹰身女妖蛋----------------------------
CardHarpyEgg::CardHarpyEgg():
CardDerived(RACE::MONSTERS, "HarpyEgg",":/img/card/res/cardPicture/HarpyEgg.jpeg","当蛋被吞噬时，除了自身、、本身的1点力量外，额外增强5点力量",
            1, TYPE::BRONZE, COMBAT_ROW::ANY, true)
{
    m_idOfDatabase=27;
    
}

void CardHarpyEgg::beforeBeSwallowed()
{
    getGain(5);
}

//---------------------暴怒的狼----------------------------------
CardRabidWolf::CardRabidWolf():
CardDerived(RACE::MONSTERS, "RabidWolf", ":/img/card/res/cardPicture/Rabid_Wolf.png", "无特殊能力",
            1, TYPE::BRONZE, COMBAT_ROW::CLOSE, true)
{
    m_idOfDatabase=28;
    
}

//---------------------次级土元素-------------------------------
CardLesserEarthElemental::CardLesserEarthElemental():
CardDerived(RACE::MONSTERS, "LesserEarthElemental", ":/img/card/res/cardPicture/Lesser_Earth_Elemental.png", "无特殊能力",
            2, TYPE::BRONZE, COMBAT_ROW::CLOSE, true)
{
    m_idOfDatabase=29;
    
}


