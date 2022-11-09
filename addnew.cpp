#include "addnew.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QComboBox>

AddNewDialog::AddNewDialog()
{
    setWindowTitle(tr("添加新电影"));
    // choose video file & add other infomation:
    // 1.name 2.year 3.actors 4.type(3) 5.short intro(outline)
    QVBoxLayout *mainLayout = new QVBoxLayout();

    QHBoxLayout *chooseFileLayout = new QHBoxLayout();
    QLabel *chooseFileLabel = new QLabel("选择电影文件(夹)");
    QComboBox *chooseFileBox = new QComboBox();
    chooseFileBox->setEditable(true);
    chooseFileBox->addItem(tr("请输入文件(夹)路径"));
    chooseFileBox->addItem("选择已有文件(夹)");
    chooseFileBox->setCurrentIndex(0);
    //chooseFileBox->lineEdit()->setPlaceholderText(tr("请输入文件(夹)路径"));
    connect(chooseFileBox, SIGNAL(activated(int)), this, SLOT(chooseFile(int)));
    chooseFileLayout->addWidget(chooseFileLabel);
    chooseFileLayout->addWidget(chooseFileBox);

    mainLayout->addLayout(chooseFileLayout);
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
