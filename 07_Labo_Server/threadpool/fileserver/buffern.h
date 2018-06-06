/*******************************
** BufferN
** buffern.h/.cpp
**
** Yann Lederrey and Joel Schär
**
** Generic buffer extending AbstractBuffer using an Hoare Monitor system for mutual exclusion
** handling. It uses an elements pointed table for saving it's content.
**
**/

#ifndef BUFFERN_H
#define BUFFERN_H

#include "abstractbuffer.h"
#include "hoaremonitor.h"


template<typename T>
class BufferN : public AbstractBuffer<T>, public HoareMonitor
{
protected:
    T *elements; // elements pointer ( table where the elements are stored ), has a defined size.
    int writePointer, readPointer; // pointer to the nex element to read or where to write the next element.
    int nbElements, bufferSize; // keeps track of buffers size and content size.
    unsigned nbWaitingProd, nbWaitingConso; // number of waiting threads to get or put elements
    Condition notFull, notEmpty;  // condition the threads will be waiting for to be signaled if the buffer is empty ,of full.

public:

    /**
     * @brief BufferN Constructor
     * @param size
     */
    BufferN(unsigned int size){
        if((elements = new T[size]) != 0){
            writePointer = readPointer = nbElements = 0;
            nbWaitingProd = nbWaitingConso = 0;
            bufferSize = size;
        }
    }

    /**
     * @brief ~BufferN Destructor
     */
    ~BufferN(){
        while(nbElements>0){
            this->get();
        }
        delete elements;
    }

    /**
     * @brief put adding an element to the buffer
     * @param item Item that need's to be kept in the buffer
     */
    void put(T item){

        monitorIn();

        if(nbElements == bufferSize){
            wait(notFull);
        }
        elements[writePointer] = item;
        writePointer = (writePointer + 1) % bufferSize;
        nbElements ++;

        signal(notEmpty);
        monitorOut();
    }

    /**
     * @brief tryPut adding an element to the buffer unless the maximum sizes is reached.
     * If the buffer is full the producer doesn't wait but gets rejected
     * @param item Item that need's to be kept in the buffer
     *  @return boolean if the given element cool be put into the buffer.
     */
    bool tryPut(T item){
        bool ok;

        monitorIn();

        if(nbElements == bufferSize){
            ok = false;
        }else{
            elements[writePointer] = item;
            writePointer = (writePointer + 1) % bufferSize;
            nbElements ++;

            signal(notEmpty);
            ok = true;
        }

        monitorOut();

        return ok;
    }

    /**
     * @brief get taking the first element out of the buffer
     * @return the first element of the buffer.
     */
    T get (void){
        T item;

        monitorIn();

        if(nbElements == 0){
            wait(notEmpty);
        }

        item = elements[readPointer];
        readPointer = (readPointer + 1) % bufferSize;
        nbElements --;

        signal(notFull);
        monitorOut();

        return item;
    }
};

#endif // BUFFERN_H
