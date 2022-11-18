#include "mainWin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile classicStyleQss(":/qss/classicStyle.qss");
    if (classicStyleQss.open(QFile::ReadOnly))
    {
        a.setStyleSheet(classicStyleQss.readAll());
    }

    classicStyleQss.close();
    MainWin w;
    w.show();
    return a.exec();
}
