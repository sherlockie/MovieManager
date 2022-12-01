#include "pagecontrol.h"
#include "qevent.h"
#include "qstyle.h"
#include <QDebug>
#include <QEvent>

pageControl::pageControl(QWidget *parent)
    : QWidget{parent}
{
    //pageNum = 1;
    //pageSize = 10;
    // 布局初始化设置
    mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(8);
    mainLayout->setMargin(0);
    // 各个按钮/标签初始化
    totalNumLabel = new QLabel(this);
    mainLayout->addWidget(totalNumLabel);
    initPageButton();
    initJumpControl();
    // 向布局中添加组件
    mainLayout->addStretch(1);
    mainLayout->addWidget(totalNumLabel);

    this->setLayout(mainLayout);
}

/**
 * @brief 正式初始化控件，指定一共有多少数据和每页显示多少条后，
 *        调用setCurrentPage函数来初始化
 * @param _total 总数据条数
 * @param _pageNum 当前页码
 * @param _pageSize 单页大小
 */
void pageControl::initPage(int _total, int _pageNum, int _pageSize)
{
    pageCount = (_total + _pageSize - 1) / _pageSize;
    pageSize = _pageSize;
    totalNumLabel->setText(QString("共%1条").arg(_total));
    // 默认第一页和最后一页是总要显示的，除非总共只有一页，那么最后一页不显示
    if(pageCount > 1)
    {
        lastPageButton->setVisible(true);
        QString maxPageNum = QString::number(pageCount);
        lastPageButton->setText(maxPageNum);
        lastPageButton->setFixedWidth(35 + (maxPageNum.length() < 3 ? 0 : maxPageNum.length() - 3) * 12);
    } else
    {
        lastPageButton->setVisible(false);
    }
    // 如果输入了过大的页码，根本不存在，则默认是指最后一页
    if(_pageNum > pageCount)
    {
        pageNum = pageCount;
    }
    this->setCurrentPage(_pageNum);
}

// 给pageNum这个类变量赋值，表示目前应该显示哪一页，此函数主要判断所给的_pageNum值
// 是否合法，有无越界，并设置左右加减页的按钮是否可点击，然后调用updatePageButton()函数
void pageControl::setCurrentPage(int _pageNum)
{
    pageNum = _pageNum;
    // 所给页码异常，大于最大值
    if(_pageNum >= pageCount)
    {
        pageNum = pageCount;
        lastPageButton->setProperty("currentPage", true);
        lastPageButton->style()->unpolish(lastPageButton);
        lastPageButton->style()->polish(lastPageButton);
        lastPageButton->update();
        nextPageButton->setCheckable(false);
    } else
    {
        lastPageButton->setProperty("currentPage", false);
        lastPageButton->style()->unpolish(lastPageButton);
        lastPageButton->style()->polish(lastPageButton);
        lastPageButton->update();
        nextPageButton->setCheckable(true);
    }
    if(_pageNum <= 1)
    {
        pageNum = 1;
        firstPageButton->setProperty("currentPage","true");
        firstPageButton->style()->unpolish(firstPageButton);
        firstPageButton->style()->polish(firstPageButton);
        firstPageButton->update();
        prePageButton->setCheckable(false);
        //firstPageButton->setCursor(Qt::ForbiddenCursor);
    }
    else
    {
        firstPageButton->setProperty("currentPage","false");
        firstPageButton->style()->unpolish(firstPageButton);
        firstPageButton->style()->polish(firstPageButton);
        firstPageButton->update();
        prePageButton->setCheckable(true);
        //firstPageButton->setCursor(Qt::PointingHandCursor);
    }

    updatePageButton();
}

