#ifndef LIST_H
#define LIST_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>

class list : public QWidget
{
    Q_OBJECT
public:
    explicit list(QWidget *parent = nullptr);

signals:

public slots:
    void showPage(int p);

private:
    QStandardItemModel *tableModel;
    QTableView *tableView;

};

#endif // LIST_H
