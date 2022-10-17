#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QMouseEvent>

class MainWin : public QWidget
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

public slots:
    void closeButtonClicked();

private:
    QRect m_areaMoveable;
    bool m_mousePressed;
    QPoint m_pressedMousePos;

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};
#endif // MAINWIN_H
