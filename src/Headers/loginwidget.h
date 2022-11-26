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

    void login_pushButton_clicked();
    void register_pushButton_clicked();

private:
    Ui::LoginWidget *ui;

    void change_parent_title(const QString &add_something);
};


#endif //QT_CHART_LOGINWIDGET_H
