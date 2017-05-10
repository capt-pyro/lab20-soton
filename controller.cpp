#include <controller.h>
#include <iostream>
#include "common.h"
#include <QPoint>
std::mutex imageMutex;
QPoint qpoint;
//Constructor
Controller::Controller(Model* m, Window* w):model(m),window(w){}
Controller::Controller(){}

//Destructor
Controller::~Controller(){}

//Clear Model
void Controller::wipeImage() {
    model->clear();
}

//Update Pixel
/*
void Controller::updatePixel(Pixel pixel) {
        //Checks for out of bound values
        if(pixel.getPoint().x() > 10000 || pixel.getPoint().y() > 10000 ||
           pixel.getPoint().x() < -10000 || pixel.getPoint().y() < -10000) return;

        //Works when prevpoint is corrupted
        if(pixel.getPrevPoint().x() > 10000 || pixel.getPrevPoint().y() > 10000 ||
           pixel.getPrevPoint().x() < -10000 || pixel.getPrevPoint().y() < -10000) {
            imageMutex.lock();
            window->getScribbleArea()->drawLineTo(this->prevP, pixel.getPoint(), false,pixel.getColor());
            imageMutex.unlock();
        }
        //Clears screen -100 is command to clear screen
        else if (pixel.getPoint().x() == -100) {
            imageMutex.lock();
            window->getScribbleArea()->clearImage();
            imageMutex.unlock();
        }
        //Normal drawing
        else {
            imageMutex.lock();
            window->getScribbleArea()->drawLineTo(pixel.getPrevPoint(), pixel.getPoint(), false,pixel.getColor());
            this->prevP = pixel.getPoint();
            imageMutex.unlock();
        }
}*/

void Controller::updatePixel(Pixel pixel) {
        //Checks for out of bound values
        if(pixel.getPoint().x() > 10000 || pixel.getPoint().y() > 10000 ||
           pixel.getPoint().x() < -10000 || pixel.getPoint().y() < -10000){return;}
        //Clears screen -100 is command to clear screen
        if (pixel.getPoint().x() == -100) {
            imageMutex.lock();
            window->getScribbleArea()->clearImage();
            imageMutex.unlock();
        }
        else if(pixel.getPrevPBool() == 1) {
            qpoint.setX(pixel.getPoint().x());
            qpoint.setY(pixel.getPoint().y());
            //std::cout << "NOOOOOOOOOOOOOOOOOOO" << std::endl;
            return;
        }
        //Normal drawing
        else {
            imageMutex.lock();
            std::cout << "qpointx " << qpoint.x() << " qpoint y " << qpoint.y() <<std::endl;
            window->getScribbleArea()->drawLineTo(qpoint, pixel.getPoint(), false,pixel.getColor());
            qpoint = pixel.getPoint();
            imageMutex.unlock();
        }
}
