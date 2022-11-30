#include "list.h"
#include "pagecontrol.h"

list::list(QWidget *parent)
    : QWidget{parent}
{
    // 以表格、列表的形式展示所有的电影库，主要目的是为了编辑电影信息，补充信息
    // 分页展示
    QVBoxLayout *mainLayout = new QVBoxLayout();
    tmp = new QLabel("Hello");
    tmp->setStyleSheet("color:white");
    pageControl *pagecontrol = new pageControl();
    pagecontrol->initPage(10, 1, 5);
    connect(pagecontrol, SIGNAL(pageChanged(int)), this, SLOT(showPage(int)));

    mainLayout->addWidget(tmp);
    mainLayout->addWidget(pagecontrol);
    this->setLayout(mainLayout);
}

void list::showPage(int p)
{
    tmp->setText(QString("当前页码%1").arg(p));
}
