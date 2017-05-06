#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "window.h"
#include "pixel.h"

class Model;
class Window;

class Controller {
public:
    Controller(Model* m, Window* w);
    Controller();
    virtual ~Controller();
    void wipeImage();
    void updatePixel(Pixel);

private:
  Model* model;
  Window *window;
};

#endif // CONTROLLER_H
