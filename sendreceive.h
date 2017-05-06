#ifndef SENDRECEIVE_H
#define SENDRECEIVE_H

#include "pixel.h"
#include "controller.h"
#include <QObject>
#include <queue>
class Controller;

class SendReceive : public QObject{

    Q_OBJECT

public:
    ~SendReceive();
    void send(Pixel pixel);
    void receive();
    static SendReceive *instance();
    void setController(Controller* ctrl);
    void transferPixel(/*std::queue<Pixel> pixQueue*/);

signals:
    void foundPixel(Pixel);

private slots:
    void processPixel(Pixel);

private:
    int fd;
    Controller *controller;
    static SendReceive* inst;
    SendReceive();
    char binaryGetChar();
    void binaryPutChar(char);
};

#endif // SENDRECEIVE_H
