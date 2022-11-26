//
// Created by Admin on 2022/11/26.
//

#include "UtilTools.h"

QString UtilTools::get_info(const QString &prefix,
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

void UtilTools::save_info(const QString &prefix,
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
