#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

    m_users.push_back(new User(0));

}
