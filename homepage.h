#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "graphicspixmap.h"

#include <QWidget>
#include <QMap>
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTimer>

class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);
    ~HomePage();

private:
    void initImgPlaceholder();
    void nextPlay();
    void lastPlay();
    void play();

private slots:
    void leftButtonClicked();
    void rightButtonClicked();
    void imgHoverMove();
    void imgHoverLeave();

private:
    QGraphicsScene* m_scene;
    QList<QMap<QString, float>> m_imgInfoMapList;
    QList<GraphicsPixmap *> m_imgs;
    QParallelAnimationGroup *m_imgsAnimGroup;
    QMap<GraphicsPixmap *, QPropertyAnimation *>m_imgOffsetAnimMap;
    QMap<GraphicsPixmap *, QPropertyAnimation *>m_imgSizeAnimMap;
    QTimer *m_timer;
    bool m_isStart;
};

#endif // HOMEPAGE_H
