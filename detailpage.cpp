#include "detailpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

detailPage::detailPage(QWidget *parent)
    : QWidget{parent}
{
    this->setObjectName("detailPage");
    this->setWindowFlag(Qt::FramelessWindowHint);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);
    QVBoxLayout *detailLayout = new QVBoxLayout();
    // all details goes to this scroll area, screen center
    detailArea = new QScrollArea(this);
    detailArea->setFixedWidth(1000);
    detailArea->setAlignment(Qt::AlignCenter);
    detailArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    detailArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QFrame *detailFrame = new QFrame(detailArea);
    detailFrame->setFixedWidth(1000);
    /*
     * add all contents
    */
    QLabel *name = new QLabel("海边的曼彻斯特(2016)", detailFrame);
    name->setObjectName("name");
    name->setAlignment(Qt::AlignLeft);
    // poster,info,rating
    QHBoxLayout *tmpLayout = new QHBoxLayout();
    QLabel *poster = new QLabel();
    poster->setPixmap(QPixmap(":/default/Resources/1.jpg"));
    QVBoxLayout *infoLayout = new QVBoxLayout();
    QLabel *info1 = new QLabel("导演: 肯尼思·洛纳根");
    QLabel *info2 = new QLabel("编剧: 肯尼思·洛纳根");
    QLabel *info3 = new QLabel("主演: 卡西·阿弗莱克 / 卢卡斯·赫奇斯 / 米歇尔·威廉姆斯 / C·J·威尔逊 / 凯尔·钱德勒");
    QLabel *info4 = new QLabel("类型: 剧情 / 家庭");
    QLabel *info5 = new QLabel("类型: 剧情 / 家庭");
    QLabel *info6 = new QLabel("上映日期: 2017-08-25(中国大陆) / 2016-01-23(圣丹斯电影节) / 2016-11-18(美国)");
    infoLayout->addWidget(info1);
    infoLayout->addWidget(info2);
    infoLayout->addWidget(info3);
    infoLayout->addWidget(info4);
    infoLayout->addWidget(info5);
    infoLayout->addWidget(info6);

    tmpLayout->addWidget(poster);
    tmpLayout->addLayout(infoLayout);
    // outline title
    QLabel *outlineTitle = new QLabel("海边的曼彻斯特的剧情简介 · · · · · ·", detailFrame);
    outlineTitle->setObjectName("outlineTitle");
    // outline
    QString outlineString = {"李（卡西·阿弗莱克 Casey Affleck 饰）是一名颓废压抑的修理工，在得知哥哥乔伊（凯尔·钱德勒 Kyle Chandler 饰）"
                             "去世的消息后，李回到了故乡——海边的曼彻斯特处理乔伊的后事。根据乔伊的遗嘱，李将会成为乔伊的儿子帕特里克（卢卡斯·赫奇斯 "
                             "Lucas Hedg es 饰）的监护人，李打算将帕特里克带回波士顿，但很显然帕特里克并不愿意离开家乡和朋友们，但李亦不愿在这片伤心地久留。\n"
                             "原来，曼彻斯特埋藏着李的一段绝望的回忆，他的过失使得三个孩子葬身火海，妻子兰迪（米歇尔·威廉姆斯 Michelle Williams 饰）亦因"
                             "此而离开了他。此次重回故乡，李再度见到了已经再婚并且即将做妈妈的兰迪，与此同时，帕特里克那失踪已久的母亲艾丽斯（格瑞辰·摩尔 Gr"
                             "etchen Mol 饰）亦联系上了帕特里克，希望他能够成为她的新家庭中的一员"};
    QLabel *outline = new QLabel();
    outline->setWordWrap(true);
    outline->setText(outlineString);
    // add to detailLayout
    detailLayout->addWidget(name);
    detailLayout->addLayout(tmpLayout);
    detailLayout->addWidget(outlineTitle);
    detailLayout->addWidget(outline);
    // set layout
    detailFrame->setLayout(detailLayout);
    detailArea->setWidget(detailFrame);
    mainLayout->addWidget(detailArea);
    this->setLayout(mainLayout);
}
