#ifndef MODEL_H
#define MODEL_H

#include <QImage>

class Model {
public:
  Model();
  ~Model();
  void clear();
  QImage* getImage();
  QImage getImageObj();

private:
  QImage image;
};

#endif // MODEL_H
