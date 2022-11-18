#ifndef DETAILPAGE_H
#define DETAILPAGE_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>

class detailPage : public QWidget
{
    Q_OBJECT
public:
    explicit detailPage(QWidget *parent = nullptr);

signals:

private:
    QScrollArea *detailArea;

};

#endif // DETAILPAGE_H
