#include "mainWin.h"
#include "homepage.h"
#include "searchpage.h"
#include "infowin.h"
#include "addnew.h"

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
//    this->setStyleSheet("QWidget#mainWin{background-color:black;}");

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
    topBarFrame->setStyleSheet(
                "background-color:#FF282828;"
                "border:0px none #FF282828;"
                );
    topBarFrame->setMaximumHeight(42);
    //topBarFrame->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    topBarLayout->setContentsMargins(1, 1, 1, 1);

    QPushButton *menuButton = new QPushButton(topBarFrame);
    menuButton->setIcon(QIcon(":/icons/Resources/menu.png"));
    menuButton->setFixedSize(40, 40);
    initMenu();
    menuButton->setMenu(menu);

    QPushButton *homeButton = new QPushButton(topBarFrame);
    homeButton->setIcon(QIcon(":/icons/Resources/home.png"));
    homeButton->setFixedSize(40, 40);
    connect(homeButton, SIGNAL(clicked()), this, SLOT(homeButtonClicked()));

    QPushButton *searchButton = new QPushButton(topBarFrame);
    searchButton->setIcon(QIcon(":/icons/Resources/search.png"));
    searchButton->setFixedSize(40, 40);
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));

    QPushButton *closeButton = new QPushButton(topBarFrame);
    closeButton->setIcon(QIcon(":/icons/Resources/close.png"));
    closeButton->setFixedSize(40, 40);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
    topBarFrame->setLayout(topBarLayout);

    QFile topButtonQssFile(":/qss/topButton.qss");
    if (topButtonQssFile.open(QFile::ReadOnly))
    {
        auto qssStyle = topButtonQssFile.readAll();
        menuButton->setStyleSheet(qssStyle);
        homeButton->setStyleSheet(qssStyle);
        searchButton->setStyleSheet(qssStyle);
        closeButton->setStyleSheet(qssStyle);
    }

    topButtonQssFile.close();

    topBarLayout->addWidget(menuButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(homeButton);
    topBarLayout->addWidget(searchButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(closeButton);

    HomePage *homepage = new HomePage(this);
    //homepage->setAutoFillBackground(true);
    SearchPage *searchpage = new SearchPage(this);

    // QListWidget *pageList = new QListWidget();
    // pageList->insertItem(0, "homepage");
    // pageList->insertItem(1, "searchpage");
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

void MainWin::addNewActionTriggered()
{
    AddNewDialog *addNew = new AddNewDialog();
    addNew->exec();
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
    connect(addNewAction, SIGNAL(triggered(bool)), this, SLOT(addNewActionTriggered()));
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
