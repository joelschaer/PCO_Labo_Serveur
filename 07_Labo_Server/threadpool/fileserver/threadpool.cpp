#include "threadpool.h"

void ThreadPool::start(Runnable* runnable){
    QTextStream(stdout) << runnable->id() << "call start" << endl;

    mutex.lock();

    // create a new thread if maximum is not reached and all threads are busy
    if(runningThreads < maxThreadCount && workingThreads == runningThreads){
        Thread* newThread = new Thread(this);
        threadList.push_back(newThread);
        pendingThreadBuffer->put(newThread);
        newThread->start();
        runningThreads++;
        QTextStream(stdout) << "starting new thread" << runningThreads << endl;
    }

    // wait for a thread to be ready for a new job
    while(workingThreads == maxThreadCount){
        waitingThreads++;
        QTextStream(stdout) << runnable->id() << " waiting" << endl;
        cond.wait(&mutex);
        waitingThreads--;
    }

    workingThreads++;
    Thread* thread = pendingThreadBuffer->get();
    mutex.unlock();

    thread->runRunnable(runnable);
}

void ThreadPool::jobDone(Thread* thread){
    mutex.lock();

    if(waitingThreads > 0){
        QTextStream(stdout) << "wake one" << endl;
        cond.wakeOne();
    }
    workingThreads--;

    pendingThreadBuffer->put(thread);

    mutex.unlock();
}
