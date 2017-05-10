#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "window.h"
#include "pixel.h"
#include <QPoint>
#include <mutex>

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
  QPoint prevP;
  std::mutex imageMutex;
};

#endif // CONTROLLER_H
