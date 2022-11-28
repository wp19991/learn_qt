//
// Created by Admin on 2022/11/26.
//

#ifndef QT_CHART_UTILTOOLS_H
#define QT_CHART_UTILTOOLS_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QSettings>
#include <QTextStream>
#include <QStandardPaths>

class UtilTools {

public:
    static QString get_desktop_path();

    static QString safe_get_file_name(const QString &file_network_path);

    static QString safe_splice_path_and_path(const QString &pre_path, const QString &after_path);

    static QString get_file_context(const QString &file_path);

    static void main_layout_widget_change_main_windows_title(QObject *main_layout_widget_parent_to_main_window,
                                                             const QString &add_something);

    static void setting_save_info(const QString &prefix,
                                  const QString &key,
                                  const QString &value,
                                  bool is_format_base64);

    static QString setting_get_info(const QString &prefix,
                                    const QString &key,
                                    bool is_format_base64);
};


#endif //QT_CHART_UTILTOOLS_H
