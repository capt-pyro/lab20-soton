#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "scribblearea.h"
#include "controller.h"
#include "model.h"

class ScribbleArea;
class Controller;

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    void setController(Controller* c);
    void setModel(Model* m);
    Controller* getController();
    Model* getModel();
    ScribbleArea* getScribbleArea();


private:
    Controller*  controller;
    Model* model;
    Ui::Window *ui;
    ScribbleArea *scribbleArea;

private slots:
    void on_actionClearScreen_triggered();
    void on_actionPenColor_triggered();
    void on_actionPenWidth_triggered();
};

#endif // WINDOW_H
