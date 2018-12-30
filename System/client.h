#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QTimer>




namespace MMO
{
namespace System
{
class Realm;
class Room;
class Entity;

class Client : public QObject
{
    Q_OBJECT

public:
    Client(MMO::System::Realm * parent, QTcpSocket *socket, MMO::System::Room * defaultRoom);

private slots:
    void receiveKeyboardState();
    void receiveHeartBeat();
    void receiveKeyAction();
    void receiveEnvironmentAction();
    void receiveSystemAction();
    void networkError(QAbstractSocket::SocketError socketError);
    void networkTimedOut();
    void readMessage();
private:
    void enterRoom(Room * room);
    void sendKeyboardState();
    void sendHeartBeat();
    void sendKeyAction();
    void sendEnvironmentAction();
    void sendSystemAction();

public:
    void send(char * data, long long int size);
    void forceSend(char * data, long long int size);
    void sendSnapshot();
    void sendDisconnection();
    long long int getId() {return m_id;}
    QTcpSocket * getSocket() {return m_socket;}


private:
    // Network variables
    QTcpSocket * m_socket = nullptr;
    qint64 m_id;
    Room * m_currentRoom = nullptr;
    Realm * m_currentRealm = nullptr;
    Entity * m_entity = nullptr;
    QTimer * m_timer = nullptr;
    short m_heartbeatMissed;
    QMap<QString,bool> m_keyboardState;
    QMap<QString,float> m_analogState;

    // Network parameters
    static int m_heartbeatTimer;
    static qint64 m_count;


};

}
}

#endif // CLIENT_H
