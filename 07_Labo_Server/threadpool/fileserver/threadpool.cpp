#include "threadpool.h"

void ThreadPool::start(Runnable* runnable){
    QTextStream(stdout) << runnable->id() << "call start" << endl;

    mutex.lock();

    if(runningThreads < maxThreadCount && workingThreads == runningThreads){
        Thread* newThread = new Thread(this);
        threadList.push_back(newThread);
        pendingThreadBuffer->put(newThread);
        newThread->start();
        runningThreads++;
        QTextStream(stdout) << "starting new thread" << runningThreads << endl;
    }

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

void ThreadPool::stoppedThread(Thread* thread){
    mutex.lock();
    workingThreads--;
    runningThreads--;
    stoppedThreads.push_back(thread);
    done.wakeOne();
    mutex.unlock();
}
