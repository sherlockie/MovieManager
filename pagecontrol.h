#ifndef PAGECONTROL_H
#define PAGECONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

class pageControl : public QWidget
{
    Q_OBJECT
public:
    explicit pageControl(QWidget *parent = nullptr);
    void initPage(int total, int pageNum = 1, int pageSize = 10);
    void setTotal(int total);
    void setCurrentPage(int pageNum = 1);
    void setCurrentPageEmitSignal(int pageNum = 1);
    //void setPageSize(int pageSize = 10);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *e);

signals:
    void pageChanged(int currentPage);

private:
    void initJumpControl();
    void initPageButton();
    void updatePageButton();
    QPushButton *initPushButton();

private:
    QHBoxLayout *mainLayout;
    QLabel *totalNumLabel;

    QHBoxLayout *pageButtonLayout;
    QPushButton *prePageButton;
    QPushButton *nextPageButton;
    QPushButton *firstPageButton;
    QPushButton *lastPageButton;
    QPushButton *leftMoreButton;
    QPushButton *rightMoreButton;
    QList<QPushButton*> pageButtonList;
    bool showLeftMoreButton;
    bool showRightMoreButton;

    QHBoxLayout *jumpWidgetLayout;
    QLabel *goToLabel;
    QLineEdit *pageSetLine;
    QPushButton *goToButton;
    QLabel *pageUnitLabel;

    int pageNum;
    int pageSize;
    int pageCount;
    int total;
    int midButtonNum;
};

#endif // PAGECONTROL_H
