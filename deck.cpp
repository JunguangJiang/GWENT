#include "deck.h"
#include "carddatabase.h"
#include <QDebug>
#include <QFile>
#include <QDir>
Deck::Deck(int deckId, GraphicsItem *parent) :GraphicsItem(0,0,1,1,ModifyDeckImagePath, parent)
{
    m_deckId=deckId;

    for(int i=0; i<3; i++)
    {
        m_cardNumberShow[i]=new text(DeckTitlePos[i], DeckTitleSize, this);
        m_cardNumberShow[i]->setFontColor(Qt::white);
        m_cardNumberShow[i]->setFontSize(20);
        m_cardNumberShow[i]->setCenter();
        m_cardNumberOfType[i]=0;
    }
    m_totalCardNumberShow=new text(DeckTotalNumberPos, DeckTitleSize, this);
    m_totalCardNumberShow->setFontColor(Qt::white);
    m_totalCardNumberShow->setFontSize(19);
    m_totalCardNumberShow->setCenter();
    m_totalCardNumber=0;

    m_saveButton=new Button(DeckSavePos, DeckSaveSize,SaveButtonImagePath, this);
    m_saveButton->setEnabled(true);
    connect(m_saveButton, SIGNAL(buttonPressed()), this, SLOT(on_saveButtonPressed()));

    //m_exitButton=new Button(DeckExitPos, DeckExitSize, ExitButtonImagePath, this);
    //m_exitButton->setEnabled(true);
    //connect(m_exitButton, SIGNAL(buttonPressed()), this, SLOT(on_exitButtonPressed()));

    m_hasLeader=false;

    cardDatabase=new CardDatabase();

    for(int i=0; i<cardDatabase->getSize(); i++)
    {
        newCard[i]=cardDatabase->getCardWithIdOfDatabase(i);
        newCard[i]->setParentItem(this);
        newCard[i]->setEnabled(true);
        connect(newCard[i], SIGNAL(cardPressed(Card*)), this, SLOT(on_cardPressed(Card*)));
        newCard[i]->showAmountInDeck(true);//卡牌上显示张数

        switch (newCard[i]->getInitType()) {
        case TYPE::GOLD:
            m_CardIdOfType[GOLD].push_back(i);
            break;
        case TYPE::SILVER:
            m_CardIdOfType[SILVER].push_back(i);
            break;
        case TYPE::BRONZE:
            m_CardIdOfType[BRONZE].push_back(i);
            break;
        default:
            break;
        }
    }


}

void Deck::complete()//完成卡组的创建时，需要给所有的卡牌一个标识符
{    
    m_cardId.clear();

    m_cardId.push_back(m_leader);//返回的卡组第一个总是领袖的id

    qDebug()<<"the 4th deck leader is"<<m_leader;

    for(int i=0; i<cardDatabase->getSize(); i++)
    {
        if(newCard[i]->isLeader())//如果当前卡牌是领袖，由于上面已经处理过了，所以跳过
        {
            continue;
        }

        int times=newCard[i]->m_amountInDeck;//根据选中的卡牌数量
        for(int j=0; j<times; j++)
        {
            m_cardId.push_back(newCard[i]->getIdOfDatabase());//加入相应数量的卡牌id
        }
    }

}

void Deck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItem::paint(painter, option, widget);

    for(int type=0; type<3; type++)
    {
        m_cardNumberShow[type]->setText(std::to_string(m_cardNumberOfType[type]));
    }
    m_totalCardNumberShow->setText("Total: "+std::to_string(m_totalCardNumber));

    showAllCards(painter);
}

void Deck::showAllCards(QPainter* painter)//展示卡牌上所有的卡牌
{

    for(int type=0; type<3; type++)
    {
        if(m_CardIdOfType[type].empty())
        {
            continue;
        }
        qreal DeckCardHorizontalDistance=DeckCardSize.width()/m_CardIdOfType[type].size();

        qreal left=DeckCardPos[type].x();
        qreal top=DeckCardPos[type].y();

        for(int cardNum=0; cardNum<m_CardIdOfType[type].size(); cardNum++)
        {
            int idOfDatabase=m_CardIdOfType[type][cardNum];
            newCard[idOfDatabase]->setLeftTop(left, top);
            left+=DeckCardHorizontalDistance;
            newCard[idOfDatabase]->setZValue(cardNum);
        }
    }
}

void Deck::countCardNumber()
{
    m_totalCardNumber=0;
    for(int type=0; type<3; type++)
    {
        m_cardNumberOfType[type]=0;
        for(int cardNum=0; cardNum<m_CardIdOfType[type].size(); cardNum++)
        {
            int idOfDatabase=m_CardIdOfType[type][cardNum];
            m_cardNumberOfType[type]+=newCard[idOfDatabase]->m_amountInDeck;
        }
        m_totalCardNumber+=m_cardNumberOfType[type];
    }

}

void Deck::on_cardPressed(Card *card)
{
    if(card->canBeLeader())//对于领袖卡特殊处理
    {
        if(card->isLeader())//如果已经被设置为领袖
        {
            m_hasLeader=false;//则取消其领袖的位置
            card->setLeader(false);
            card->m_amountInDeck=0;
        }else//否则没有被设置为领袖的话
        {
            if(!m_hasLeader)//在没有领袖时
            {
                m_hasLeader=true;
                card->setLeader(true);
                card->m_amountInDeck=1;
                m_leader=card->getIdOfDatabase();
            }
        }
    }
    else
    {
        if(card->getInitType()==TYPE::BRONZE)
        {
            card->m_amountInDeck=(card->m_amountInDeck+1)%4;
        }
        else
        {
            card->m_amountInDeck=(card->m_amountInDeck+1)%2;
        }
    }

    card->update();
    countCardNumber();
    update();
}

void Deck::on_saveButtonPressed()
{
    if(m_totalCardNumber>40 || m_totalCardNumber<25 || m_hasLeader==false)
    {
        return;
    }
    else
    {
        complete();

        QFile file(DeckFilePrefix+QString::number(m_deckId)+QString(".dat"));

        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug()<<"error writing";
        }
        QDataStream out(&file);
        out << *(this);
        file.close();

        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug()<<"error reading";
            return;
        }

        Deck newDeck(-1);
        QDataStream in(&file);


        in>>newDeck;
        for(int i=0; i<newDeck.getSize(); i++)
        {
          qDebug()<<QString::number(newDeck.getNthCardId(i));
        }
        file.close();

        emit closeInterface(ModifyDeckInterface);//退出当前界面

    }

}


QDataStream &operator<<(QDataStream &out,const Deck &deck)
{
    int size=static_cast<int>(deck.m_cardId.size());

    out << size;

    for(int i=0; i<deck.m_cardId.size(); i++)
    {
        out << deck.m_cardId[i];
    }
    return out;
}

QDataStream &operator>>(QDataStream &in , Deck &deck)
{
    int size;
    in >> size;
    deck.m_cardId.clear();
    for(int i=0; i<size; i++)
    {
        int idOfDatabase;
        in >> idOfDatabase;
        deck.m_cardId.push_back(idOfDatabase);
    }
    return in;
}
