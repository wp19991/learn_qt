//
// Created by wp19991 on 2022/11/29.
//

#ifndef LEARN_QT_TCPCLIENTWIDGET_H
#define LEARN_QT_TCPCLIENTWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpClient; }
QT_END_NAMESPACE

class TcpClient : public QWidget {
Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = nullptr);

    ~TcpClient() override;

private:
    Ui::TcpClient *ui;
    QTcpSocket* m_tcp;

    void connect_server_pushButton_clicked();

    void send_msg_pushButton_clicked();

    void disconnect_server_pushButton_clicked();
};


#endif //LEARN_QT_TCPCLIENTWIDGET_H
