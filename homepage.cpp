#include "homepage.h"
#include "graphicspixmap.h"
#include "graphicsview.h"
#include <QDebug>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
//    this->setWindowTitle("Local Test Sample");
    this->setStyleSheet("background-color:black;");
    this->resize(1600, 860);
    // scene
    m_scene = new QGraphicsScene(QRect(0, 0, 1600, 860), this);  // 876, 368; 1.83, 2.34
    // images infos
    m_imgInfoMapList << QMap<QString, float> {
        { "zIndex", 1},
        { "width", 120},
        { "height", 150},
        { "top", 71},
        { "left", 134},
        { "opacity" , 0.6}
    };
    m_imgInfoMapList << QMap<QString, float>{
        { "zIndex", 2},
        { "width", 130},
        { "height", 170},
        { "top", 61},
        { "left", 0},
        { "opacity", 0.7}
    };
    m_imgInfoMapList << QMap<QString, float>{
        { "zIndex", 3},
        { "width", 170},
        { "height", 218},
        { "top", 37},
        { "left", 110},
        { "opacity", 0.8}
    };
    m_imgInfoMapList << QMap<QString, float>{
        { "zIndex", 4},
        { "width", 224},
        { "height", 288},
        { "top", 0},
        { "left", 262},
        { "opacity", 1}
    };
    m_imgInfoMapList << QMap<QString, float>{
        { "zIndex", 3},
        { "width", 170},
        { "height", 218},
        { "top", 37},
        { "left", 468},
        { "opacity", 0.8}
    };
    m_imgInfoMapList << QMap<QString, float>{
        { "zIndex", 2},
        { "width", 130},
        { "height", 170},
        { "top", 61},
        { "left", 620},
        { "opacity", 0.7}
    };
    m_imgInfoMapList << QMap<QString, float>{
        { "zIndex", 1},
        { "width", 220},
        { "height", 150},
        { "top", 71},
        { "left", 496},
        { "opacity", 0.6}
    };

    // add images to scene
    for (int i = 0; i < m_imgInfoMapList.size(); ++i)
    {
        const auto imgInfoMap = m_imgInfoMapList[i];
        const QString&& centerImg = QString(":/default/Resources/%1.jpg").arg(i + 1);
        const QPixmap&& pixmap = QPixmap(centerImg);
        GraphicsPixmap *item = new GraphicsPixmap();
        item->setPixmap(pixmap);
        item->setPixmapSize(QSize(imgInfoMap["width"], imgInfoMap["height"]));
        item->setItemOffset(QPointF(imgInfoMap["left"] + 60, imgInfoMap["top"] + 40));
        item->setZValue(imgInfoMap["zIndex"]);
        item->setOpacity(imgInfoMap["opacity"]);
        m_imgs << item;
        m_scene->addItem(item);
    }
    // left button
    GraphicsPixmap *leftButton = new GraphicsPixmap();
    leftButton->setCursor(QCursor(Qt::PointingHandCursor));
    leftButton->setItemOffset(QPointF(12, 430));
    leftButton->setPixmap(QPixmap(":/icons/Resources/Wblog_left.png"));
//    leftButton->setZValue(5);
    m_scene->addItem(leftButton);
    connect(leftButton, SIGNAL(clicked()), this, SLOT(leftButtonClicked()));

    // right button
    GraphicsPixmap *rightButton = new GraphicsPixmap();
    rightButton->setCursor(QCursor(Qt::PointingHandCursor));
    rightButton->setItemOffset(QPointF(1530, 430));
    rightButton->setPixmap(QPixmap(":/icons/Resources/Wblog_right.png"));
//    rightButton->setZValue(5);
    m_scene->addItem(rightButton);
    connect(rightButton, SIGNAL(clicked()), this, SLOT(rightButtonClicked()));

    // view
    QGraphicsView *view = new GraphicsView(m_scene);
    view->setParent(this);
    view->setFrameShape(QFrame::NoFrame);
//    view->setBackgroundBrush(QColor(46, 46, 46));
//    view->show();
    // animations
    qDebug() << "Init animations";
    m_imgsAnimGroup = new QParallelAnimationGroup();
    for (int i = 0; i < m_imgs.count(); ++i)
    {
        QPropertyAnimation *offsetAnim = new QPropertyAnimation(m_imgs[i], "itemoffset");
        QPropertyAnimation *sizeAnim = new QPropertyAnimation(m_imgs[i], "itemsize");
        m_imgOffsetAnimMap.insert(m_imgs[i], offsetAnim);
        m_imgSizeAnimMap.insert(m_imgs[i], sizeAnim);
        offsetAnim->setDuration(1000);
        sizeAnim->setDuration(1000);
        offsetAnim->setEasingCurve(QEasingCurve::OutQuad);
        sizeAnim->setEasingCurve(QEasingCurve::OutQuad);
        m_imgsAnimGroup->addAnimation(offsetAnim);
        m_imgsAnimGroup->addAnimation(sizeAnim);
    }

    // timer, change image
    qDebug() << "Init timer";
    m_timer = new QTimer(this);
    m_timer->setInterval(2000);
    connect(m_timer, &QTimer::timeout, [this](){
        nextPlay();
    });
    connect(m_imgsAnimGroup, &QParallelAnimationGroup::finished, [this](){
        m_isStart = false;
        m_timer->start();
    });
    m_timer->start();
}

HomePage::~HomePage()
{
}

void HomePage::leftButtonClicked()
{
//    qDebug() << "left button clicked!";
    m_timer->stop();
    lastPlay();
}

void HomePage::rightButtonClicked()
{
//    qDebug() << "right button clicked!";
    m_timer->stop();
    nextPlay();
}

void HomePage::play()
{
    for (int i = 0; i < m_imgInfoMapList.size(); ++i)
    {
        const auto item = m_imgs[i];
        QPropertyAnimation *offsetAnim = m_imgOffsetAnimMap.value(item);
        QPropertyAnimation *sizeAnim = m_imgSizeAnimMap.value(item);
        const auto imgInfoMap = m_imgInfoMapList[i];
        item->setZValue(imgInfoMap["zIndex"]);
        item->setOpacity(imgInfoMap["opacity"]);
        QPointF pointf(imgInfoMap["left"] + 60, imgInfoMap["top"] + 40);
//        const QString&& centerImg = QString(":/ImageViewWindow/Resources/%1.jpg").arg(i + 1);
        offsetAnim->setStartValue(item->getItemOffset());
        sizeAnim->setStartValue(item->getPixmapSize());
        offsetAnim->setEndValue(pointf);
        sizeAnim->setEndValue(QSize(imgInfoMap["width"], imgInfoMap["height"]));
    }
    m_isStart = true;
}

void HomePage::nextPlay()
{
    this->m_imgsAnimGroup->stop();
    auto firstItem = m_imgs.takeAt(0);  // take out current first img
    m_imgs.append(firstItem);  // put it to the end
    play();
    this->m_imgsAnimGroup->start();
}

void HomePage::lastPlay()
{
    this->m_imgsAnimGroup->stop();
    auto lastItem = m_imgs.takeAt(m_imgs.size() - 1);  // take out current last img
    m_imgs.prepend(lastItem);  // put it to the beginning
    play();
    this->m_imgsAnimGroup->start();
}
