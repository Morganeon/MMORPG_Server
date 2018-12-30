#include "packet.h"
#include "realm.h"
namespace MMO
{
namespace System
{

Realm::Realm()
{
    m_server = new QTcpServer(this);
    m_server->listen(QHostAddress::Any,m_port);

    qInfo()<< "Server listening on" << m_server->serverAddress() << ":" << m_port;
    connect(m_server,&QTcpServer::newConnection,this,&Realm::onNewConnection);
    connect(m_server,&QTcpServer::destroyed,this,&Realm::onServerShutdown);
    Room * room = new Room("Start");
    m_rooms.push_back(room);

}

Realm::~Realm()
{

    m_server->close();
    delete m_server;

}

void Realm::onNewConnection()
{
    qInfo()<< "New connection";
    Client * client = new Client(this, m_server->nextPendingConnection(),m_rooms.at(0));
    m_clients.push_back(client);
}

void Realm::onServerShutdown()
{
    // Destroying rooms
    for (int i=0;i<m_rooms.size();i++)
    {
        delete m_rooms.at(i);
    }

}

void Realm::unregisterClient(Client * client)
{
    m_clients.removeOne(client);
}

}
}
