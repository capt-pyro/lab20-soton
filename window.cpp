#include "window.h"
#include "controller.h"
#include "model.h"
#include "scribblearea.h"
#include "ui_window.h"
#include "scribblearea.h"
#include <QtWidgets>
#include "common.h"
#include <QPoint>


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


void Window::on_actionClearScreen_triggered()
{
    getScribbleArea()->clearImage();
    QPoint qP(-100,-100);
    Pixel pixel;
    pixel.setPoint(qP);
    pixel.setColor(Qt::blue);
    pixel.setPrevPBool(0);
    pixQueue.push(pixel);


}

void Window::on_actionPenColor_triggered()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
        if (newColor.isValid()) {
            getScribbleArea()->setPenColor(newColor);
        }
}

void Window::on_actionPenWidth_triggered()
{
   /* bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        getScribbleArea()->penWidth(),
                                        1, 50, 1, &ok);
    if (ok) {
        getScribbleArea()->setPenWidth(newWidth);
    }*/
}
