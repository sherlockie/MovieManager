#include "library.h"
#include "list.h"
#include "grid.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>

library::library(QWidget *parent)
    : QWidget{parent}
{
    this->setObjectName("libraryPage");
    // 主竖直布局，上方是按钮，下方是所有文件
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // 按钮水平布局
    QHBoxLayout *buttonLyout = new QHBoxLayout();
    // 所有文件是stacked的组件
    allMovieView = new QStackedWidget();

    // 按钮们
    QToolButton *listButton = new QToolButton();
    listButton->setObjectName("listButton");
    connect(listButton, SIGNAL(clicked(bool)), this, SLOT(listButtonClicked()));
    QToolButton *gridButton = new QToolButton();
    gridButton->setObjectName("gridButton");
    connect(gridButton, SIGNAL(clicked(bool)), this, SLOT(gridButtonClicked()));
    QToolButton *refreshButton = new QToolButton();
    refreshButton->setObjectName("refreshButton");
    connect(refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshButtonClicked()));

    buttonLyout->addStretch();
    buttonLyout->addWidget(listButton);
    buttonLyout->addWidget(gridButton);
    buttonLyout->addWidget(refreshButton);
    buttonLyout->addStretch();

    // 展示区域
    list *lView = new list();
    grid *gView = new grid();
    allMovieView->addWidget(lView);
    allMovieView->addWidget(gView);
    // 设置布局
    mainLayout->addLayout(buttonLyout);
    mainLayout->addWidget(allMovieView);
    this->setLayout(mainLayout);

}

void library::listButtonClicked()
{
    allMovieView->setCurrentIndex(0);
}

void library::gridButtonClicked()
{
    allMovieView->setCurrentIndex(1);
}

void library::refreshButtonClicked()
{
    qDebug() << "尝试从数据库中重新读取所有电影文件信息，并刷新显示";
}
