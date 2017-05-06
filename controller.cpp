#include <controller.h>
#include <iostream>

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
void Controller::updatePixel(Pixel pixel) {
    if(pixel.getLastPBool() == 1) {
        window->getScribbleArea()->setLastPoint(pixel.getPoint());
        std::cout <<"LastPoint" << std::endl;
    }
    else {
        if(pixel.getPoint().x() > 10000 || pixel.getPoint().y() > 10000) return;
        window->getScribbleArea()->drawLineTo(pixel.getPoint());
        std::cout <<"regular drawing" << std::endl;
    }

}
