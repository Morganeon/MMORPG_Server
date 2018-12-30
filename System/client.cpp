#include "client.h"

#include "packet.h"
#include "realm.h"

namespace MMO
{
namespace System
{

int MMO::System::Client::m_heartbeatTimer = 5; // in seconds
qint64 MMO::System::Client::m_count = 0; // for ID calculation

Client::Client(MMO::System::Realm * parent, QTcpSocket *socket, MMO::System::Room * defaultRoom)
{
    m_currentRealm = parent;
    setParent(parent);
    m_timer = new QTimer(this);
    m_timer->start(1000*m_heartbeatTimer);
    m_id = m_count;
    m_count ++;
    m_socket = socket;

    connect(m_timer,  SIGNAL(timeout()),this,SLOT(networkTimedOut()));
    connect(m_socket, SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(m_socket,QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),this,&Client::networkError);

    enterRoom(defaultRoom);
}

void Client::receiveKeyboardState()
{
    char data[12] = {0};
    m_socket->read(data,4);
    unsigned long int keyboardState = *(unsigned long int*)data;
    m_socket->read(data,4);
    float analogFront = *(float*)data;
    m_socket->read(data,4);
    float analogSide = *(float*)data;

    Packet p(24);
    p.pushHeader(PacketHeader::ServerSendKeyboardState);
    p.pushInt64(m_id);
    p.pushUnsignedInt32(keyboardState);
    p.pushFloat32(analogFront);
    p.pushFloat32(analogSide);
    m_currentRoom->broadcast(p.data(),p.size());

}

void Client::receiveHeartBeat()
{

}

void Client::receiveKeyAction()
{

}

void Client::receiveEnvironmentAction()
{

}

void Client::receiveSystemAction()
{

}

void Client::networkError(QAbstractSocket::SocketError socketError)
{
    qInfo()<< "Error occured:" << socketError;
    sendDisconnection();
}

void Client::networkTimedOut()
{
    m_heartbeatMissed++;
    if (m_heartbeatMissed>= 5)
    {
        m_timer->stop();
        qInfo()<< "Client timed out.";
        sendDisconnection();
    }
}

void Client::enterRoom(Room *room)
{
    if (m_currentRoom != nullptr)
    {
        m_currentRoom->unregisterClient(this);

    }

    m_currentRoom = room;
    Packet packet(12);
    packet.pushHeader(PacketHeader::ServerClientEnterRoom);
    packet.pushInt64(m_id);
    m_currentRoom->broadcast(packet.data(),packet.size());
    room->registerClient(this);
    room->sendSnapshot(this);
}

void Client::sendKeyboardState()
{

}

void Client::sendHeartBeat()
{

}

void Client::sendKeyAction()
{

}

void Client::sendEnvironmentAction()
{

}

void Client::sendSystemAction()
{

}

void Client::send(char *data, long long size)
{
    m_socket->write(data,size);
}

void Client::forceSend(char *data, long long size)
{
    send(data,size);
    m_socket->flush();
}

void Client::readMessage()
{
    m_heartbeatMissed = 0;
    char data[4] = {0};
    while (m_socket->read(data,4)!=0)
    {
        switch(data[0])
        {
            case PacketHeader::ClientSendKeyboardState:
                receiveKeyboardState();
            break;

        default:
            qInfo()<< "Unhandled message:" << (short)data[0];
            break;
        }
    }

}

void Client::sendDisconnection()
{
    if (m_socket->isOpen())
    {
        Packet p(4);
        p.pushHeader(PacketHeader::ServerSendKick);
        send(p.data(),p.size());
    }
    m_currentRoom->unregisterClient(this);
    m_currentRealm->unregisterClient(this);
    delete this;
}

}
}
