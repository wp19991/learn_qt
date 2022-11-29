//
// Created by Admin on 2022/11/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWidget.h" resolved


#include "LoginWidget.h"
#include "Forms/ui_LoginWidget.h"


LoginWidget::LoginWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::LoginWidget) {
    ui->setupUi(this);

    // 如果之前登录过，就读取之前的配置信息更新ui显示
    QString username = UtilTools::setting_get_info("user_info", "username", false);
    QString password = UtilTools::setting_get_info("user_info", "password", true);
    ui->username_lineEdit->setText(username);
    ui->password_lineEdit->setText(password);

    //连接action与函数的信号槽
    connect(ui->login_pushButton, &QPushButton::clicked, this, &LoginWidget::login_pushButton_clicked);
    connect(ui->register_pushButton, &QPushButton::clicked, this, &LoginWidget::register_pushButton_clicked);
}

LoginWidget::~LoginWidget() {
    delete ui;
}


void LoginWidget::login_pushButton_clicked() {
    QString user_name = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();
    if (password != "123") {
        ui->state_label->setText("密码错误");
        UtilTools::setting_save_info("user_info", "password", "", true);
        return;
    }
    UtilTools::setting_save_info("user_info", "username", user_name, false);
    UtilTools::setting_save_info("user_info", "password", password, true);
//    this->change_parent_title(ui->username_lineEdit->text());
    QObject *parent_to_main_window = this->parent()->parent();
    UtilTools::change_main_window_title(parent_to_main_window,
                                        ui->username_lineEdit->text());
    ui->state_label->setText("登录成功");
}

void LoginWidget::register_pushButton_clicked() {
    QString user_name = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();
    UtilTools::setting_save_info("user_info", "username", user_name, false);
    UtilTools::setting_save_info("user_info", "password", password, true);
    QObject *parent_to_main_window = this->parent()->parent();
    UtilTools::change_main_window_title(parent_to_main_window,
                                        ui->username_lineEdit->text());
    ui->state_label->setText("注册成功");
}

