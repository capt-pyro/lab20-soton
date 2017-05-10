#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>
#include <QPoint>
#include <QString>
#include "serializable.h"

class Pixel : public Serializable{
public:

    Pixel();
    void setPoint(QPoint point);
    QPoint getPoint();
    void setColor(QColor color);
    QColor getColor();
    /*void setPrevPoint(QPoint);
    QPoint getPrevPoint();
    */
    void setPrevPBool(int b);
    int getPrevPBool();

    void serialize(std::vector<char>& buf);
    void deSerialize(std::vector<char>& buf);

private:
    QPoint point;
    QColor color;
    //QPoint prevPoint;//new last point scribble
    int prevPointBool;
};

Q_DECLARE_METATYPE(Pixel);// signal/slot handling

#endif // PIXEL_H
