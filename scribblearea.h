#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <window.h>
#include "sendreceive.h"
#include "pixel.h"
#include <queue>

class Window;

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    ScribbleArea(Window *);

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void clearImage();
    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    Pixel drawLineTo(QPoint prevPoint, const QPoint &endPoint, bool uiSource, QColor lineColor);
    void setLastPoint(QPoint);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:

    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QPoint lastPoint;
    Window* window;
    //std::queue<Pixel> pixelQueue;
};

#endif // SCRIBBLEAREA_H
