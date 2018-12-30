#include "packet.h"
#include <QDebug>

namespace MMO
{
namespace System
{

Packet::Packet(long long int base_size)
{
    m_currentSize = base_size;
    m_data = new char[base_size];
}

Packet::~Packet()
{
    if (m_data!=nullptr) delete m_data;
}

char *Packet::data()
{
    return m_data;
}

long long Packet::size()
{
    return m_size;
}

void Packet::pushHeader(PacketHeader val)
{
    long long int desiredSize = 4;
    adaptSize(m_size+desiredSize);
    memcpy(m_data+m_size,&val,desiredSize);
    m_size +=desiredSize;
}

void Packet::pushUnsignedInt32(unsigned long val)
{
    long long int desiredSize = 4;
    adaptSize(m_size+desiredSize);
    memcpy(m_data+m_size,&val,desiredSize);
    m_size +=desiredSize;
}

void Packet::pushInt32(long val)
{
    long long int desiredSize = 4;
    adaptSize(m_size+desiredSize);
    memcpy(m_data+m_size,&val,desiredSize);
    m_size +=desiredSize;

}

void Packet::pushInt64(long long val)
{
    long long int desiredSize = 8;
    adaptSize(m_size+desiredSize);
    memcpy(m_data+m_size,&val,desiredSize);
    m_size +=desiredSize;
}

void Packet::pushFloat32(float val)
{
    long long int desiredSize = 4;
    adaptSize(m_size+desiredSize);
    memcpy(m_data+m_size,&val,desiredSize);
    m_size +=desiredSize;
}

void Packet::pushBool(bool val)
{
    long long int desiredSize = 1;
    adaptSize(m_size+desiredSize);
    memcpy(m_data+m_size,&val,desiredSize);
    m_size +=desiredSize;
}

void Packet::pushString(QString val)
{
    QByteArray ba = val.toLatin1()+ '\0';
    long long int desiredSize = ba.size();
    qInfo() << ba.size();
    adaptSize(m_size+desiredSize);
    memcpy(m_data+m_size,ba.data(),desiredSize);
    m_size +=desiredSize;
}

void Packet::adaptSize(long long desired)
{
    if (desired > m_currentSize)
    {
        qWarning() << "WARNING: Adapting packet size, shouldn't happen:" << m_currentSize << desired;
        char * redata = new char[desired];
        memcpy(redata,m_data,m_size);
        delete m_data;
        m_data = redata;
        m_currentSize = desired;
    }
}

}
}
