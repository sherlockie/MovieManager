#include "mainWin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile classicStyleQss(":/qss/classicStyle.qss");
    if (classicStyleQss.open(QFile::ReadOnly))
    {
        QByteArray qssStyle = classicStyleQss.readAll();
        qssStyle.replace("@color1", "#363636");
        qssStyle.replace("@color2", "#4F4F4F");
        qssStyle.replace("@color3", "#696969");
        qssStyle.replace("@color4", "#1F4e5F");
        qssStyle.replace("@color5", "#79A8A9");
        qssStyle.replace("@color6", "#AACFD0");
        qssStyle.replace("@color7", "#CACACA");
        qssStyle.replace("@color8", "#F8F8F8");
        app.setStyleSheet(qssStyle);
    }

    classicStyleQss.close();
    MainWin w;
    w.show();
    return app.exec();
}
