//
// Created by Admin on 2022/11/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "Forms/ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->main_widget = new LearnNetworkWidget();
    this->clear_and_add_main_widget(this->main_widget);

    //连接action与函数的信号槽
    connect(ui->actionlogin, &QAction::triggered, this, &MainWindow::action_login_clicked);
    connect(ui->actionlogout, &QAction::triggered, this, &MainWindow::action_logout_clicked);
}

MainWindow::~MainWindow() {
    this->clear_and_add_main_widget(nullptr);
    delete ui;
}

void MainWindow::change_window_title(const QString &add_something) {
    // 获取本来的标题
    QString b = this->property("windowTitle").toString();
    b = b.split(" - ")[0];
    if (add_something != nullptr) {
        // 添加分隔符
        b.append(" - ");
        b.append(add_something);
    }
    this->setProperty("windowTitle", b);
}

void MainWindow::action_login_clicked() {
    this->main_widget = new LoginWidget();
    this->clear_and_add_main_widget(this->main_widget);
}

void MainWindow::action_logout_clicked() {
    this->change_window_title(nullptr);
    this->main_widget = new LoginWidget();
    this->clear_and_add_main_widget(this->main_widget);
}

void MainWindow::clear_and_add_main_widget(QWidget *m_w) {
    //删除main_layout里面的所有widget
    QLayoutItem *child = this->ui->main_layout->takeAt(0);
    while (child) {
        this->ui->main_layout->removeWidget(child->widget());// 第一步
        child->widget()->setParent(nullptr);// 第二步
        delete child;// 第三步
        child = this->ui->main_layout->takeAt(0);// 循环
    }
    if (m_w != nullptr) {
        m_w->setParent(this);
    }
    ui->main_layout->addWidget(m_w);
}





