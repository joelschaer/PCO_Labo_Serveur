#ifndef BUFFERN_H
#define BUFFERN_H

#include "abstractbuffer.h"
#include "hoaremonitor.h"


template<typename T> class BufferN : public AbstractBuffer<T>, public HoareMonitor
{
protected:
    T *elements;
    int writePointer, readPointer, nbElements, bufferSize;
    unsigned nbWaitingProd, nbWaitingConso;
    Condition notFull, notEmpty;

public:
    BufferN(unsigned int size){
        if((elements = new T[bufferSize]) != 0){
            writePointer = readPointer = nbElements = 0;
            nbWaitingProd = nbWaitingConso = 0;
            bufferSize = size;
            return;
        }
        //throw NoInitTamponN;
    }

    void put(T item){

        monitorIn();

        if(nbElements == bufferSize){
            wait(&notFull);
        }
        elements[writePointer] = item;
        writePointer = (writePointer + 1) % bufferSize;
        nbElements ++;

        signal(notEmpty);
        monitorOut();
    }

    T get (void){
        T item;

        monitorIn();

        if(nbElements == 0){
            wait(&notEmpty);
        }
        item = elements[readPointer];
        readPointer = (readPointer + 1) & bufferSize;
        nbElements --;

        signal(notFull);
        monitorOut();
        return item;
    }
};

#endif // BUFFERN_H
