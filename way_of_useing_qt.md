- 修改标签属性
```c++
//常规办法
ui->label->setText("hello");
//取巧办法
ui->label->setProperty("text", "hello");
//属性大法
ui->label->setStyleSheet("qproperty-text:hello;");
```
- 获取系统环境变量
```c++
QString a = qEnvironmentVariable("path");
ui->label->setText(a);
```
- 设置图标
    - [图标对照](https://blog.csdn.net/WU9797/article/details/86386977)
```c++
#include <QStyle>
...
QPixmap pixmap = this->style()->standardPixmap(QStyle::SP_TitleBarMenuButton);
this->setWindowIcon(pixmap);
...
```
- 应用程序缩放比例
  - 必须写在main函数的QApplication a(argc, argv);的前面
```c++
qputenv("QT_SCALE_FACTOR", "2.0");
```
- 高分屏属性以便支持2K4K等高分辨率
  - 必须写在main函数的QApplication a(argc, argv);的前面
```c++
QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
```

