//
// Created by wp19991 on 2022/11/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TcpClient.h" resolved

#include "TcpClientWidget.h"
#include "Forms/ui_TcpClientWidget.h"


TcpClient::TcpClient(QWidget *parent) :
        QWidget(parent), ui(new Ui::TcpClient) {
    ui->setupUi(this);

    // 创建通信的套接字对象
    this->m_tcp = new QTcpSocket(this);
    // 检测服务器是否回复了数据
    connect(this->m_tcp, &QTcpSocket::readyRead, [=]()
    {
        // 接收服务器发送的数据
        QByteArray recvMsg = this->m_tcp->readAll();
        ui->msg_textEdit->append("tcp_server: " + recvMsg);
    });

    // 检测是否和服务器是否连接成功了
    connect(this->m_tcp, &QTcpSocket::connected, this, [=]()
    {
        ui->msg_textEdit->append("恭喜, 连接服务器成功!!!");
        ui->connect_server_pushButton->setEnabled(false);
        ui->disconnect_server_pushButton->setEnabled(true);
        ui->state_label->setText("连接成功");
        ui->send_msg_pushButton->setEnabled(true);
    });

    // 检测服务器是否和客户端断开了连接
    connect(this->m_tcp, &QTcpSocket::disconnected, this, [=]()
    {
        ui->msg_textEdit->append("服务器已经断开了连接, ...");
        ui->connect_server_pushButton->setEnabled(true);
        ui->disconnect_server_pushButton->setEnabled(false);
        ui->send_msg_pushButton->setEnabled(false);
    });

    ui->disconnect_server_pushButton->setEnabled(false);
    ui->send_msg_pushButton->setEnabled(false);
    //连接action与函数的信号槽
    connect(ui->connect_server_pushButton, &QPushButton::clicked,
            this, &TcpClient::connect_server_pushButton_clicked);
    connect(ui->send_msg_pushButton, &QPushButton::clicked,
            this, &TcpClient::send_msg_pushButton_clicked);
    connect(ui->disconnect_server_pushButton, &QPushButton::clicked,
            this, &TcpClient::disconnect_server_pushButton_clicked);
}

TcpClient::~TcpClient() {
    delete ui;
}

void TcpClient::connect_server_pushButton_clicked() {
    QString ip = ui->ip_lineEdit->text();
    unsigned short port = ui->port_lineEdit->text().toInt();
    // 连接服务器
    this->m_tcp->connectToHost(QHostAddress(ip), port);
}

void TcpClient::send_msg_pushButton_clicked() {
    QString sendMsg = ui->send_msg_textEdit->toPlainText();
    this->m_tcp->write(sendMsg.toUtf8());
    ui->msg_textEdit->append("tcp_client: " + sendMsg);
}

void TcpClient::disconnect_server_pushButton_clicked() {
    this->m_tcp->close();
    ui->connect_server_pushButton->setEnabled(true);
    ui->disconnect_server_pushButton->setEnabled(false);
}

