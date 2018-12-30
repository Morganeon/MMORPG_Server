#ifndef PACKET_H
#define PACKET_H

#include <QString>
namespace MMO
{
namespace System
{
enum PacketHeader
{
    ServerSendKeyboardState,
    ClientSendKeyboardState,
    ServerSendHeartBeat,
    ClientSendHeartBeat,
    ServerSendSnapshot,
    ServerClientEnterRoom,
    ServerClientLeaveRoom,
    ServerSendConnection,
    ServerSendDisconnection,
    ServerSendKick,
    ClientSendKeyAction,
    ServerSendKeyAction,
    ClientSendEnvironmentAction,
    ServerSendEnvironmentAction,
    ClientSendSystemAction,
    ServerSendSystemAction,
    ServerSendMapData

};

class Packet
{
public:
    Packet(long long int base_size);
    ~Packet();
    char *data();
    long long int size();
    void pushHeader(PacketHeader val);
    void pushUnsignedInt32(unsigned long int val);
    void pushInt32(long int val);
    void pushInt64(long long int val);
    void pushFloat32(float val);
    void pushBool(bool val);
    void pushString(QString val);

private:
    void adaptSize(long long int desired);
    char * m_data = nullptr;
    long long int m_currentSize=0;
    long long int m_size=0;
};
}
}

#endif // PACKET_H
