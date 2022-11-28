#include "mainsettingpage.h"
#include "moviebank.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

mainSettingPage::mainSettingPage()
{
    this->setObjectName("mainSettingPage");
    this->resize(800, 450);
    /*设置页面主体布局，水平布局，左侧窗口是各个类别设置选项，右侧是每个类别设置的详情设置页*/
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    /*左侧由QFrame装载，右侧是一个QStackedWidget*/
    QFrame *leftWin = new QFrame();
    leftWin->setMaximumWidth(100);
    rightWin = new QStackedWidget();

    /*左侧的布局竖直，紧密排列*/
    QVBoxLayout *leftWinLayout = new QVBoxLayout();
    leftWinLayout->setSpacing(0);
    QToolButton *movieBankButton = new QToolButton();
    //movieBankButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    movieBankButton->setText("电影库");
    connect(movieBankButton, SIGNAL(clicked(bool)), this, SLOT(movieBankButtonClicked()));
    leftWinLayout->addWidget(movieBankButton, Qt::AlignLeft | Qt::AlignTop);
    leftWinLayout->addStretch(0);

    leftWin->setLayout(leftWinLayout);
    /*右侧详情页*/
    auto emptyPage = initEmptySettingPage();
    movieBank *movieBankPage = new movieBank();

    rightWin->addWidget(emptyPage);
    rightWin->addWidget(movieBankPage);
    //rightWin->setCurrentWidget(0);
    // 开始布局
    mainLayout->addWidget(leftWin);
    mainLayout->addWidget(rightWin);
    this->setLayout(mainLayout);
}

void mainSettingPage::movieBankButtonClicked()
{
    this->rightWin->setCurrentIndex(1);
}

QWidget *mainSettingPage::initEmptySettingPage()
{
    QWidget * emptyPage = new QWidget(this);
    emptyPage->setObjectName("emptyPage");
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->setMargin(0);
    QLabel *tmp = new QLabel("选择一项设置");
    mainLayout->addWidget(tmp, 1, 1);
    emptyPage->setLayout(mainLayout);

    return emptyPage;
}
