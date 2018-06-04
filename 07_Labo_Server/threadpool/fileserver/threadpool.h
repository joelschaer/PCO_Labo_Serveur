/*******************************
** ThreadPool
** threadpool.h/.cpp
**
** Yann Lederrey and Joel Schär
**
** Manages the threads to make them execute jobs.
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

    class Thread: public QThread
    {
    private:
        Runnable* runnable;
        QMutex mutex;
        QWaitCondition cond;
        ThreadPool* pool;
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

        for(Thread* thread: threadList){
            thread->stopThread();
        }

        while(runningThreads > 0){
            done.wait(&mutex);
        }

        while(!stoppedThreads.empty()){
            Thread* thread = stoppedThreads.first();
            stoppedThreads.pop_front();
            if(thread->isFinished()){
                delete thread;
            }
            else{
                stoppedThreads.push_back(thread);
            }
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
