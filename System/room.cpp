#include "room.h"

namespace MMO
{
namespace System
{

Room::Room(QString name)
{

    m_name = name;
    m_mapData = new MapData("C:/Users/morga/Desktop/testmap_tiles.txt","C:/Users/morga/Desktop/testmap_collider.txt");

    int wdt = m_mapData->m_tiles->getWidth();
    int hei = m_mapData->m_tiles->getHeight();

    m_roomPacket = new Packet(12+4*wdt*hei*2);
    m_roomPacket->pushHeader(PacketHeader::ServerSendMapData);
    m_roomPacket->pushInt32(wdt);
    m_roomPacket->pushInt32(hei);
    for (int i=0;i<hei;i++)
        for (int j=0;j<wdt;j++)
        {
            m_roomPacket->pushInt32(m_mapData->m_tiles->getData(j,i));
            m_roomPacket->pushInt32(m_mapData->m_block->getData(j,i));
        }
}

Room::~Room()
{

    Packet p(4);
    p.pushHeader(PacketHeader::ServerSendKick);
    for (int i=0;i<m_clients.size();i++)
    {
        m_clients.at(i)->forceSend(p.data(),p.size());
        delete m_clients.at(i);
    }
    delete m_roomPacket;
    delete m_mapData;

}

void Room::broadcast(char *data, qint64 lenght)
{
    for (int i=0;i<m_clients.size();i++)
    {
        m_clients.at(i)->getSocket()->write(data,lenght);
    }
}

void Room::registerClient(Client * client)
{
    m_clients.push_back(client);
}

void Room::unregisterClient(Client * client)
{
    m_clients.removeOne(client);
    Packet packet(12);
    packet.pushHeader(PacketHeader::ServerClientLeaveRoom);
    packet.pushInt64(client->getId());
    broadcast(packet.data(),packet.size());
}

void Room::sendSnapshot(Client * client)
{

    Packet p(20+m_name.length()+1+m_clients.size()*8);
    p.pushHeader(PacketHeader::ServerSendSnapshot);
    p.pushInt64(client->getId());
    p.pushInt64(m_clients.size());
    for (int i=0;i<m_clients.size();i++)
    {
        p.pushInt64(m_clients.at(i)->getId());
    }
    client->send(p.data(),p.size());

    client->send(m_roomPacket->data(),m_roomPacket->size());
}

}
}
