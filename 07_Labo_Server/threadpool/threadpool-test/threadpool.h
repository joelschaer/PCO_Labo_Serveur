#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QList>
#include <QMutex>
#include <QWaitCondition>

#include "runnable.h"
#include "buffern.h"
#include "thread.h"

class ThreadPool
{
private:
    int maxThreadCount;
    int runningThreads;
    int workingThreads;
    QList<Thread*> threadList;
    AbstractBuffer<Thread*>* freeThreadBuffer;

    QWaitCondition cond;
    QMutex mutex;

public:
    ThreadPool(int maxThreadCount)
        : maxThreadCount(maxThreadCount), runningThreads(0), workingThreads(0)
    {
        freeThreadBuffer = new BufferN<Thread*>(maxThreadCount);

        for(int i = 0; i < maxThreadCount; i++){
            Thread* newThread = new Thread(this);
            threadList.push_back(newThread);
            freeThreadBuffer->put(newThread);
            newThread->start();
            runningThreads++;
        }
    }

    ~ThreadPool(){
        // todo stop thread and delete
        // delete buffer
    }

    /**
     * @brief start
     * @param runnable
     */
    void start(Runnable* runnable){
        mutex.lock();
        while(workingThreads == maxThreadCount){
            cond.wait(&mutex);
        }
        workingThreads++;
        Thread* thread = freeThreadBuffer->get();
        thread->runRunnable(runnable);

        mutex.unlock();
    }

};

#endif // THREADPOOL_H
