#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    //高分屏属性以便支持2K4K等高分辨率
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
