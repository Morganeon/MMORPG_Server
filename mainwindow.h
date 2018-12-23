#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include "NetworkObjects/mmoclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<MMOClient *> m_clientList;


private:

    void onNewConnection();
    void clearData();



    Ui::MainWindow * ui;
    QTcpServer * m_server;
    quint16 m_port = 2100;
};

#endif // MAINWINDOW_H
