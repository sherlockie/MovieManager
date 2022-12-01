#include "mainWin.h"
#include "homepage.h"
#include "searchpage.h"
#include "infowin.h"
#include "addnew.h"
#include "detailpage.h"
#include "mainsettingpage.h"
#include "library.h"

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
    this->setObjectName("mainWin");
    //this->setStyleSheet("QWidget#mainWin{background-color:black;}");

    QPalette pal =this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/images/Resources/background-m.jpg")));
    this->setPalette(pal);
    // this->setContentsMargins(1, 1, 1, 1);
    // set moveable area
    this->m_areaMoveable = QRect(0, 0, 1600, 40);
    // init
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(1);

    QFrame *topBarFrame = new QFrame();
    topBarFrame->setObjectName("topBarFrame");
    topBarFrame->setMaximumHeight(42);
    //topBarFrame->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    topBarLayout->setContentsMargins(1, 1, 1, 1);

    QPushButton *menuButton = new QPushButton(topBarFrame);
    menuButton->setObjectName("menuButton");
    //menuButton->setIcon(QIcon(":/icons/Resources/menu.png"));
    menuButton->setFixedSize(40, 40);
    initMenu();
    menuButton->setMenu(menu);

    QPushButton *homeButton = new QPushButton(topBarFrame);
    homeButton->setObjectName("homeButton");
    //homeButton->setIcon(QIcon(":/icons/Resources/home.png"));
    homeButton->setFixedSize(40, 40);
    connect(homeButton, SIGNAL(clicked()), this, SLOT(homeButtonClicked()));

    QPushButton *libraryButton = new QPushButton(topBarFrame);
    libraryButton->setObjectName("libraryButton");
    //libraryButton->setIcon(QIcon(":/icons/Resources/home.png"));
    libraryButton->setFixedSize(40, 40);
    connect(libraryButton, SIGNAL(clicked()), this, SLOT(libraryButtonClicked()));

    QPushButton *searchButton = new QPushButton(topBarFrame);
    searchButton->setObjectName("searchButton");
    //searchButton->setIcon(QIcon(":/icons/Resources/search.png"));
    searchButton->setFixedSize(40, 40);
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));

    QPushButton *detailButton = new QPushButton(topBarFrame);
    detailButton->setObjectName("detailButton");
    //detailButton->setIcon(QIcon(":/icons/Resources/details.png"));
    detailButton->setFixedSize(40, 40);
    connect(detailButton, SIGNAL(clicked()), this, SLOT(detailButtonClicked()));

    QPushButton *closeButton = new QPushButton(topBarFrame);
    closeButton->setObjectName("closeButton");
    //closeButton->setIcon(QIcon(":/icons/Resources/close.png"));
    closeButton->setFixedSize(40, 40);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
    topBarFrame->setLayout(topBarLayout);

    topBarLayout->addWidget(menuButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(homeButton);
    topBarLayout->addWidget(libraryButton);
    topBarLayout->addWidget(searchButton);
    topBarLayout->addWidget(detailButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(closeButton);

    HomePage *homepage = new HomePage(this);
    library *libraryPage = new library();
    //homepage->setAutoFillBackground(true);
    SearchPage *searchpage = new SearchPage(this);
    detailPage *detailpage = new detailPage(this);

    // QListWidget *pageList = new QListWidget();
    // pageList->insertItem(0, "homepage");
    // pageList->insertItem(1, "searchpage");
    mainLayout->addWidget(topBarFrame);
    pageStack = new QStackedWidget(this);
    pageStack->addWidget(homepage);
    pageStack->addWidget(libraryPage);
    pageStack->addWidget(searchpage);
    pageStack->addWidget(detailpage);
    connect(searchpage, SIGNAL(cardClickedSignal(int)), this, SLOT(cardClicked(int)));

//    mainLayout->addWidget(pageList);
    mainLayout->addWidget(pageStack);

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

void MainWin::libraryButtonClicked()
{
    pageStack->setCurrentIndex(1);
}

void MainWin::searchButtonClicked()
{
    pageStack->setCurrentIndex(2);
}

void MainWin::detailButtonClicked()
{
    pageStack->setCurrentIndex(3);
}

void MainWin::cardClicked(int i)
{
    qDebug() << "id:" << i;
    pageStack->setCurrentIndex(3);
}

void MainWin::aboutActionTriggered()
{
//    qDebug() << "info";
    infoWin *info = new infoWin();
    info->show();
}

void MainWin::addNewActionTriggered()
{
    AddNewDialog *addNew = new AddNewDialog();
    addNew->exec();
}

void MainWin::settingActionTriggered()
{
    mainSettingPage *settingPage = new mainSettingPage();
    settingPage->exec();
}

MainWin::~MainWin()
{
}

void MainWin::initMenu()
{
    menu = new QMenu();
    menu->setObjectName("topMenu");

    QAction *addNewAction = new QAction(menu);
    addNewAction->setText("添加新电影");
    connect(addNewAction, SIGNAL(triggered(bool)), this, SLOT(addNewActionTriggered()));
    QAction *settingAction = new QAction(menu);
    settingAction->setText("设置");
    connect(settingAction, SIGNAL(triggered()), this, SLOT(settingActionTriggered()));
    QAction *aboutAction = new QAction(menu);
    aboutAction->setText("关于");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutActionTriggered()));

    menu->addAction(addNewAction);
    menu->addAction(settingAction);
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
