#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTextStream>
#include "runnable.h"
#include "abstractbuffer.h"
#include "hoaremonitor.h"
#include "threadpool.h"

class Thread: public QThread
{
private:
    Runnable* runnable;
    QMutex mutex;
    QWaitCondition cond;
    //AbstractBuffer<Thread*>* freeThreadBuffer;

    ThreadPool* pool;
public:
    Thread(ThreadPool* pool):pool(pool){}

    void runRunnable(Runnable* runnable){
        mutex.unlock();
        this->runnable = runnable;
        cond.wakeOne();
        mutex.unlock();
    }

    void run(){
        while(true){
            mutex.lock();
            cond.wait(&mutex);
            QTextStream(stdout) << runnable->id() << endl;
            mutex.unlock();

            runnable->run();

            //freeThreadBuffer->put(this);

        }
    }
};

#endif // THREAD_H
