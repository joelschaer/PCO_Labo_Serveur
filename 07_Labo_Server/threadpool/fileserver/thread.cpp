#include "thread.h"
#include "threadpool.h"

void Thread::runRunnable(Runnable* runnable){
    mutex.lock();
    this->runnable = runnable;
    needRun = true;
    cond.wakeOne();
    mutex.unlock();
}

void Thread::run(){
    while(true){
        mutex.lock();
        while(needRun == false && running == true){
            cond.wait(&mutex);
        }

        if(needRun == true){
            mutex.unlock();

            QTextStream(stdout) << runnable->id() << "run" << endl;

            runnable->run();
            QTextStream(stdout) << runnable->id() << "done" << endl;

            mutex.lock();

            needRun = false;
        }

        mutex.unlock();

        if(QThread::currentThread()->isInterruptionRequested()){
            QTextStream(stdout) << runnable->id() << "ended" << endl;
            pool->stoppedThread(this);
            return;
        }

        pool->jobDone(this);

    }
}

void Thread::stopThread(){
    mutex.lock();
    QTextStream(stdout) << runnable->id() << "stopped" << endl;
    running = false;
    this->requestInterruption();
    cond.wakeOne();
    mutex.unlock();
}
