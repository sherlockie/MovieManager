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
    // 增加和删除按钮
    QToolButton *addButton = new QToolButton();
    //movieBankButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QToolButton *decButton = new QToolButton();
    // 路径表
    // 同步按钮
    QToolButton *syncButton = new QToolButton();
    syncButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    syncButton->setText("开始同步");
    connect(syncButton, SIGNAL(clicked(bool)), this, SLOT(syncButtonClicked()));

    // 开始布局
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(decButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(syncButton, 0, Qt::AlignCenter);
    this->setLayout(mainLayout);
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
