#include "mainWin.h"

#include <QApplication>

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
    MainWin w;
    w.show();
    return app.exec();
}
