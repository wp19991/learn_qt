//
// Created by wp19991 on 2022/11/26.
//


#include "UtilTools.h"

QString UtilTools::setting_get_info(const QString &prefix,
                                    const QString &key,
                                    bool is_format_base64 = false) {
    QString path = "./user.ini";
    auto *config = new QSettings(path, QSettings::IniFormat);
    QString value = config->value(prefix + "/" + key).toString();
    if (is_format_base64) {
        QByteArray uidb64 = QByteArray::fromBase64(value.toLocal8Bit());
        return QString::fromLocal8Bit(uidb64);
    }
    return value;
}

void UtilTools::setting_save_info(const QString &prefix,
                                  const QString &key,
                                  const QString &value,
                                  bool is_format_base64 = false) {
    QString path = "./user.ini";
    auto *config = new QSettings(path, QSettings::IniFormat);
    QString format_after;
    if (is_format_base64) {
        // 用户名base64加密
        QByteArray uidb64 = value.toLocal8Bit().toBase64();
        format_after = QString::fromLocal8Bit(uidb64);
    } else {
        format_after = value;
    }

    // 将信息写入配置文件
    config->beginGroup(prefix);
    config->setValue(key, format_after);
    config->endGroup();
}

void UtilTools::change_main_window_title(QObject *widget_parent_to_main_window,
                                         const QString &add_something) {

    QObject *a = widget_parent_to_main_window;
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

QString UtilTools::get_desktop_path() {
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);;
}

QString UtilTools::get_file_context(const QString &file_path) {
    auto *resp_file = new QFile(file_path);
    if (resp_file->open(QFile::ReadOnly)) {
        QTextStream in(resp_file);
        in.setCodec("UTF-8");
        QString res = in.readAll().toHtmlEscaped();
        resp_file->close();
        delete resp_file;
        return res;
    }
    resp_file->close();
    delete resp_file;
    return QString();
}

QString UtilTools::safe_get_file_name(const QString &file_network_path) {
    QString res = file_network_path.section('/', -1).split("?")[0];
    res.replace("\\", "_");
    res.replace("/", "_");
    res.replace(":", "_");
    res.replace("*", "_");
    res.replace("?", "_");
    res.replace("\"", "_");
    res.replace("<", "_");
    res.replace(">", "_");
    if (res.size() == 0) {
        // 如果大小为0的情况就找-2的位置，因为有的时候会出现下面的情况
        // https://www.bilibili.com/video/BV1nP411w7tx/?spm_id_from=333.1007.tianma.1-1-1.click
        res = file_network_path.section('/', -2).split("/")[0];
        res.replace("\\", "_");
        res.replace("/", "_");
        res.replace(":", "_");
        res.replace("*", "_");
        res.replace("?", "_");
        res.replace("\"", "_");
        res.replace("<", "_");
        res.replace(">", "_");
    }
    return res;
}

QString UtilTools::safe_splice_path_and_path(const QString &pre_path, const QString &after_path) {
    QString res = QDir::cleanPath(pre_path + QDir::separator() + after_path);
    return res;
}

QString UtilTools::get_localhost_address() {
    //获取主机名
    QString localHostName = QHostInfo::localHostName();
    //获取本机的IP地址(可能有多条）
    QHostInfo info = QHostInfo::fromName(localHostName);
    for (int i = 0; i < info.addresses().size(); ++i) {
        if (info.addresses()[i].protocol() == QAbstractSocket::IPv4Protocol) {
            return info.addresses()[i].toString();
        }
    }
    return QString();
}
