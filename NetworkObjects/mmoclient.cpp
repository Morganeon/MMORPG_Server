#include "mmoclient.h"

#include <mainwindow.h>

#define CLIENT_MESSAGE_UPDATE (qint32)1
#define CLIENT_CONNECT (qint32)0
#define CLIENT_DISCONNECTED (qint32)-1
#define CLIENT_SNAPSHOT (qint32)2

int MMOClient::count = 0;

MMOClient::MMOClient(MainWindow * parent, QTcpSocket *socket)
{
    m_id = count;
    count ++;
    m_main = parent;
    setParent(parent);
    m_socket = socket;
    connect(m_socket,&QTcpSocket::readyRead,this,&MMOClient::onReadyRead);
    connect(m_socket,&QTcpSocket::disconnected,this,&MMOClient::onDisconnected);

    char data[8] = {0};
    qint32 tmp = CLIENT_CONNECT;
    memcpy(data,&tmp,4);
    memcpy(data+4,&m_id,4);
    m_socket->write(data,8);
    m_r = rand()%255;
    m_g = rand()%255;
    m_b = rand()%255;

}

void MMOClient::onReadyRead()
{
    char data[4] = {0};
    m_socket->read(data,4);

    switch(data[0])
    {
        case CLIENT_MESSAGE_UPDATE:
            receiveUpdate();
        break;

    default:
        qInfo()<< "Unhandled message:" << (short)data[0];
        break;
    }
}

void MMOClient::receiveUpdate()
{
    char data[16] = {0};
    int read = m_socket->read(data,16);
    m_x = *(float*)data;
    m_y = *(float*)(data+4);
    m_angle = *(float*)(data+8);
    sendUpdate();
}

void MMOClient::sendUpdate()
{
    char data[20] = {0};
    qint32 tmp = CLIENT_MESSAGE_UPDATE;
    memcpy(data,&tmp,4);
    memcpy(data+4,&m_id,4);
    memcpy(data+8,&m_x,4);
    memcpy(data+12,&m_y,4);
    memcpy(data+16,&m_angle,4);
    for (int i=0;i<m_main->m_clientList.size();i++)
    {
        if (m_main->m_clientList.at(i)!=this)
        {
            m_main->m_clientList.at(i)->m_socket->write(data,20);
        }
    }
}

void MMOClient::onDisconnected()
{
    qInfo()<< "Client disconnected.";
    char data[8] = {0};
    qint32 tmp = CLIENT_DISCONNECTED;
    memcpy(data,&tmp,4);
    memcpy(data+4,&m_id,4);
    int _id = 0;
    for (int i=0;i<m_main->m_clientList.size();i++)
    {
        if (m_main->m_clientList.at(i)!=this)
        {
            m_main->m_clientList.at(i)->m_socket->write(data,8);
        }
        else
        {
            _id = i;
        }
    }

    m_main->m_clientList.erase(m_main->m_clientList.begin()+_id);
    delete this;

}

void MMOClient::sendSnapshot()
{
    qInfo() << "Sending snapshot...";
    int val_per_client = 28;
    int nb_clients = m_main->m_clientList.size();
    qInfo() << nb_clients;
    int payload = 8;
    char * data = new char[payload+nb_clients*val_per_client];
    qint32 tmp = CLIENT_SNAPSHOT;
    memcpy(data,&tmp,4);
    tmp = nb_clients;
    memcpy(data+4,&tmp,4);
    for (int i=0;i<nb_clients;i++)
    {
        MMOClient * c = m_main->m_clientList.at(i);
        memcpy(data+payload+i*val_per_client,&c->m_id,4);
        memcpy(data+payload+i*val_per_client+4,&c->m_x,4);
        memcpy(data+payload+i*val_per_client+8,&c->m_y,4);
        memcpy(data+payload+i*val_per_client+12,&c->m_angle,4);
        memcpy(data+payload+i*val_per_client+16,&c->m_r,4);
        memcpy(data+payload+i*val_per_client+20,&c->m_g,4);
        memcpy(data+payload+i*val_per_client+24,&c->m_b,4);
    }
    m_socket->write(data,payload+nb_clients*val_per_client);

    delete data;
}

