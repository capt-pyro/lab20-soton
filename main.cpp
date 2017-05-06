#include <QApplication>
#include <QDebug>
#include <QString>
#include <iostream>
#include "common.h"
#include <pthread.h>
#include <wiringPi.h>
#include "window.h"
#include "controller.h"
#include "model.h"
#include <pixel.h>
#include "sendreceive.h"

void* receiveWorker(void* ptr)
{
    SendReceive::instance()->receive();
    // end thread
    pthread_exit(NULL);
}


//std::queue<Pixel> pixQueue;

int main(int argc, char *argv[])
{

    qRegisterMetaType<Pixel>(); //Enable or tell qt that pixel exists for signal/slot
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    //wiringPiSetup();
    //pinMode (0, OUTPUT);
    QApplication a(argc, argv);
    Window w;
    Model model;
    Controller ctrl(&model,&w);
    w.setController(&ctrl);
    w.setModel(&model);

    // starting worker thread(s)

    SendReceive::instance()->setController(&ctrl);
    int rc;
    pthread_t worker_thread;
    rc = pthread_create(&worker_thread, NULL, &receiveWorker, (void*)NULL);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
        exit(1);
    }

    std::cout << "Before sendworker thread " <<std::endl;
    //SendReceive::instance()->transferPixel(w.getScribbleArea()->getPixelQueue());
    // setup Qt GUI


    w.show();
    SendReceive::instance()->transferPixel(/*w.getScribbleArea()->getPixelQueue()*/);
    // start window event loop
    qDebug() << "Starting event loop...";
    int ret = a.exec();
    qDebug() << "Event loop stopped.";




    // cleanup pthreads
    pthread_exit(NULL);

    // exit
    return ret;
}
