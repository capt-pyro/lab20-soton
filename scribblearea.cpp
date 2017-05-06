#include <QtWidgets>
#include <wiringPi.h>
#include "scribblearea.h"
#include "sendreceive.h"
#include <pthread.h>
#include "common.h"

ScribbleArea::ScribbleArea(Window *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
    window = parent;
}

void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}


void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void ScribbleArea::clearImage()
{
    window->getController()->wipeImage();
    modified = true;
    update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        /*
        Pixel pixel;
        pixel.setLastPBool(1);
        pixel.setColor(myPenColor);
        pixel.setPoint(lastPoint);
        pixQueue.push(pixel);
        */
        scribbling = true;//trigger boolean that starts recording mousemoveevents.
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling) {
        //SendReceive::instance()->transferPixel(drawLineTo(event->pos()));
        //pixelQueue.push(drawLineTo(event->pos()));
        pixQueue.push(lastPoint, drawLineTo(event->pos()),true);
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        //SendReceive::instance()->transferPixel(drawLineTo(event->pos()));
        //pixelQueue.push(drawLineTo(event->pos()));
        pixQueue.push(drawLineTo(event->pos()));
        scribbling = false;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, window->getModel()->getImageObj(), dirtyRect);
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > window->getModel()->getImage()->width() || height() > window->getModel()->getImage()->height()) {
        int newWidth = qMax(width() + 128, window->getModel()->getImage()->width());
        int newHeight = qMax(height() + 128, window->getModel()->getImage()->height());
        resizeImage(window->getModel()->getImage(), QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

Pixel ScribbleArea::drawLineTo(QPoint prevPoint,const QPoint &endPoint,bool uiSource)
{
    QPainter painter(window->getModel()->getImage());
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(prevPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(prevPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    if(uiSource) {
        lastPoint = endPoint;
    }
    Pixel pixel;
    pixel.setPoint(endPoint);
    pixel.setColor(myPenColor);
    pixel.setLastPBool(0);
    return pixel;
}

void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (window->getModel()->getImage()->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ScribbleArea::setLastPoint(QPoint lP) {
    lastPoint = lP;
}

