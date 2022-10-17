#ifndef GRAPHICSPIXMAP_H
#define GRAPHICSPIXMAP_H

//#include <QObject>
#include <QGraphicsObject>

class GraphicsPixmap : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF itemoffset READ getItemOffset WRITE setItemOffset)
    Q_PROPERTY(QSize itemsize READ getPixmapSize WRITE setPixmapSize)
public:
    GraphicsPixmap();

public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void setItemOffset(QPointF point);
    QPointF getItemOffset();
    QSize getPixmapSize();
    void setPixmap(const QPixmap& pixmap);
    void setPixmapSize(QSize size);

signals:
    void clicked();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

private:
    QPixmap pix;
    QPointF offset;
    QSize pixSize;
};

#endif // GRAPHICSPIXMAP_H
