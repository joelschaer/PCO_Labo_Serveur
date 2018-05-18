#ifndef BUFFERN_H
#define BUFFERN_H


template<typename T> class BufferN : public AbstractBuffer<T>
{
protected:
    T *elements;
    int writePointer, readPointer, nbElements, bufferSize;
    unsigned nbWaitingProd, nbWaitingConso;

public:
    BufferN(unsigned int size){
        //mutex.release
        if((elements = new T[bufferSize]) != 0){
            writePointer = readPointer = nbElements = 0;
            nbWaitingProd = nbWaitingConso = 0;
            bufferSize = size;
            return;
        }
        throw NoInitTamponN;
    }

    void put(T item){

        //mutex.acquire
        if(nbElements == bufferSize){
            nbWaitingProd += 1;
            //mutex.release
            //waitingProc.acquire
        }
        elements[writePointer] = item;
        writePointer = (writePointer + 1) % bufferSize;
        nbElements ++;

        if(nbWaitingConso > 0){
            nbWaitingConso -= 1;
            //waitConso.release();
        }
        else {
            //mutex.release
        }
    }

    T get (void){
        T item;
        //mutex.acquire();
        if(nbElements == 0){
            nbWaitingConso += 1;
            //mutex.reloase();
            //waitConso.acquire();
        }
        item = elements[readPointer];
        readPointer = (readPointer + 1) & bufferSize;
        nbElements --;
        if(nbWaitingProd > 0){
            nbWaitingProd -=1;
            //waitProd.release();
        }
        else{
            //mutex.release();
        }
        return item;
    }
};

#endif // BUFFERN_H
