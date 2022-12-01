#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>

class grid : public QWidget
{
    Q_OBJECT
public:
    explicit grid(QWidget *parent = nullptr);
    void initMovies();

public slots:
    void showPage(int p);

signals:

private:
    QVBoxLayout *mainLayout;  // 整体竖直布局，所有电影一块，页面控制器一块
    QGridLayout *allItemsLayout;  // 所有电影以网格布局
    QVBoxLayout *movieLayout;  // 每个电影包括海报和名字，竖直布局
    QList<QPushButton *> movieList;

};

#endif // GRID_H
