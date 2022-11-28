#include "moviebank.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QDebug>

movieBank::movieBank(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // 增加和删除按钮
    QToolButton *addButton = new QToolButton();
    addButton->setObjectName("addButton");
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addButtonClicked()));
    QToolButton *decButton = new QToolButton();
    decButton->setObjectName("decButton");
    connect(decButton, SIGNAL(clicked(bool)), this, SLOT(decButtonClicked()));
    // 路径表
    tableModel = new QStandardItemModel();
    tableModel->setColumnCount(2);
    QStringList headerNames = {"名称", "路径"};
    tableModel->setHorizontalHeaderLabels(headerNames);
    for(int i=0; i<2; ++i)
    {
        QStandardItem *name = new QStandardItem("test1");
        QStandardItem *path = new QStandardItem("/home/local/bank1");
        name->setCheckable(true);
        tableModel->setItem(i, 0, name);
        tableModel->setItem(i, 1, path);
    }

    tableView = new QTableView();
    tableView->setModel(tableModel);
    tableView->verticalHeader()->setVisible(false);
    tableView->setColumnWidth(0, 120);
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    // 同步按钮
    QToolButton *syncButton = new QToolButton();
    //syncButton->setMinimumSize(105, 50);
    syncButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    syncButton->setText("开始同步");
    syncButton->setObjectName("syncButton");
    connect(syncButton, SIGNAL(clicked(bool)), this, SLOT(syncButtonClicked()));

    // 开始布局
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(decButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableView);
    mainLayout->addWidget(syncButton, 0, Qt::AlignCenter);
    this->setLayout(mainLayout);
}

void movieBank::addButtonClicked()
{
    int currentRow = tableModel->rowCount();
    QStandardItem *name = new QStandardItem("请输入名称");
    QStandardItem *path = new QStandardItem("请输入路径");
    QList<QStandardItem*> itemList;
    itemList << name << path;
    name->setCheckable(true);
    tableModel->insertRow(currentRow, itemList);
}

void movieBank::decButtonClicked()
{
    QModelIndex selecedRow = tableView->currentIndex();
    tableModel->removeRow(selecedRow.row());
}

void movieBank::syncButtonClicked()
{
    // 获取选择的路径
    QStringList paths = {"D:\\迅雷下载"};
    //搜索结果
    QFileInfoList fileList;
    // 筛选条件：视频文件
    for (int i=0; i < paths.size(); ++i)
    {
        QString path = paths.at(i);
        this->findAllFiles(path, fileList);
    }
    qDebug() << "找到" << fileList.size() << "个视频。";
}

void movieBank::findAllFiles(QString path, QFileInfoList &fileList)
{
    QDir qPath(path);
    const QStringList nameFilters = {"*.mp4", "*.avi", "*.mkv"};
    foreach(QFileInfo info,qPath.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs)){
        //qDebug()<<"dir:"<<info.filePath();
        findAllFiles(info.filePath(), fileList);
    }

    foreach(QFileInfo info, qPath.entryInfoList(nameFilters, QDir::Files)){
        fileList.append(info);
        //qDebug()<<"fileInfo"<<info;
    }

}
