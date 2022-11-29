//
// Created by Admin on 2022/11/26.
//

#ifndef QT_CHART_LOGINWIDGET_H
#define QT_CHART_LOGINWIDGET_H

#include <QWidget>

#include <UtilTools.h>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget {
Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);

    ~LoginWidget() override;


private:
    Ui::LoginWidget *ui;

    void login_pushButton_clicked();

    void register_pushButton_clicked();
};


#endif //QT_CHART_LOGINWIDGET_H
