
#include "model.h"

//Constructor
Model::Model() {

}

//Destructor
Model::~Model(){}

void Model::clear() {
    image.fill(qRgb(255, 255, 255));//Clear image to
}

QImage* Model::getImage() {
    return &image;
    //Gives image pointer
}

QImage Model::getImageObj() {
    return image;
    //gives image
}

