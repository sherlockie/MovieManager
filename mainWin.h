#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QMenu>

class MainWin : public QWidget
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();
    void initMenu();

public slots:
    void closeButtonClicked();
    void homeButtonClicked();
    void searchButtonClicked();
    void aboutActionTriggered();
    void addNewActionTriggered();
    void settingActionTriggered();
    void detailButtonClicked();
    void libraryButtonClicked();
    void cardClicked(int i);

private:
    QRect m_areaMoveable;
    bool m_mousePressed;
    QPoint m_pressedMousePos;
    QStackedWidget *pageStack;
    QMenu *menu;

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};
#endif // MAINWIN_H
