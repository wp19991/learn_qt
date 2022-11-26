//
// Created by Admin on 2022/11/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWidget.h" resolved


#include "loginwidget.h"
#include "Forms/ui_LoginWidget.h"


LoginWidget::LoginWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::LoginWidget) {
    ui->setupUi(this);

    // 如果之前登录过，就读取之前的配置信息更新ui显示
    QString username = UtilTools::get_info("user_info", "username", false);
    QString password = UtilTools::get_info("user_info", "password", true);
    ui->username_lineEdit->setText(username);
    ui->password_lineEdit->setText(password);

    //连接action与函数的信号槽
    connect(ui->login_pushButton, &QPushButton::clicked, this, &LoginWidget::login_pushButton_clicked);
    connect(ui->register_pushButton, &QPushButton::clicked, this, &LoginWidget::register_pushButton_clicked);
}

LoginWidget::~LoginWidget() {
    delete ui;
}

void LoginWidget::change_parent_title(const QString &add_something) {
    QObject *a = this->parent()->parent();
    if (a->isWidgetType()) {
        // 获取本来的标题
        QString b = a->property("windowTitle").toString();
        b = b.split(" - ")[0];
        if (add_something != nullptr) {
            // 添加分隔符
            b.append(" - ");
            b.append(add_something);
        }
        // 设置属性
        a->setProperty("windowTitle", b);
    }
}

void LoginWidget::login_pushButton_clicked() {
    QString user_name = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();
    if (password != "123") {
        ui->state_label->setText("密码错误");
        UtilTools::save_info("user_info", "password", "", true);
        return;
    }
    UtilTools::save_info("user_info", "username", user_name, false);
    UtilTools::save_info("user_info", "password", password, true);
    this->change_parent_title(ui->username_lineEdit->text());
    ui->state_label->setText("登录成功");
}

void LoginWidget::register_pushButton_clicked() {
    QString user_name = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();
    UtilTools::save_info("user_info", "username", user_name, false);
    UtilTools::save_info("user_info", "password", password, true);
    this->change_parent_title(ui->username_lineEdit->text());
    ui->state_label->setText("注册成功");
}


