#ifndef MOVIEBANK_H
#define MOVIEBANK_H

#include "QFileInfoList"
#include <QWidget>
#include <QFrame>
#include <QToolButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>

/* 数据库设计：
 * 实体：电影；导演；演员；类别；
 *      全部都是多对多
 * 表1 主要信息表：
 * - 电影id： 唯一id，主键，非空
 * - 电影名称：字符串
 * - 电影文件路径
 * - 海报路径
 * - 年代
 * - 地区
 *
 * 表2 导演表
 * - 导演id
 * - 导演姓名
 * - 导演性别
 *
 * 表3 导演和电影对应表
 * - 导演id
 * - 电影id
 *
 * 表4 演员表
 * - 演员id
 * - 演员姓名
 * - 演员性别
 *
 * 表5 演员和电影对应关系
 * - 演员id
 * - 电影id
 *
 * 表6 类别表
 * - 类别id
 * - 类别名称
 *
 * 表7 电影和类别关系表
 * - 电影id
 * - 类别id
 */
class movieBank : public QWidget
{
    Q_OBJECT
public:
    explicit movieBank(QWidget *parent = nullptr);
    void findAllFiles(QString path, QFileInfoList &fileList);

public slots:
    void syncButtonClicked();
    void addButtonClicked();
    void decButtonClicked();

private:
    QStandardItemModel *tableModel;
    QTableView *tableView;

signals:

};

#endif // MOVIEBANK_H
