#include "window.h"
#include "controller.h"
#include "model.h"
#include "scribblearea.h"
#include "ui_window.h"
#include "scribblearea.h"
#include <QtWidgets>


Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    resize(500,500);
    setWindowTitle("P20 PROJECT");
    scribbleArea = new ScribbleArea(this);
    setCentralWidget(scribbleArea);
}

Window::~Window()
{
    delete ui;
}

void Window::on_actionClear_triggered()
{
    scribbleArea->clearImage();
}

Controller* Window::getController() {
    return controller;
}
Model* Window::getModel() {
    return model;
}
ScribbleArea* Window::getScribbleArea(){
    return scribbleArea;
}

void Window::setController(Controller* c) {this->controller = c;}

void Window::setModel(Model* m) {this->model = m;}

