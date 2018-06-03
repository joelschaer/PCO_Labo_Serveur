#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTextStream>
#include "runnable.h"

class ThreadPool;

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

#endif // THREAD_H
