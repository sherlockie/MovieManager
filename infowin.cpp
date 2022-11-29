#include "infowin.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QGuiApplication>
#include <QScreen>
#include <QFrame>

infoWin::infoWin(QWidget *parent)
    : QWidget{parent}
{
    this->setObjectName("infoWin");
    this->setWindowFlags(Qt::Popup);
    this->resize(180, 340);
    QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
    int w = screenRect.width();
    int h = screenRect.height();
    move(w / 2 - 90, h / 2 - 120);
    // init widgets
    QLabel *logoLabel = new QLabel(this);
    logoLabel->setObjectName("logoLabel");
    logoLabel->setAlignment(Qt::AlignHCenter);
    QLabel *versionLabel = new QLabel(this);
    versionLabel->setText("Version: alpha 0.0.1");
    versionLabel->setAlignment(Qt::AlignHCenter);
    QLabel *ttLabel = new QLabel(this);
    ttLabel->setText("All right preserved.");
    ttLabel->setAlignment(Qt::AlignHCenter);

    QVBoxLayout *mainlayout = new QVBoxLayout();
    mainlayout->setMargin(5);
    QFrame *mainFrame = new QFrame();
    mainFrame->setObjectName("mainFrame");
    QVBoxLayout *infolayout = new QVBoxLayout();
    infolayout->setAlignment(Qt::AlignHCenter);
    infolayout->addWidget(logoLabel, 3);
    infolayout->addWidget(versionLabel, 1);
    infolayout->addWidget(ttLabel, 1);
    infolayout->addStretch(5);
    mainFrame->setLayout(infolayout);

    mainlayout->addWidget(mainFrame);
    this->setLayout(mainlayout);

//    setFocus();
}
