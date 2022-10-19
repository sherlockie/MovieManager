#include "mainWin.h"
#include "homepage.h"
#include "searchpage.h"
#include "infowin.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QStackedWidget>
#include <QListWidget>
#include <QAction>
#include <QDebug>
#include <QFile>
#include <QFrame>

MainWin::MainWin(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QString("Movie Manager"));
    this->resize(1600, 900);
    this->setWindowFlag(Qt::FramelessWindowHint); // frameless window
    this->setStyleSheet("background-color:black;");
    // set moveable area
    this->m_areaMoveable = QRect(0, 0, 1600, 40);
    // init
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(1);
    QFrame *topBarFrame = new QFrame();
    topBarFrame->setStyleSheet("background-color:#FF282828");
    QHBoxLayout *topBarLayout = new QHBoxLayout();

    QPushButton *menuButton = new QPushButton(topBarFrame);
    menuButton->setIcon(QIcon(":/icons/Resources/menu.png"));
    menuButton->setFlat(true);
    initMenu();
    menuButton->setMenu(menu);

    QPushButton *homeButton = new QPushButton(topBarFrame);
    homeButton->setIcon(QIcon(":/icons/Resources/home.png"));
    homeButton->setFlat(true);
    connect(homeButton, SIGNAL(clicked()), this, SLOT(homeButtonClicked()));

    QPushButton *searchButton = new QPushButton(topBarFrame);
    searchButton->setIcon(QIcon(":/icons/Resources/search.png"));
    searchButton->setFlat(true);
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));

    QPushButton *closeButton = new QPushButton(topBarFrame);
    closeButton->setIcon(QIcon(":/icons/Resources/close.png"));
    closeButton->setFlat(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
    topBarFrame->setLayout(topBarLayout);

    topBarLayout->addWidget(menuButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(homeButton);
    topBarLayout->addWidget(searchButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(closeButton);

    HomePage *homepage = new HomePage();
    SearchPage *searchpage = new SearchPage();

//    QListWidget *pageList = new QListWidget();
//    pageList->insertItem(0, "homepage");
//    pageList->insertItem(1, "searchpage");
    mainLayout->addWidget(topBarFrame);
    pageStack = new QStackedWidget(this);
    pageStack->addWidget(homepage);
    pageStack->addWidget(searchpage);

//    mainLayout->addWidget(pageList);
    mainLayout->addWidget(pageStack);
//    connect(pageList, SIGNAL(currentItemChanged(int)), pageStack, SLOT(setCurrentIndex(int)));

    this->setLayout(mainLayout);
}

void MainWin::closeButtonClicked()
{
    this->close();
}

void MainWin::homeButtonClicked()
{
    pageStack->setCurrentIndex(0);
}

void MainWin::searchButtonClicked()
{
    pageStack->setCurrentIndex(1);
}

void MainWin::aboutActionTriggered()
{
//    qDebug() << "info";
    infoWin *info = new infoWin();
    info->show();
}

MainWin::~MainWin()
{
}

void MainWin::initMenu()
{
    menu = new QMenu();
    QFile menuQssFile(":/qss/menu.qss");
    if (menuQssFile.open(QFile::ReadOnly))
    {
        menu->setStyleSheet(menuQssFile.readAll());
    }
    menuQssFile.close();

    QAction *addNewAction = new QAction(menu);
    addNewAction->setText("Add new film");
    QAction *aboutAction = new QAction(menu);
    aboutAction->setText("About");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutActionTriggered()));

    menu->addAction(addNewAction);
    menu->addAction(aboutAction);
}

void MainWin::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_pressedMousePos = event->pos();
        m_mousePressed = m_areaMoveable.contains(m_pressedMousePos);
    }
}

void MainWin::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePressed = false;
}

void MainWin::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mousePressed)
    {
        move(pos() + event->pos() - m_pressedMousePos);
    }
}
