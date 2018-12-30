#ifndef ROOM_H
#define ROOM_H

#include "client.h"
#include "packet.h"

#include <QList>

#include <Gameplay/mapdata.h>

namespace MMO
{
namespace System
{

class Room
{
public:
    Room(QString name);
    virtual ~Room();
    void broadcast(char * data, qint64 lenght);
    void registerClient(Client * client);
    void unregisterClient(Client * client);
    void sendSnapshot(Client * client);

private:
    QList<Client *>m_clients;
    QString m_name;
    MapData * m_mapData;
    Packet * m_roomPacket;
    //QList<MMO::Entity::PlayerCharacter *> m_playerCharacter;
    //QList<MMO::Entity::NonPlayerCharacter *> m_nonPlayerCharacter;
    //QList<MMO::Entity::Collectible *> m_collectibles;
};

}
}
#endif // ROOM_H
