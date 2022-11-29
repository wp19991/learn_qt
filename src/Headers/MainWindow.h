//
// Created by wp19991 on 2022/11/25.
//

#ifndef QT_CHART_MAINWINDOW_H
#define QT_CHART_MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>

#include "LoginWidget.h"
#include "TcpServerWidget.h"
#include "TcpClientWidget.h"
#include "LearnNetworkWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QWidget *main_widget{};//主界面，可以根据action的按钮进行更换

    void clear_and_add_main_widget(QWidget *m_w);

    // 重写关闭事件处理器函数
    void closeEvent(QCloseEvent *event) override;

    // 重写改变大小事件处理器函数
    void resizeEvent(QResizeEvent *event) override;

    void action_login_clicked();

    void action_logout_clicked();

    void action_request_example_clicked();

    void action_tcp_example_clicked();

    void change_window_title(const QString &add_something);
};


#endif //QT_CHART_MAINWINDOW_H
