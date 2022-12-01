#include "list.h"
#include "pagecontrol.h"
#include <QDebug>

list::list(QWidget *parent)
    : QWidget{parent}
{
    const int pageSize = 10;  // 每页显示多少条数据
    // 以表格、列表的形式展示所有的电影库，主要目的是为了编辑电影信息，补充信息
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // 分页展示，使用表格控件
    tableModel = new QStandardItemModel();
    tableModel->setColumnCount(6);
    QStringList headerNames = {"电影名", "文件路径", "主演", "类型", "年代", "地区"};
    tableModel->setHorizontalHeaderLabels(headerNames);
    // 从数据库中分页查询，然后放入model中
    int total = 100;  //一共有多少条数据(电影),此数据应从数据库中查询得到

    tableView = new QTableView();
    tableView->setModel(tableModel);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    // 页面控制控件
    pageControl *pagecontrol = new pageControl();
    pagecontrol->initPage(total, 1, pageSize);
    connect(pagecontrol, SIGNAL(pageChanged(int)), this, SLOT(showPage(int)));
    // 开始布局
    mainLayout->addWidget(tableView);
    mainLayout->addWidget(pagecontrol, 0, Qt::AlignRight);
    this->setLayout(mainLayout);
}

void list::showPage(int p)
{
    qDebug() << QString("当前页码%1").arg(p);
    // 按照所给页数p从数据库中分页查询结果，重新置于model中显示
}
