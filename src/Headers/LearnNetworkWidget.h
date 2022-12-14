//
// Created by wp19991 on 2022/11/27.
//

#ifndef LEARN_QT_LEARNNETWORKWIDGET_H
#define LEARN_QT_LEARNNETWORKWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkConfiguration>
#include <QFile>
#include <QElapsedTimer>

#include <UtilTools.h>

QT_BEGIN_NAMESPACE
namespace Ui { class LearnNetworkWidget; }
QT_END_NAMESPACE

class LearnNetworkWidget : public QWidget {
Q_OBJECT

public:
    explicit LearnNetworkWidget(QWidget *parent = nullptr);

    ~LearnNetworkWidget() override;

private:
    Ui::LearnNetworkWidget *ui;
    QNetworkAccessManager *net_manager;

    QNetworkRequest *request;
    QNetworkReply *reply;
    QFile *file;
    QElapsedTimer *file_download_start;

    void net_finish();

    void on_ready_read();

    void progress_change(qint64 bytesReceived, qint64 bytesTotal);

    void pushButton_clicked();

    void select_save_file_path_pushButton_clicked();
};

#endif //LEARN_QT_LEARNNETWORKWIDGET_H
