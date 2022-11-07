#include "searchpage.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QGridLayout>

SearchPage::SearchPage(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *mainLayout = new QHBoxLayout();

    // search conditions
    QVBoxLayout *searchLayout = new QVBoxLayout(this);
    QFrame *searchFrame = new QFrame(this);
    searchFrame->setMaximumWidth(450);
    typeBox = new QGroupBox(tr("类型"));
    // typeBox->setCheckable(true);
    // typeBox->setChecked(false);
    typeBox->setStyleSheet("color:white;");
    // connect(typeBox, SIGNAL(toggled()), this, SLOT(typeBoxChecked()));
    QList<QString> typeLNameist = {"所有类型", "动作", "爱情", "科幻", "剧情", "记录", "惊悚", "艺术", "搞笑", "音乐"};
    initButtons(typeLNameist, "type");

    ageBox = new QGroupBox(tr("年代"));
    // ageBox->setCheckable(true);
    // ageBox->setChecked(false);
    ageBox->setStyleSheet("color:white;");
    // connect(ageBox, SIGNAL(toggled()), this, SLOT(ageBoxChecked()));
    QList<QString> ageLNameist = {"所有年代", "2022", "2021", "2020", "2019", "2010年代", "2000年代", "90年代", "80年代", "70年代", "60年代", "更早"};
    initButtons(ageLNameist, "age");

    regionBox = new QGroupBox(tr("地区"));
    // regionBox->setCheckable(true);
    // regionBox->setChecked(false);
    regionBox->setStyleSheet("color:white;");
    // connect(regionBox, SIGNAL(toggled()), this, SLOT(regionBoxChecked()));
    QList<QString> regionLNameist = {"所有地区", "华语", "欧美", "韩国", "中国大陆", "中国台湾", "中国台湾", "日本", "美国", "意大利"};
    initButtons(regionLNameist, "region");

    searchLayout->addWidget(typeBox);
    searchLayout->addWidget(ageBox);
    searchLayout->addWidget(regionBox);
    searchFrame->setLayout(searchLayout);

    // search result
    QLabel *searchResult = new QLabel("search result", this);
    searchResult->setStyleSheet("color:white;");

    mainLayout->addWidget(searchFrame);
    mainLayout->addWidget(searchResult);
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
