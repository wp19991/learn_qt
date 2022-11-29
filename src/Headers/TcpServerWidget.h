//
// Created by wp19991 on 2022/11/29.
//

#ifndef LEARN_QT_TCPSERVERWIDGET_H
#define LEARN_QT_TCPSERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>

#include "UtilTools.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TcpServer; }
QT_END_NAMESPACE

class TcpServer : public QWidget {
Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);

    ~TcpServer() override;

private:
    Ui::TcpServer *ui;
    QTcpServer* m_server;
    QTcpSocket* m_tcp;

    void start_server_pushButton_clicked();

    void send_msg_pushButton_clicked();
};


#endif //LEARN_QT_TCPSERVERWIDGET_H
