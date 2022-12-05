#ifndef LIST_H
#define LIST_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlQueryModel>
#include <QHeaderView>

// 表格模型，与数据库交互
class sqlModel: public QSqlQueryModel
{
public:
    explicit sqlModel(QObject *parent = nullptr);

protected:
    QVariant data(const QModelIndex &index, int role) const;

private:
    bool allCenter;
    QList<int> alignCenterColumn;
    QList<int> alignRightColumn;
public:
    //设置所有列居中
    void setAllCenter(bool allCenter);
    //设置居中对齐列索引集合
    void setAlignCenterColumn(const QList<int> &alignCenterColumn);
    //设置右对齐列索引集合
    void setAlignRightColumn(const QList<int> &alignRightColumn);
};
// 数据库操作线程类
//class

// 整体展示页面，结合表格和下方的页面控制控件
class list : public QWidget
{
    Q_OBJECT
public:
    explicit list(QWidget *parent = nullptr);
    //设置数据库连接名称
    void setConnName(const QString &connName);

signals:

public slots:
    void showPage(int p);

private:
    QSqlQueryModel *tableModel;
    QTableView *tableView;

    quint32 pageSize;  // 每页显示数目
    quint32 totalPage;  // 一共有多少电影
    quint32 currentPage;  // 当前页数
    QString connName;  // 数据库连接名
    QList<QString> columnNames; //列名集合
    QList<int> columnWidths;    //列宽集合

};

#endif // LIST_H
