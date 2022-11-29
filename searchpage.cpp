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
    this->setObjectName("searchPage");
    QHBoxLayout *mainLayout = new QHBoxLayout();

    // search conditions
    QVBoxLayout *searchLayout = new QVBoxLayout(this);
    QFrame *searchFrame = new QFrame(this);
    searchFrame->setMaximumWidth(450);
    typeBox = new QGroupBox(tr("类型"));
    QList<QString> typeLNameList = {"所有类型", "动作", "爱情", "科幻", "剧情", "记录", "惊悚", "艺术", "搞笑", "音乐"};
    initButtons(typeLNameList, "type");

    ageBox = new QGroupBox(tr("年代"));
    QList<QString> ageLNameList = {"所有年代", "2022", "2021", "2020", "2019", "2010年代", "2000年代", "90年代", "80年代", "70年代", "60年代", "更早"};
    initButtons(ageLNameList, "age");

    regionBox = new QGroupBox(tr("地区"));
    QList<QString> regionLNameList = {"所有地区", "华语", "欧美", "韩国", "中国大陆", "中国台湾", "中国台湾", "日本", "美国", "意大利"};
    initButtons(regionLNameList, "region");

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
    QLabel *defaultSearchResult = new QLabel();
    defaultSearchResult->setFixedSize(512, 512);
    defaultSearchResult->setStyleSheet("background:transparent;");
    defaultSearchResult->setPixmap(QPixmap(":/default/Resources/emptySearch.png"));
    resultArea = new QScrollArea(this);
    resultArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    resultArea->setAlignment(Qt::AlignCenter);
    resultArea->setObjectName("resultArea");
    resultArea->setWidget(defaultSearchResult);

    mainLayout->addWidget(searchFrame);
    mainLayout->addWidget(resultArea);
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
    QFrame *allResultCard = new QFrame();
    allResultCard->setObjectName("allResultCard");
    allResultCard->setMinimumWidth(1080);
    QLabel *searchSummary = new QLabel(allResultCard);
    searchSummary->setObjectName("searchSummary");
    searchSummary->setText("共找到 4396 条结果：");
    searchSummary->setMaximumHeight(50);
    QVBoxLayout *allResultCardyout = new QVBoxLayout();
    allResultCardyout->addWidget(searchSummary);
    // results blocks/cards
    for (int i=0; i < 10; ++i)
    {
        QPushButton *resultCard = new QPushButton(allResultCard);
        resultCard->setMinimumHeight(330);
        // poster & details layout
        QHBoxLayout *cardLayout = new QHBoxLayout();
        cardLayout->setContentsMargins(30, 15, 15, 15);
        // details: name/actors/main plots layout
        QVBoxLayout *detailsLayout = new QVBoxLayout();
        detailsLayout->setAlignment(Qt::AlignLeft);
        // components
        QLabel *poster = new QLabel("海报", resultCard);
        const QPixmap &&posterimg = QPixmap(":/default/Resources/1.jpg");
        poster->setPixmap(posterimg);
        QLabel *name = new QLabel("海边的曼彻斯特(2016)", resultCard);
        name->setProperty("isTitle", true);
        QLabel *actors = new QLabel("主演：肯尼斯·罗纳根/卡西·阿弗莱克", resultCard);
        actors->setProperty("isTitle", false);
        QLabel *outline = new QLabel("李（卡西·阿弗莱克饰）是一名颓废压抑的修理工，在得知哥哥乔伊（凯尔·钱德勒饰）"
                                     "去世的消息后，李回到了故乡-海边的曼彻斯特处理乔伊的后事。", resultCard);
        outline->setFixedWidth(500);
        outline->setProperty("isTitle", false);
        // outline->adjustSize();
        outline->setWordWrap(true);
        detailsLayout->addWidget(name, 1);
        detailsLayout->addWidget(actors, 1);
        detailsLayout->addWidget(outline, 3);
        cardLayout->addWidget(poster);
        cardLayout->addLayout(detailsLayout, 1);

        resultCard->setLayout(cardLayout);
        allResultCardyout->addWidget(resultCard);
    }
    allResultCard->setLayout(allResultCardyout);
    resultArea->setWidget(allResultCard);
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
