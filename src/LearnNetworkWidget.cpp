//
// Created by Admin on 2022/11/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LearnNetworkWidget.h" resolved


#include "LearnNetworkWidget.h"
#include "Forms/ui_LearnNetworkWidget.h"


LearnNetworkWidget::LearnNetworkWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::LearnNetworkWidget) {
    ui->setupUi(this);

    // 初始化参数
    this->file_download_start = new QElapsedTimer;
    this->net_manager = new QNetworkAccessManager(this);
    this->file = nullptr;
    this->reply = nullptr;

    // 设置请求支持https 还需要根据readme里面进行添加https的支持
    this->request = new QNetworkRequest;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    this->request->setSslConfiguration(config);

    // 初始化显示
    ui->save_file_path_lineEdit->setText(UtilTools::get_desktop_path());

    // 连接action与函数的信号槽
    connect(ui->pushButton, &QPushButton::clicked,
            this, &LearnNetworkWidget::pushButton_clicked);
    connect(ui->select_save_file_path_pushButton, &QPushButton::clicked,
            this, &LearnNetworkWidget::select_save_file_path_pushButton_clicked);
    connect(this->net_manager, &QNetworkAccessManager::finished,
            this, &LearnNetworkWidget::net_finish);
}

LearnNetworkWidget::~LearnNetworkWidget() {
    delete file_download_start;
    delete net_manager;
    delete request;
    delete file;
    delete reply;
    delete ui;
}

void LearnNetworkWidget::select_save_file_path_pushButton_clicked() {
    QString selectDir = QFileDialog::getExistingDirectory(this,
                                                          tr("选择下载保存的文件夹"),
                                                          UtilTools::get_desktop_path(),
                                                          QFileDialog::ShowDirsOnly);
    ui->save_file_path_lineEdit->setText(selectDir);
}

void LearnNetworkWidget::pushButton_clicked() {
    // 设置当前时间对象的值为当前系统时间
    this->file_download_start->restart();
    if (this->net_manager) {
        QUrl t_url = QUrl(ui->url_lineEdit->text());
        // 获得文件名称
        QString file_name = UtilTools::safe_get_file_name(ui->url_lineEdit->text());
        QString file_save_path = ui->save_file_path_lineEdit->text();
        ui->url_lineEdit->setDisabled(true);
        ui->save_file_path_lineEdit->setDisabled(true);
        QString file_path = UtilTools::safe_splice_path_and_path(file_save_path, file_name);
        this->file = new QFile(file_path);
        if (this->file->open(QIODevice::WriteOnly)) {
            this->request->setUrl(t_url);
            // TODO 附带header请求
            // TODO 更改请求方式
            this->reply = this->net_manager->get(*this->request);
            connect(this->reply, &QNetworkReply::readyRead, this, &LearnNetworkWidget::on_ready_read);
            connect(this->reply, &QNetworkReply::downloadProgress, this, &LearnNetworkWidget::progress_change);
        }
    }
}

void LearnNetworkWidget::on_ready_read() {
    //在这个槽里 找到刚刚保存的file指针 一直写数据
    this->file->write(this->reply->readAll());
}

void LearnNetworkWidget::progress_change(qint64 bytesReceived, qint64 bytesTotal) {
    // 返回最后一次调用start()或restart()到现在已经经过的毫秒数
    qint64 after_ms = this->file_download_start->elapsed();
    int after_s = (int) (after_ms / 1000);
    // 注意下面计算速度可能秒为0，这里调整为1
    if (after_s == 0) { after_s = 1; }

    qint64 kbTotal = bytesTotal / 1024;
    qint64 mbTotal = kbTotal / 1024;

    qint64 kbReceived = bytesReceived / 1024;
    qint64 mbReceived = kbReceived / 1024;
    if (kbTotal == 0) { kbTotal = 1; }
    int value = (int) (kbReceived * 100 / kbTotal);
    ui->progressBar->setValue(value);

    if (kbTotal < 10240) {
        // 如果小于10mb，文字显示kb的进度
        ui->rate_label->setText(QString::number(kbReceived) + "kb/" + QString::number(kbTotal) + "kb");
        // 显示计算速度
        int sp = (int) (kbReceived / after_s);
        ui->speed_label->setText(QString::number(sp) + "kb/s");
    } else {
        // 如果大于10mb，文字显示mb的进度
        ui->rate_label->setText(QString::number(mbReceived) + "mb/" + QString::number(mbTotal) + "mb");
        // 显示计算速度
        int sp = (int) (mbReceived / after_s);
        ui->speed_label->setText(QString::number(sp) + "mb/s");
    }
}

void LearnNetworkWidget::net_finish() {
    // 结束完成的处理数据
    this->file->close();
    delete this->file;
    this->file = nullptr;
    this->reply->deleteLater();
    ui->state_label->setText("ok");
    ui->progressBar->setValue(100);
    // 输出文件路径
    QString file_name = UtilTools::safe_get_file_name(ui->url_lineEdit->text());
    QString file_save_path = ui->save_file_path_lineEdit->text();
    QString file_path = UtilTools::safe_splice_path_and_path(file_save_path, file_name);

    ui->response_textBrowser->setText("文件已经下载在：" + file_path);
    if (file_name.contains(".htm", Qt::CaseSensitive) ||
        !file_name.contains(".", Qt::CaseSensitive)) {
        QString file_context = UtilTools::get_file_context(file_path);
        ui->response_textBrowser->setHtml(file_context);
    }
    ui->url_lineEdit->setDisabled(false);
    ui->save_file_path_lineEdit->setDisabled(false);
}



