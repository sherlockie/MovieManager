#include "addnew.h"
#include "flowlayout.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QDebug>

AddNewDialog::AddNewDialog()
{
    this->setObjectName("addNewPage");
    setWindowTitle(tr("添加新电影"));
    // this->resize(800, 450);
    this->setFixedSize(800, 450);
    // choose video file & add other infomation:
    // 1.name 2.actors 3.type(3) 4.short intro(outline)
    QVBoxLayout *mainLayout = new QVBoxLayout();

    QHBoxLayout *chooseFileLayout = new QHBoxLayout();
    chooseFileLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    QLabel *chooseFileLabel = new QLabel("选择电影文件(夹)");
    chooseFileBox = new QComboBox();
    chooseFileBox->setEditable(true);
    chooseFileBox->addItem(tr("请输入文件(夹)路径"));
    chooseFileBox->addItem("选择已有文件(夹)");
    chooseFileBox->setCurrentIndex(0);
    connect(chooseFileBox, SIGNAL(activated(int)), this, SLOT(chooseFile(int)));
    chooseFileLayout->addWidget(chooseFileLabel);
    chooseFileLayout->addWidget(chooseFileBox, 1);

    QHBoxLayout *inputNameLayout = new QHBoxLayout();
    inputNameLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    QLabel *inputNameLabel = new QLabel("电影名称");
    inputNameLine = new QLineEdit();
    inputNameLine->setPlaceholderText(tr("*必填"));
    inputNameLayout->addWidget(inputNameLabel);
    inputNameLayout->addWidget(inputNameLine, 1);

     QHBoxLayout *inputTypeLayout = new QHBoxLayout();
     inputTypeLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
     QLabel *inputTypeLabel = new QLabel("电影类型");
     QList<QString> typeLNameList = {"未知", "动作", "爱情", "科幻", "剧情", "记录", "惊悚", "艺术", "搞笑", "音乐"};
     FlowLayout *typelayout = new FlowLayout();
     allTypeList = new QButtonGroup();
     allTypeList->setExclusive(false);  // 类型可以多选
     foreach(QString typeName, typeLNameList)
     {
         QPushButton *typeButton = new QPushButton(typeName);
         typeButton->setCheckable(true);
         allTypeList->addButton(typeButton);
         typelayout->addWidget(typeButton);
         //connect(typeButton, SIGNAL(clicked(bool)), this, SLOT(commonButtonTagClicked()));
     }
     inputTypeLayout->addWidget(inputTypeLabel);
     inputTypeLayout->addLayout(typelayout, 1);

    QHBoxLayout *inputAgeLayout = new QHBoxLayout();
    inputAgeLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    QLabel *inputAgeLabel = new QLabel("电影年代");
    QList<QString> ageLNameList = {"未知", "2022", "2021", "2020", "2019", "2010年代", "2000年代", "90年代", "80年代", "70年代", "60年代", "更早"};
    FlowLayout *agelayout = new FlowLayout();
    allAgeList = new QButtonGroup();
    foreach(QString ageName, ageLNameList)
    {
        QPushButton *ageButton = new QPushButton(ageName);
        ageButton->setCheckable(true);
        allAgeList->addButton(ageButton);
        agelayout->addWidget(ageButton);
        //connect(ageButton, SIGNAL(clicked(bool)), this, SLOT(commonButtonTagClicked()));
    }
    inputAgeLayout->addWidget(inputAgeLabel);
    inputAgeLayout->addLayout(agelayout, 1);

    QHBoxLayout *inputRegionLayout = new QHBoxLayout();
    inputRegionLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    QLabel *inputRegionLabel = new QLabel("电影地区");
    QList<QString> regionLNameList = {"未知", "华语", "欧美", "韩国", "中国大陆", "中国台湾", "中国台湾", "日本", "美国", "意大利"};
    FlowLayout *regionlayout = new FlowLayout();
    allRegionList = new QButtonGroup();
    foreach(QString regionName, regionLNameList)
    {
        QPushButton *regionButton = new QPushButton(regionName);
        allRegionList->addButton(regionButton);
        regionButton->setCheckable(true);
        regionlayout->addWidget(regionButton);
        //connect(regionButton, SIGNAL(clicked(bool)), this, SLOT(commonButtonTagClicked()));
    }
    inputRegionLayout->addWidget(inputRegionLabel);
    inputRegionLayout->addLayout(regionlayout, 1);

    // confirm/ cancel button
    QPushButton *confirmButton = new QPushButton();
    confirmButton->setIcon(QIcon(":/default/Resources/confirm-w.png"));
    confirmButton->setFlat(true);
    connect(confirmButton, SIGNAL(clicked(bool)), this, SLOT(confirmButtonClicked()));

    mainLayout->addLayout(chooseFileLayout);
    mainLayout->addLayout(inputNameLayout);
    mainLayout->addLayout(inputTypeLayout);
    mainLayout->addLayout(inputAgeLayout);
    mainLayout->addLayout(inputRegionLayout);
    mainLayout->addWidget(confirmButton);
    this->setLayout(mainLayout);
}

AddNewDialog::~AddNewDialog() {}

void AddNewDialog::chooseFile(int i)
{
    if (i == 1)
    {
        QFileDialog *chooseFileDialog = new QFileDialog();
        chooseFileDialog->setFileMode(QFileDialog::ExistingFile);
        chooseFileDialog->setFileMode(QFileDialog::Directory);
        chooseFileDialog->exec();
    }
}

void AddNewDialog::confirmButtonClicked()
{
    QString filmPath = chooseFileBox->currentText();
    QString filmName = inputNameLine->text();
    QStringList filmType;
    QStringList filmAge;
    QStringList filmRegion;
    foreach (auto typeButton, allTypeList->buttons()) {
        auto button = qobject_cast<QPushButton *>(typeButton);
        if (button->isChecked()) filmType.append(button->text());
    }
    foreach (auto ageButton, allAgeList->buttons()) {
        auto button = qobject_cast<QPushButton *>(ageButton);
        if (button->isChecked()) filmAge.append(button->text());
    }
    foreach (auto regionButton, allRegionList->buttons()) {
        auto button = qobject_cast<QPushButton *>(regionButton);
        if (button->isChecked()) filmRegion.append(button->text());
    }
    qDebug() << filmPath << "/" << filmName << "/" << filmType << "/" << filmAge << "/" << filmRegion;
}
