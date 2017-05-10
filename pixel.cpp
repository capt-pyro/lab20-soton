#include <pixel.h>
#include <iostream>

    Pixel::Pixel(){}

    void Pixel::serialize(std::vector<char>& buf) {
        // The buffer we will be writing bytes into
        char outBuf[(8*sizeof(char)) + (3*sizeof(int))];

        // A pointer we will advance whenever we write data
        char *p = outBuf;

        // Serialize "x" into outBuf
        int x = this->point.x();
        memcpy(p, &x, sizeof(int));
        p += sizeof(int);

        // Serialize "y" into outBuf
        int y = this->point.y();
        memcpy(p, &y, sizeof(int));
        p += sizeof(int);

        // Serialize "color" into outBuf
        char col[8];
        QString qstr = this->color.name();
        memcpy( col, qstr.toStdString().c_str() ,qstr.size());
        col[7] = '\0';
        memcpy(p, col, sizeof(col));
        p += sizeof(col);

        //lastpoint Serialize
/*        int lPx = this->prevPoint.x();
        std::cout << "PrevPoint " << lPx << std::endl;
        memcpy(p,&lPx,sizeof(int));
        p += sizeof(int);

        int lPy = this->prevPoint.y();
        std::cout << "PrevPoint " << lPy << std::endl;
        memcpy(p,&lPy,sizeof(int));
        p += sizeof(int);
*/
        int pB = this->prevPointBool;
       // std::cout << "PrevPoint " << lPy << std::endl;
        memcpy(p,&pB,sizeof(int));
        p += sizeof(int);

        for(int i=0; i< p-outBuf; i++) {
            buf.push_back(outBuf[i]);
        }
    }

//DESERIALIZE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    void Pixel::deSerialize(std::vector<char>& buf) {
        int size = buf.size();
        char outBuf[(8*sizeof(char)) + (3*sizeof(int))];

        for(int i=0; i< size; i++) {
            outBuf[i] = buf[i];
        }
        // A pointer we will advance whenever we write data
        char *p = outBuf;

        // Serialize "x" into outBuf
        int x;
        memcpy(&x, p, sizeof(int));
        this->point.setX(x);
        p += sizeof(int);

        // Serialize "y" into outBuf
        int y;
        memcpy(&y, p, sizeof(int));
        this->point.setY(y);
        p += sizeof(int);

        // Serialize "color" into outBuf
        char col[8];
        memcpy(col, p, 8*sizeof(char));
        QString qstr(col);
        this->color.setNamedColor(qstr);
        p += sizeof(col);

        //lastpoint Deserialize
/*        int tx;
        memcpy(&tx,p,sizeof(int));
        this->prevPoint.setX(tx);        
        p += sizeof(int);

        int ty;
        memcpy(&ty,p,sizeof(int));
        this->prevPoint.setY(ty);
        p += sizeof(int);
        */
        int lPB;
        memcpy(&lPB,p,sizeof(int));
        this->setPrevPBool(lPB);
        p += sizeof(int);
    }
//Start of Getter/Setter
    void Pixel::setPoint(QPoint point){
        this->point = point;
    }

    QPoint Pixel::getPoint() {
        return this->point;
    }

    void Pixel::setColor(QColor color){
        this->color = color;
    }

    QColor Pixel::getColor(){
        return this->color;
    }
/*    void Pixel::setPrevPoint(QPoint b) {
        this->prevPoint = b;
    }
    QPoint Pixel::getPrevPoint() {
        return this->prevPoint;
    }*/

    void Pixel::setPrevPBool(int b) {
          this->prevPointBool = b;
      }
    int Pixel::getPrevPBool() {
          return this->prevPointBool;
      }

    //End of Getter/Setter
