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
    update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        Pixel pixel;
        pixel.setPrevPBool(1);
        pixel.setColor(myPenColor);
        //QPoint qp(10,10);
        pixel.setPoint(lastPoint);
        pixQueue.push(pixel);
        scribbling = true;//trigger boolean that starts recording mousemoveevents.
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling) {
        pixQueue.push(drawLineTo(lastPoint,event->pos(),true,myPenColor));
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        pixQueue.push(drawLineTo(lastPoint, event->pos(),true,myPenColor));
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

Pixel ScribbleArea::drawLineTo(QPoint prevPoint,const QPoint &endPoint,bool uiSource, QColor lineColor) {
    QPainter painter(window->getModel()->getImage());
    painter.setPen(QPen(lineColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(prevPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(prevPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    Pixel pixel;
    pixel.setPoint(endPoint);
    pixel.setColor(myPenColor);
    //pixel.setPrevPoint(lastPoint);
    pixel.setPrevPBool(0);

    if(uiSource) {
        lastPoint = endPoint;
    }
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
