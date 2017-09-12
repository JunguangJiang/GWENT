#include "user.h"

User::User(int id, QObject *parent) : QObject(parent), m_id(id)
{

}

User::~User()
{

}

Deck* User::getNthDeck(int i) const
{
    return m_decks[i];
}
