#include "mainsettingpage.h"
#include "moviebank.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

mainSettingPage::mainSettingPage()
{
    /*设置页面主体布局，水平布局，左侧窗口是各个类别设置选项，右侧是每个类别设置的详情设置页*/
    QHBoxLayout *mainLayout = new QHBoxLayout();
    /*左右侧都由QFrame装载*/
    QFrame *leftWin = new QFrame();
    rightWin = new QStackedWidget();

    /*左侧的布局竖直，紧密排列*/
    QVBoxLayout *leftWinLayout = new QVBoxLayout();
    QToolButton *movieBankButton = new QToolButton();
    //movieBankButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    movieBankButton->setText("电影库");
    connect(movieBankButton, SIGNAL(clicked(bool)), this, SLOT(movieBankButtonClicked()));
    leftWinLayout->addWidget(movieBankButton);

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
    QWidget * emptyPage = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();
    QLabel *tmp = new QLabel("Working in progress.");
    mainLayout->addWidget(tmp);
    emptyPage->setLayout(mainLayout);

    return emptyPage;
}
