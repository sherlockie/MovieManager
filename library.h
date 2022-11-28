#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>
#include <QToolButton>
#include <QStackedWidget>

class library : public QWidget
{
    Q_OBJECT
public:
    explicit library(QWidget *parent = nullptr);

public slots:
    void listButtonClicked();
    void gridButtonClicked();
    void refreshButtonClicked();

private:
    QStackedWidget *allMovieView;

};

#endif // LIBRARY_H
