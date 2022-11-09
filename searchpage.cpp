#include "searchpage.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>

SearchPage::SearchPage(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *mainLayout = new QHBoxLayout();

    // search conditions
    QVBoxLayout *searchLayout = new QVBoxLayout(this);
    QFrame *searchFrame = new QFrame(this);
    searchFrame->setMaximumWidth(450);
    typeBox = new QGroupBox(tr("类型"));
    typeBox->setStyleSheet("color:white;");
    QList<QString> typeLNameist = {"所有类型", "动作", "爱情", "科幻", "剧情", "记录", "惊悚", "艺术", "搞笑", "音乐"};
    initButtons(typeLNameist, "type");

    ageBox = new QGroupBox(tr("年代"));
    ageBox->setStyleSheet("color:white;");
    QList<QString> ageLNameist = {"所有年代", "2022", "2021", "2020", "2019", "2010年代", "2000年代", "90年代", "80年代", "70年代", "60年代", "更早"};
    initButtons(ageLNameist, "age");

    regionBox = new QGroupBox(tr("地区"));
    regionBox->setStyleSheet("color:white;");
    QList<QString> regionLNameist = {"所有地区", "华语", "欧美", "韩国", "中国大陆", "中国台湾", "中国台湾", "日本", "美国", "意大利"};
    initButtons(regionLNameist, "region");

    // confirm button
    QPushButton *confirmButton = new QPushButton();
    confirmButton->setIcon(QIcon(":/icons/Resources/confirm.png"));
    confirmButton->setFlat(true);
    connect(confirmButton, SIGNAL(clicked(bool)), this, SLOT(confirmButtonClicked()));

    searchLayout->addWidget(typeBox);
    searchLayout->addWidget(ageBox);
    searchLayout->addWidget(regionBox);
    searchLayout->addWidget(confirmButton);
    searchFrame->setLayout(searchLayout);

    // search result
    QLabel *searchResult = new QLabel("search result", this);
    searchResult->setStyleSheet("color:white;");
    resultEara = new QScrollArea();
    resultEara->setWidget(searchResult);

    mainLayout->addWidget(searchFrame);
    mainLayout->addWidget(resultEara);
    setLayout(mainLayout);
}

void SearchPage::initButtons(QList<QString> buttonNameList, QString category)
{
    int cols = 3;  // fixed 3 columns
    QGridLayout *tmpLayout = new QGridLayout();
    for(int i=0; i < buttonNameList.size(); ++i)
    {
        QString buttonName = buttonNameList[i];
        QRadioButton *tmp = new QRadioButton(buttonName);
        tmp->setObjectName(buttonName);
        // if(i==0) tmp->setChecked(true);  // first 'all' is checked defaulty
        if(i==0)
        {
            if (category == "type")
            {
                connect(tmp, SIGNAL(clicked()), this, SLOT(allTypeClicked()));
            } else if (category == "age")
            {
                connect(tmp, SIGNAL(clicked()), this, SLOT(allAgeClicked()));
            } else
            {
                connect(tmp, SIGNAL(clicked()), this, SLOT(allRegionClicked()));
            }
        }
        else
        {
            if (category == "type")
            {
                connect(tmp, SIGNAL(clicked()), this, SLOT(commonTypeClicked()));
            } else if (category == "age")
            {
                connect(tmp, SIGNAL(clicked()), this, SLOT(commonAgeClicked()));
            } else
            {
                connect(tmp, SIGNAL(clicked()), this, SLOT(commonRegionClicked()));
            }
        }
        tmp->setAutoExclusive(false);
        tmp->setStyleSheet("color:white;");
        if (category == "type")
        {
            typeButtonList.append(tmp);
        } else if (category == "age")
        {
            ageButtonList.append(tmp);
        } else
        {
            regionButtonList.append(tmp);
        }
        tmpLayout->addWidget(tmp, i / cols, i % cols);
    }
    if (category == "type")
    {
        typeBox->setLayout(tmpLayout);
    } else if (category == "age")
    {
        ageBox->setLayout(tmpLayout);
    } else
    {
        regionBox->setLayout(tmpLayout);
    }
}

