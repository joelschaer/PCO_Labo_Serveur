/*******************************
** ThreadPool
** threadpool.h/.cpp
**
** Yann Lederrey and Joel Schär
**
** Manages a pool of threads and attributes jobs to the one that are free.
**
**/
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QList>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QTextStream>

#include "runnable.h"
#include "buffern.h"

class ThreadPool
{
    class Thread;

private:
    int maxThreadCount;     // max possible threads
    int runningThreads;     // number of running threads
    int workingThreads;     // number of working threads
    int waitingThreads;     // number of threads waiting for a job
    int elementsToRun;      // number of elements that have to be runned
    QList<Thread*> threadList;  // list of the started threads pointers
    AbstractBuffer<Thread*>* pendingThreadBuffer;   // buffer of pending threads
    QWaitCondition cond;        // mesa monitor condition
    QMutex mutex;           // mutual exclusion variable


    class Thread: public QThread
    {
    private:
        Runnable* runnable;     // pointer to the runnable element
        QMutex mutex;           // mutual exclusion variable
        QWaitCondition cond;    // mesa monito condition
        ThreadPool* pool;       // threadpool pointer
        bool needRun;  // the job in runnable is a job that needs to be runned
        bool running;  // set at false when the thread needs to be stopped


    public:
        Thread(ThreadPool* pool): pool(pool), needRun(false), running(true){}

        ~Thread(){}

        /**
         * @brief runRunnable puts the new job in runnable, asks for its execution and wakes up the thread that the job gets done.
         * @param runnable
         */
        void runRunnable(Runnable* runnable);

        /**
         * @brief run,waits for a new job, runns the job in runnable and puts the thread in wait for the next job.
         */
        void run();

        /**
         * @brief stopThread called to interrupt threads execution. lets the job be finished.
         */
        void stopThread();
    };

public:
    ThreadPool(int maxThreadCount)
        : maxThreadCount(maxThreadCount), runningThreads(0), workingThreads(0), waitingThreads(0)
    {
        pendingThreadBuffer = new BufferN<Thread*>(maxThreadCount);
    }

    ~ThreadPool(){
        mutex.lock();

        // put all thread in terminating mod.
        for(Thread* thread: threadList){
            thread->stopThread();
        }

        // join all threads and delete the pointers
        while(runningThreads > 0){
            Thread* thread = threadList.first();
            threadList.pop_front();
            thread->wait();
            workingThreads--;
            runningThreads--;
            delete thread;
        }

        delete pendingThreadBuffer;

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

};

#endif // THREADPOOL_H
