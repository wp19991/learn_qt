//
// Created by Admin on 2022/11/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "string"
#include "Forms/ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->label->setText("please chick the button");
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked);
}

void MainWindow::on_pushButton_clicked() {
    this->chick_num++;
    QString a;
    a.append("chicked") ;
    a.append(QString::number(this->chick_num));
    ui->label->setText(a);
}

MainWindow::~MainWindow() {
    delete ui;
}

