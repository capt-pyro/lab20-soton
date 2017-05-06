#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "sendreceive.h"
#include <iostream>
#include <wiringPi.h>
#include <vector>
#include <pthread.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <QDebug>
#include <bitset>
#include <queue>
#include <pthread.h>
#include "common.h"

#define ALPHA 224
#define OMEGA 234

std::bitset<8> ToBits(unsigned char byte)
{
    return std::bitset<8>(byte);
}


void* sendWorker(void* ptr)
{
    //std::cout << "Inside Sendworker function!" << std::endl;
    while(1) {
        if(!pixQueue.empty()) {
            SendReceive::instance()->send(pixQueue.front());
            pixQueue.pop();
        }
    }
    //std::cout << "Getting out of Sendworker function!" << std::endl;
    // end thread
    pthread_exit(NULL);
}

std::queue<Pixel> pixQueue;

SendReceive::~SendReceive(){}

void SendReceive::setController(Controller* ctrl){
    this->controller = ctrl;
}

SendReceive *SendReceive::inst = 0;

SendReceive* SendReceive::instance()
{
    if (!inst) inst = new SendReceive();
    return inst;
}

SendReceive::SendReceive() {

    if (wiringPiSetup() == -1)
    {
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    }
    pinMode(0,OUTPUT);//Data out
    pinMode(2,OUTPUT);//ack to read data
    pinMode(3,INPUT);//data has been read now continue sender
    pullUpDnControl(3,PUD_DOWN);
    pinMode(1,INPUT);//Data in
    pinMode(4,INPUT);//read data now
    pinMode(5,OUTPUT);//data has been read by receiver
    pullUpDnControl(4,PUD_DOWN);
    connect(this,SIGNAL(foundPixel(Pixel)),this,SLOT(processPixel(Pixel)));

}

void SendReceive::send(Pixel pixel) {
        std::cout << "Pixel avaiable in queue" << std::endl;
        std::vector<char> buf;
        pixel.serialize(buf);
        binaryPutChar((char)ALPHA);//tells other pi to start reading

        std::cout << buf.size() << std::endl;
        for(int i =0;i<buf.size();i++) {
            binaryPutChar(buf[i]);
        }

        binaryPutChar((char)OMEGA);//tells pi to stop
}

void SendReceive::receive() {
    std::vector<char> vect;
    int state = 0;
    while(1) {
        //char c = serialGetchar(fd);
        char c = binaryGetChar();
        if((int)c == ALPHA) {
            //start building pixel
            state = 1;
        }
        else if((int)c == OMEGA) {
            //finish building pixel
            state = 0;

            Pixel pixel;
            pixel.deSerialize(vect);

            std::cout << "done: " << std::endl;
            std::cout << "X val " << pixel.getPoint().x() <<
                         "Y val " << pixel.getPoint().y() <<
                         "Color " << pixel.getColor().name().toStdString() << std::endl;

            vect.clear();
            //Used instead of SIGNAL/SLOT if needed
            //this->controller->updatePixel(pixel);

            emit foundPixel(pixel);
        }
        else if(state == 1) {
            //std::cout << "Receiving char: " << (int)c << std::endl;
            vect.push_back(c);
        }
    }

}


void SendReceive::processPixel(Pixel pixel)
{
    std::cout << "Inside processPixel slot" << std::endl;
    this->controller->updatePixel(pixel);
}

void SendReceive::transferPixel(/*std::queue<Pixel> pixQueue*/) {
    std::cout << "ENTERED TRANSFERPIXEL" << std::endl;
    //std::cout << "Pixel color" << pixel.getPoint().x() << std::endl;
    int deal;
    pthread_t row_thread;
    deal = pthread_create(&row_thread, NULL, &sendWorker, (void*)NULL);
    if (deal) {
        qDebug() << "Unable to start worker thread.";
        exit(1);
    }
    std::cout << "EXITING TRANSFERPIXEL" << std::endl;
    //Don't join the thread back as it will block the ui.
}


char SendReceive::binaryGetChar() {
    unsigned long k;
    unsigned char p;
    std::bitset<8> rbit;
    for(int i = 0;i < 8;) {
        if(digitalRead(4)) {
            rbit[i] = digitalRead(1);
            //std::cout << rbit[i] << std::endl;
            digitalWrite(5,HIGH);
            while(1) {
                if(digitalRead(4) == 0) {
                    digitalWrite(5,LOW);
                    break;
                }
            }
            i++;
        }
    }
    k = rbit.to_ulong();
    p = static_cast<unsigned char>(k);
    return (char)p;
}

void SendReceive::binaryPutChar(char c) {
    std::bitset<8> my_bset=ToBits(c);
    for(int i = 0;i < 8;i++) {
        //std::cout << "Sending bit" << my_bset[i] <<std::endl;
        digitalWrite(0,my_bset[i]);
        digitalWrite(2,HIGH);
        while(1) {
            if(digitalRead(3)) {
                digitalWrite(2,LOW);
                while(1) {
                    if(digitalRead(3) == 0) break;
                }
                break;
            }
        }
    }
}
