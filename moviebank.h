#ifndef MOVIEBANK_H
#define MOVIEBANK_H

#include "QFileInfoList"
#include <QWidget>
#include <QFrame>
#include <QToolButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>

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
