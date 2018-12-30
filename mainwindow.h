#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include "System/realm.h"

namespace Ui {
class MainWindow;
}

using namespace MMO::System;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:

    void onNewConnection();
    void clearData();


    Realm * m_realm;
    Ui::MainWindow * ui;
    quint16 m_port = 2100;
};

#endif // MAINWINDOW_H
