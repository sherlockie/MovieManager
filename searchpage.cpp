#include "searchpage.h"
#include <QLabel>
#include <QHBoxLayout>

SearchPage::SearchPage(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *tl = new QHBoxLayout();
    QLabel *tmp = new QLabel("This is the search page");
    tmp->setParent(this);
    tmp->setStyleSheet("color:white;");
    tl->addWidget(tmp);

    setLayout(tl);
}
