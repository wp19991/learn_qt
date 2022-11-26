//
// Created by Admin on 2022/11/26.
//

#ifndef QT_CHART_UTILTOOLS_H
#define QT_CHART_UTILTOOLS_H

#include <QString>
#include <QSettings>

class UtilTools {

public:
    static void save_info(const QString &prefix, const QString &key,const QString &value, bool is_format_base64);

    static QString get_info(const QString &prefix, const QString &key, bool is_format_base64);
};


#endif //QT_CHART_UTILTOOLS_H
