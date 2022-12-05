#include "list.h"
#include "pagecontrol.h"
#include <QDebug>

// sqlModel
sqlModel::sqlModel(QObject *parent) : QSqlQueryModel(parent)
{
    allCenter = false;
    alignCenterColumn.clear();
    alignRightColumn.clear();
}

QVariant sqlModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (allCenter)
    {
        if (role == Qt::TextAlignmentRole)
        {
            value = Qt::AlignCenter;
        }
    } else {
        //逐个从列索引中查找是否当前列在其中
        int column = index.column();
        bool existCenter = alignCenterColumn.contains(column);
        bool existRight = alignRightColumn.contains(column);
        if (role == Qt::TextAlignmentRole) {
            if (existCenter) {
                value = Qt::AlignCenter;
            }
            if (existRight) {
                value = (QVariant)(Qt::AlignVCenter | Qt::AlignRight);
            }
        }
    }
    return value;
}

void sqlModel::setAllCenter(bool allCenter)
{
    this->allCenter = allCenter;
}

void sqlModel::setAlignCenterColumn(const QList<int> &alignCenterColumn)
{
    this->alignCenterColumn = alignCenterColumn;
}

void sqlModel::setAlignRightColumn(const QList<int> &alignRightColumn)
{
    this->alignRightColumn = alignRightColumn;
}


// list
list::list(QWidget *parent)
    : QWidget{parent}
{
    connName = "qt_sql_default_connection";
    columnNames << "电影名称" << "海报路径" << "文件路径" << "主演";
    columnWidths << 50 << 100 << 100 << 50;
    pageSize = 10;
    totalPage = 0;
    currentPage = 1;
    // 以表格、列表的形式展示所有的电影库，主要目的是为了编辑电影信息，补充信息
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // 分页展示
    tableModel = new QSqlQueryModel();
    // 从数据库中分页查询，然后放入model中

    //tableView = new QTableView();
    //tableView->setModel(tableModel);
    //tableView->verticalHeader()->setVisible(false);
    //tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    // 页面控制控件
    pageControl *pagecontrol = new pageControl();
    pagecontrol->initPage(totalPage, currentPage, pageSize);
    connect(pagecontrol, SIGNAL(pageChanged(int)), this, SLOT(showPage(int)));
    // 开始布局
    mainLayout->addWidget(tableView);
    mainLayout->addWidget(pagecontrol, 0, Qt::AlignRight);
    this->setLayout(mainLayout);
}

void list::setConnName(const QString &name)
{
    this->connName = name;
}

void list::showPage(int p)
{
    qDebug() << QString("当前页码%1").arg(p);
    // 按照所给页数p从数据库中分页查询结果，重新置于model中显示
    QString sql = "";
    tableModel->setQuery(sql, QSqlDatabase::database(connName));
    tableView->setModel(tableModel);
    int columnCount = columnNames.count();
    // 设置表头
    for (int i=0; i < columnCount; ++i)
    {
        tableModel->setHeaderData(i, Qt::Horizontal, columnNames.at(i));
        tableView->setColumnWidth(i, columnWidths.at(i));
    }
}
