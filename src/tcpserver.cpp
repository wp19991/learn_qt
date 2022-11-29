//
// Created by Admin on 2022/11/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TcpServer.h" resolved

#include "tcpserver.h"
#include "Forms/ui_TcpServer.h"


TcpServer::TcpServer(QWidget *parent) :
        QWidget(parent), ui(new Ui::TcpServer) {
    ui->setupUi(this);

    this->m_server = new QTcpServer(this);
    //更新ip地址
    ui->ip_lineEdit->setText(UtilTools::get_localhost_address());

    // 检测是否有新的客户端连接
    connect(m_server, &QTcpServer::newConnection, this, [=]() {
        this->m_tcp = this->m_server->nextPendingConnection();
        ui->msg_textEdit->append("成功和客户端建立了新的连接...");
        ui->state_label->setText("连接成功");
        // 检测是否有客户端数据
        connect(m_tcp, &QTcpSocket::readyRead, this, [=]() {
            // 接收数据
            QString recvMsg = m_tcp->readAll();
            ui->msg_textEdit->append("tcp_client: " + recvMsg);
        });
        // 客户端断开了连接
        connect(m_tcp, &QTcpSocket::disconnected, this, [=]() {
            ui->msg_textEdit->append("客户端已经断开了连接...");
            this->m_tcp->deleteLater();
            ui->state_label->setText("连接失败");
            ui->start_server_pushButton->setEnabled(true);
        });
    });

    //连接action与函数的信号槽
    connect(ui->start_server_pushButton, &QPushButton::clicked,
            this, &TcpServer::start_server_pushButton_clicked);
    connect(ui->send_msg_pushButton, &QPushButton::clicked,
            this, &TcpServer::send_msg_pushButton_clicked);
}

TcpServer::~TcpServer() {
    delete ui;
}

void TcpServer::start_server_pushButton_clicked() {
    unsigned short port = ui->port_lineEdit->text().toInt();

    //更新ip地址
    ui->ip_lineEdit->setText(UtilTools::get_localhost_address());

    // 设置服务器监听
    this->m_server->listen(QHostAddress::Any, port);
    ui->start_server_pushButton->setEnabled(false);
    ui->state_label->setText("启动成功");
}

void TcpServer::send_msg_pushButton_clicked() {
    QString sendMsg = ui->send_msg_textEdit->toPlainText();
    m_tcp->write(sendMsg.toUtf8());
    ui->msg_textEdit->append("tcp_server: " + sendMsg);
}