void pageControl::updatePageButton()
{
    // 中间五个数字按钮如何显示
    showLeftMoreButton = false;
    showRightMoreButton = false;
    int beginPageNum = 2;
    // 只有大于7页的时候，中间五个按钮才可以全部派上用场，否则不需要全部五个按钮
    if(pageCount > 7)
    {
        if(pageNum - 1 < pageCount - pageNum)
        {
            //int rightAddIndex = 1;
            if(pageNum > 4)
            {
                showLeftMoreButton = true;
                beginPageNum = pageNum - 1;
            }
            else
            {
                //rightAddIndex += (4 - pageNum);
                beginPageNum = 2;
            }
            showRightMoreButton = true;
        }
        else
        {
            int leftSubIndex = 1;
            if(pageCount - pageNum > 3)
            {
                showRightMoreButton = true;
            }
            else
            {
                leftSubIndex += (3 - (pageCount - pageNum));
            }
            showLeftMoreButton = true;
            beginPageNum = pageNum - leftSubIndex;
        }
    }
    //qDebug() << showLeftMoreButton << showRightMoreButton;
    leftMoreButton->setVisible(showLeftMoreButton);
    rightMoreButton->setVisible(showRightMoreButton);
    // 中间的五个按钮，如果需要显示省略号，则减去1，剩下的用于显示数字
    int showBtnSize = pageButtonList.size() - showLeftMoreButton - showRightMoreButton;
    for(int i = 0; i < pageButtonList.size(); i++)
    {
        if(i < showBtnSize && beginPageNum + i < pageCount)
        {
            QString _pageNum = QString::number(beginPageNum + i);
            pageButtonList[i]->setText(_pageNum);
            pageButtonList[i]->setVisible(true);
            pageButtonList[i]->setFixedWidth(35 + (_pageNum.length() < 3 ? 0 : _pageNum.length() - 3) * 12);
            if(beginPageNum + i == pageNum)
            {
                pageButtonList[i]->setProperty("currentPage","true");
            }
            else
            {
                pageButtonList[i]->setProperty("currentPage","false");
            }
            pageButtonList[i]->style()->unpolish(pageButtonList[i]);
            pageButtonList[i]->style()->polish(pageButtonList[i]);
            pageButtonList[i]->update();
        }
        else
        {
            pageButtonList[i]->setVisible(false);
        }
    }
}

/**
 * @brief setCurrentPage 设置当前页码
 * @param pageNum 页码
 */
void pageControl::setCurrentPageEmitSignal(int pageNum)
{
    emit pageChanged(pageNum);
    setCurrentPage(pageNum);
}

void pageControl::setTotal(int _total)
{
    totalNumLabel->setText(QString("共%1条").arg(_total));
    int _pageCount = (_total + pageSize - 1) / pageSize;
    if(_pageCount != pageCount)
    {
        pageCount = _pageCount;
        if(pageNum >= pageCount)
        {
            pageNum = pageCount;
            lastPageButton->setProperty("currentPage", "true");
            lastPageButton->style()->unpolish(lastPageButton);
            lastPageButton->style()->polish(lastPageButton);
            lastPageButton->update();
            nextPageButton->setCheckable(false);
            //nextPageButton->setCursor(Qt::ForbiddenCursor);
        }
        else
        {
            lastPageButton->setProperty("currentPage","false");
//            m_pLastPageBtn->setStyleSheet("/**/");
            lastPageButton->style()->unpolish(lastPageButton);
            lastPageButton->style()->polish(lastPageButton);
            lastPageButton->update();
            nextPageButton->setCheckable(true);
            nextPageButton->setCursor(Qt::PointingHandCursor);
        }
        if(pageCount > 1)
        {
            lastPageButton->setVisible(true);
            QString maxPageNum = QString::number(pageCount);
            lastPageButton->setText(maxPageNum);
            lastPageButton->setFixedWidth(35 + (maxPageNum.length() < 3 ? 0 : maxPageNum.length() - 3) * 12);
        }
        else
        {
            lastPageButton->setVisible(false);
        }
        updatePageButton();
    }
}

// 一个按钮初始化的通用函数
QPushButton* pageControl::initPushButton()
{
    QPushButton* pushButton = new QPushButton(this);
    pushButton->setFixedSize(35, 35);
    pushButton->installEventFilter(this);
    return pushButton;
}

/* 初始化所有数字相关按钮并放入布局，顺序如下：
 * 前一页按钮/1/左省略号/五个数字页码/右省略号/后一页按钮
 */
