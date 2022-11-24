//
// Created by Admin on 2022/11/24.
//

#ifndef UNTITLED_MAINWINDOW_H
#define UNTITLED_MAINWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void on_pushButton_clicked();

private:
    int chick_num=0;
    Ui::MainWindow *ui;
};


#endif //UNTITLED_MAINWINDOW_H
