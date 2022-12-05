#include "mainWin.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile classicStyleQss(":/qss/classicStyle.qss");
    if (classicStyleQss.open(QFile::ReadOnly))
    {
        QByteArray qssStyle = classicStyleQss.readAll();
        qssStyle.replace("@color1", "#080808");
        qssStyle.replace("@color2", "#252525");
        qssStyle.replace("@color3", "#383838");
        qssStyle.replace("@color4", "#FF0033");
        qssStyle.replace("@color5", "#FF6666");
        qssStyle.replace("@color6", "#FFCCCC");
        qssStyle.replace("@color7", "#CACACA");
        qssStyle.replace("@color8", "#F8F8F8");
        app.setStyleSheet(qssStyle);
    }
    classicStyleQss.close();
    // 数据库
    QSqlDatabase dbConn = QSqlDatabase::database("SQLITE");
    dbConn.setDatabaseName(app.applicationDirPath() + "/mb.db");
    if (dbConn.open())
    {
        qDebug() << "数据库创建成功";
    } else
    {
        qDebug() << "数据库创建异常";
    }
    // 开始
    MainWin w;
    w.show();
    return app.exec();
}
