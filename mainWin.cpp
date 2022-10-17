#include "mainWin.h"
#include "homepage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>

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
    QHBoxLayout *topBarLayout = new QHBoxLayout();

    QPushButton *menuButton = new QPushButton(this);
    menuButton->setIcon(QIcon(":/icons/Resources/menu.png"));
    menuButton->setFlat(true);
//    connect(menuButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));

    QPushButton *homeButton = new QPushButton(this);
    homeButton->setIcon(QIcon(":/icons/Resources/home.png"));
    homeButton->setFlat(true);

    QPushButton *searchButton = new QPushButton(this);
    searchButton->setIcon(QIcon(":/icons/Resources/search.png"));
    searchButton->setFlat(true);

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(QIcon(":/icons/Resources/close.png"));
    closeButton->setFlat(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));

    topBarLayout->addWidget(menuButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(homeButton);
    topBarLayout->addWidget(searchButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(closeButton);

    mainLayout->addLayout(topBarLayout);
    // homepage
    HomePage *homepage = new HomePage();
    mainLayout->addWidget(homepage);

    this->setLayout(mainLayout);
}

void MainWin::closeButtonClicked()
{
    this->close();
}

MainWin::~MainWin()
{
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