void pageControl::initPageButton()
{
    pageButtonLayout = new QHBoxLayout();
    pageButtonLayout->setSpacing(8);
    pageButtonLayout->setMargin(0);

    prePageButton = initPushButton();
    prePageButton->setText("<");
    pageButtonLayout->addWidget(prePageButton);
    firstPageButton = initPushButton();
    firstPageButton->setText("1");
    pageButtonLayout->addWidget(firstPageButton);
    leftMoreButton = initPushButton();
    leftMoreButton->setText("...");
    pageButtonLayout->addWidget(leftMoreButton);
    for(int i = 0; i < 5; i++)
    {
        QPushButton *btn = initPushButton();
        pageButtonLayout->addWidget(btn);
        //btn->setCursor(Qt::PointingHandCursor);
        pageButtonList << btn;
    }
    rightMoreButton = initPushButton();
    rightMoreButton->setText("...");
    pageButtonLayout->addWidget(rightMoreButton);
    lastPageButton = initPushButton();
    pageButtonLayout->addWidget(lastPageButton);
    nextPageButton = initPushButton();
    nextPageButton->setText(">");
    pageButtonLayout->addWidget(nextPageButton);

    mainLayout->addLayout(pageButtonLayout);

}

/* 初始化页面跳转部分，包括
 * 文字label/文本输入框
 */
void pageControl::initJumpControl()
{
    jumpWidgetLayout = new QHBoxLayout();
    jumpWidgetLayout->setSpacing(5);
    jumpWidgetLayout->setMargin(0);

    goToLabel = new QLabel("前往");
    goToLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    goToLabel->setFixedHeight(35);
    jumpWidgetLayout->addWidget(goToLabel);

    pageSetLine = new QLineEdit(this);
    pageSetLine->setFixedSize(50, 35);
    pageSetLine->setAlignment(Qt::AlignCenter);
    pageSetLine->setValidator(new QIntValidator(1, 10000000, this));
    pageSetLine->installEventFilter(this);
    jumpWidgetLayout->addWidget(pageSetLine);

    pageUnitLabel = new QLabel("页   ", this);
    pageUnitLabel->setFixedHeight(35);
    jumpWidgetLayout->addWidget(pageUnitLabel);

    mainLayout->addLayout(jumpWidgetLayout);
}

/**
 * @brief pageControl::eventFilter
 * @param watched
 * @param e
 * @return
 */
bool pageControl::eventFilter(QObject *watched, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonRelease)
    {
        //上一页按钮被点击
        if(watched == prePageButton && prePageButton->isCheckable())
        {
            setCurrentPageEmitSignal(pageNum - 1);
        }
        //下一页按钮被点击
        else if(watched == nextPageButton && nextPageButton->isCheckable())
        {
            setCurrentPageEmitSignal(pageNum + 1);
        }
        //左边省略号按钮被点击
        else if(watched == leftMoreButton)
        {
            setCurrentPageEmitSignal(pageButtonList.at(1)->text().toInt() - 2);
        }
        //右边省略号按钮被点击
        else if(watched == rightMoreButton)
        {
            setCurrentPageEmitSignal(pageButtonList.at(2)->text().toInt() + 2);
        }
        else if(watched == firstPageButton)
        {
            setCurrentPageEmitSignal(1);
        }
        else if(watched == lastPageButton)
        {
            setCurrentPageEmitSignal(pageCount);
        }
        else
        {
            for (int i = 0; i < pageButtonList.size(); ++i)
            {
                if (watched == pageButtonList.at(i))
                {
                    setCurrentPageEmitSignal(pageButtonList.at(i)->text().toInt());
                    break;
                }
            }
        }
    }
    //跳转页敲击回车事件
    if (watched == pageSetLine && e->type() == QEvent::KeyRelease)
    {
        QKeyEvent *ke = reinterpret_cast<QKeyEvent *>(e);
        if (ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return)
        {
            setCurrentPageEmitSignal(pageSetLine->text().toInt());
            return true;
        }
    }
    return QWidget::eventFilter(watched, e);
}
