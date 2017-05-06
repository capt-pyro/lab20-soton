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
    void setLastPBool(int);
    int getLastPBool();

    void serialize(std::vector<char>& buf);

    void deSerialize(std::vector<char>& buf);
private:
    QPoint point;
    QColor color;
    int lastPBool;//new last point scribble
};

Q_DECLARE_METATYPE(Pixel);// signal/slot handling new

#endif // PIXEL_H
