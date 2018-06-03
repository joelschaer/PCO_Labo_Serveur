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
    int waitingThreads;
    int elementsToRun;
    QList<Thread*> threadList;
    AbstractBuffer<Thread*>* pendingThreadBuffer;
    QList<Thread*> stoppedThreads;
    QWaitCondition cond, done;
    QMutex mutex, bufferMutex;

public:
    ThreadPool(int maxThreadCount)
        : maxThreadCount(maxThreadCount), runningThreads(0), workingThreads(0), waitingThreads(0)
    {
        pendingThreadBuffer = new BufferN<Thread*>(maxThreadCount);
    }

    ~ThreadPool(){
        mutex.lock();

        for(Thread* thread: threadList){
            thread->stopThread();
        }

        while(runningThreads > 0){
            done.wait(&mutex);
        }

        while(!stoppedThreads.empty()){
            Thread* thread = stoppedThreads.first();
            delete thread;
            stoppedThreads.pop_front();
        }
        mutex.unlock();

    }

    /**
     * @brief start is called to put start the execution of a runnable job by a jobfree thread.
     * @param runnable
     */
    void start(Runnable* runnable);

    /**
     * @brief jobDone is called once the thread has finished runnning the job, thereby it gets put bask in the jobfree threads list.
     * @param thread
     */
    void jobDone(Thread* thread);

    /**
     * @brief stoppedThred il called by each thread when it stoppes running and is ready for delete.
     * @param thread
     */
    void stoppedThread(Thread* thread);

};

#endif // THREADPOOL_H
