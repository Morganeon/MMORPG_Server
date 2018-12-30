#ifndef REALM_H
#define REALM_H

#include "client.h"
#include "room.h"

#include <QList>
#include <QTcpServer>


namespace MMO
{
namespace System
{

class Realm : public QObject
{
    Q_OBJECT

public:
    Realm();
    ~Realm();
    void unregisterClient(Client * client);

private slots:
    void onNewConnection();
    void onServerShutdown();


private:
    QList<Room *> m_rooms;
    QList<Client *> m_clients;
    QTcpServer * m_server;
    quint16 m_port = 2100;

};

}
}
#endif // REALM_H
