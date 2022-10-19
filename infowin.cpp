#include "infowin.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QGuiApplication>
#include <QScreen>

infoWin::infoWin(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlags(Qt::Popup);
    this->resize(180, 240);
    this->setStyleSheet("background-color:#FFDEDEDE;");
    QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
    int w = screenRect.width();
    int h = screenRect.height();
    move(w / 2 - 90, h / 2 - 120);
    // init widgets
    QLabel *logoLabel = new QLabel(this);
    logoLabel->setText("Movie Manager@");
    logoLabel->setFont(QFont("Arial Black", 10, QFont::Bold));
    logoLabel->setAlignment(Qt::AlignHCenter);
    QLabel *versionLabel = new QLabel(this);
    versionLabel->setText("Version: alpha 0.0.1");
    versionLabel->setFont(QFont("Microsoft YaHei Light", 6, QFont::Light));
    versionLabel->setAlignment(Qt::AlignHCenter);
    QLabel *ttLabel = new QLabel(this);
    ttLabel->setText("All right preserved.");
    ttLabel->setFont(QFont("Microsoft YaHei Light", 6, QFont::Light));
    ttLabel->setAlignment(Qt::AlignHCenter);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignHCenter);
    layout->addWidget(logoLabel);
    layout->addWidget(versionLabel);
    layout->addWidget(ttLabel);
    layout->addStretch();
    this->setLayout(layout);

//    setFocus();
}
