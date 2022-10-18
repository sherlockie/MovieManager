#include "graphicspixmap.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

GraphicsPixmap::GraphicsPixmap()  // : QGraphicsObject()
{
    setCacheMode(DeviceCoordinateCache);
}

void GraphicsPixmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}

void GraphicsPixmap::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverMove();
}

void GraphicsPixmap::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverLeave();
}

QPointF GraphicsPixmap::getItemOffset()
{
    return this->offset;
}

QSize GraphicsPixmap::getPixmapSize()
{
    return this->pixSize;
}

void GraphicsPixmap::setItemOffset(QPointF point)
{
    this->prepareGeometryChange();
    this->offset = point;
    this->update();
}

void GraphicsPixmap::setPixmap(const QPixmap& pixmap)
{
    this->pixSize = pixmap.size();
    this->pix = pixmap;
}

void GraphicsPixmap::setPixmapSize(QSize size)
{
    this->pixSize = size;
}

QRectF GraphicsPixmap::boundingRect() const
{
//    qDebug() << pix.size() << pixSize << offset;
//    return QRectF(offset, pix.size() / pix.devicePixelRatio());
    return QRectF(offset, pixSize / pix.devicePixelRatio());
}

void GraphicsPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    qDebug() << "call paint" << pixSize;
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->drawPixmap(offset, pix.scaled(pixSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
