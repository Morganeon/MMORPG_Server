#ifndef MMOCLIENT_H
#define MMOCLIENT_H

#include <QTcpSocket>

class MainWindow;



class MMOClient : public QObject
{
    Q_OBJECT
public:
    explicit MMOClient(MainWindow * parent, QTcpSocket * socket);
    void sendSnapshot();


private:
    QTcpSocket * m_socket;
    MainWindow * m_main;
    void onReadyRead();
    void receiveUpdate();
    void sendUpdate();
    void onDisconnected();

    static int count;

    qint32 m_id = 0;
    float m_x=0;
    float m_y=0;
    float m_angle = 0;
    qint32 m_r=0;
    qint32 m_g=0;
    qint32 m_b=0;
};

#endif // MMOCLIENT_H
