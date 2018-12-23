#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_server = new QTcpServer(this);

    m_server->listen(QHostAddress::Any,m_port);
    qInfo()<< "Server listening on" << m_server->serverAddress() << ":" << m_port;
    connect(m_server,&QTcpServer::newConnection,this,&MainWindow::onNewConnection);
    connect(m_server,&QTcpServer::destroyed,this,&MainWindow::clearData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection()
{
    qInfo()<< "New connection";
    MMOClient * client = new MMOClient(this, m_server->nextPendingConnection());
    m_clientList.push_back(client);
    client->sendSnapshot();
}


void MainWindow::clearData()
{
    qInfo() << "Clearing client list";
    for (int i=0;i<m_clientList.size();i++)
    {
        delete m_clientList.at(i);
    }
}
