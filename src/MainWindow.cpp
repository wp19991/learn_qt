//
// Created by Admin on 2022/11/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "Forms/ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //连接action与函数的信号槽
    connect(ui->actionlogin, &QAction::triggered, this, &MainWindow::action_login_clicked);
    connect(ui->actionlogout, &QAction::triggered, this, &MainWindow::action_logout_clicked);
    connect(ui->actionrequest_example, &QAction::triggered, this, &MainWindow::action_request_example_clicked);
    connect(ui->actiontcp_example, &QAction::triggered, this, &MainWindow::action_tcp_example_clicked);
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

void MainWindow::action_request_example_clicked() {
    this->main_widget = new LearnNetworkWidget();
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
        ui->main_layout->addWidget(m_w);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::Button btn = QMessageBox::question(this, "关闭窗口", "您确定要关闭窗口吗?");
    if (btn == QMessageBox::Yes) {
        // 接收并处理这个事件，因为这是主窗口，所以直接关闭整个程序
        QApplication *app;
        app->exit(0);
        event->accept();
    } else {
        // 忽略这个事情
        event->ignore();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QString dx = QString::number(event->size().width());
    dx.append("*");
    dx.append(QString::number(event->size().height()));
    this->change_window_title(dx);
    qDebug() << "oldSize: " << event->oldSize() << "currentSize: " << event->size();
}

void MainWindow::action_tcp_example_clicked() {
    this->main_widget = new TcpServer();
    this->clear_and_add_main_widget(this->main_widget);

    auto *tcp_client_widget = new TcpClient();
    tcp_client_widget->setWindowModality(Qt::NonModal);
    tcp_client_widget->setWindowTitle(tr("Tcp客户端窗口"));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/icon/program.png"), QSize(), QIcon::Normal, QIcon::Off);
    tcp_client_widget->setWindowIcon(icon);
    tcp_client_widget->setGeometry(0,0,400,300);
    tcp_client_widget->show();
}