void SearchPage::initSearchResult()
{
    // search summary
    QLabel *searchSummary = new QLabel();
    searchSummary->setText("Found 4396 results shown below:");
    searchSummary->setStyleSheet("color:white;");
    QFrame *allResultCard = new QFrame();
    QVBoxLayout *allResultCardyout = new QVBoxLayout();
    allResultCardyout->addWidget(searchSummary);
    // results blocks/cards
    for (int i=0; i < 10; ++i)
    {
        QFrame *resultCard = new QFrame();
        // poster & details layout
        QHBoxLayout *cardLayout = new QHBoxLayout();
        // details: name/actors/main plots layout
        QVBoxLayout *detailsLayout = new QVBoxLayout();
        // components
        QLabel *poster = new QLabel("海报");
        const QPixmap &&posterimg = QPixmap(":/default/Resources/1.jpg");
        poster->setPixmap(posterimg);
        QLabel *name = new QLabel("海边的曼彻斯特(2016)");
        name->setStyleSheet("color:white;");
        QLabel *actors = new QLabel("主演：肯尼斯·罗纳根/卡西·阿弗莱克");
        actors->setStyleSheet("color:white;");
        QLabel *outline = new QLabel("李（卡西·阿弗莱克饰）是一名颓废压抑的修理工，在得知哥哥乔伊（凯尔·钱德勒饰）"
                                     "去世的消息后，李回到了故乡-海边的曼彻斯特处理乔伊的后事。");
        outline->setWordWrap(true);
        outline->setStyleSheet("color:white;");
        detailsLayout->addWidget(name);
        detailsLayout->addWidget(actors);
        detailsLayout->addWidget(outline);
        cardLayout->addWidget(poster);
        cardLayout->addLayout(detailsLayout);

        resultCard->setLayout(cardLayout);
        allResultCardyout->addWidget(resultCard);
    }
    allResultCard->setLayout(allResultCardyout);
    resultEara->setWidget(allResultCard);
}

void SearchPage::allTypeClicked()
{
    if (typeButtonList[0]->isChecked())
    {
        foreach (auto b, typeButtonList) {
            b->setChecked(true);
        }
    }
    else
    {
        foreach (auto b, typeButtonList) {
            b->setChecked(false);
        }
    }
}

void SearchPage::allAgeClicked()
{
    if (ageButtonList[0]->isChecked())
    {
        foreach (auto b, ageButtonList) {
            b->setChecked(true);
        }
    }
    else
    {
        foreach (auto b, ageButtonList) {
            b->setChecked(false);
        }
    }
}

void SearchPage::allRegionClicked()
{
    if (regionButtonList[0]->isChecked())
    {
        foreach (auto b, regionButtonList) {
            b->setChecked(true);
        }
    }
    else
    {
        foreach (auto b, regionButtonList) {
            b->setChecked(false);
        }
    }
}

void SearchPage::commonTypeClicked()
{
    auto button = qobject_cast<QRadioButton *>(sender());
    // button->objectName();
    if (!button->isChecked())
    {
        typeButtonList[0]->setChecked(false);
    }
}

void SearchPage::commonAgeClicked()
{
    auto button = qobject_cast<QRadioButton *>(sender());
    // button->objectName();
    if (!button->isChecked())
    {
        ageButtonList[0]->setChecked(false);
    }
}

void SearchPage::commonRegionClicked()
{
    auto button = qobject_cast<QRadioButton *>(sender());
    // button->objectName();
    if (!button->isChecked())
    {
        regionButtonList[0]->setChecked(false);
    }
}

void SearchPage::confirmButtonClicked()
{
    QList<QString> choosenCondition;
    foreach (auto b, typeButtonList) {
       if (b->isChecked()) choosenCondition.append(b->objectName());
    }
    foreach (auto b, ageButtonList) {
       if (b->isChecked()) choosenCondition.append(b->objectName());
    }
    foreach (auto b, regionButtonList) {
       if (b->isChecked()) choosenCondition.append(b->objectName());
    }
    foreach (auto s, choosenCondition) {
       qDebug() << s;
    }
    initSearchResult();
}
