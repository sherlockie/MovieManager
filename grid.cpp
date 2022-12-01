#include "grid.h"
#include "pagecontrol.h"

#include <QLabel>
#include <QDebug>

grid::grid(QWidget *parent)
    : QWidget{parent}
{
    int total = 100;
    int pageSize = 8;
    mainLayout = new QVBoxLayout();
    // 第一页所有电影网格展示
    initMovies();
    // 页面控制控件
    pageControl *pagecontrol = new pageControl();
    pagecontrol->initPage(total, 1, pageSize);
    connect(pagecontrol, SIGNAL(pageChanged(int)), this, SLOT(showPage(int)));
    // 开始布局
    mainLayout->addLayout(allItemsLayout);
    mainLayout->addWidget(pagecontrol, 0, Qt::AlignCenter);
    this->setLayout(mainLayout);
}

void grid::initMovies()
{
    // 初始化所有电影，但不设置数据
    int cols = 4;  // 每行四个
    allItemsLayout = new QGridLayout();
    allItemsLayout->setSpacing(20);
    for(int i = 0; i < 8; ++i)
    {
        int row = i / cols;
        int col = i % cols;
        movieLayout = new QVBoxLayout();
        movieLayout->setAlignment(Qt::AlignCenter);
        QPushButton *movieButton = new QPushButton();
        movieButton->setMinimumHeight(300);
        // 海报默认
        QLabel *poster = new QLabel();
        poster->setPixmap(QPixmap(QString(":/default/Resources/%1.jpg").arg(i%7+1)));
        QLabel *name = new QLabel("默认电影名");
        movieLayout->addWidget(poster);
        movieLayout->addWidget(name);

        movieButton->setLayout(movieLayout);
        movieList << movieButton;

        allItemsLayout->addWidget(movieButton, row, col);
    }
}

void grid::showPage(int p)
{
    qDebug() << QString("当前页码%1").arg(p);
    // 按照所给页数p从数据库中分页查询结果，重新置于model中显示
}
