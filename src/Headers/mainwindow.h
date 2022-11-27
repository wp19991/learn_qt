//
// Created by Admin on 2022/11/25.
//

#ifndef QT_CHART_MAINWINDOW_H
#define QT_CHART_MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"
#include "learnnetworkwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void action_login_clicked();

    void action_logout_clicked();

    void change_window_title(const QString& add_something);
private:
    Ui::MainWindow *ui;
    QWidget *main_widget{};//主界面，可以根据action的按钮进行更换
    void clear_and_add_main_widget(QWidget *m_w);
};


#endif //QT_CHART_MAINWINDOW_H
