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
    while(!QThread::currentThread()->isInterruptionRequested()){
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

            // if it should keep running indicateds that the thread is ready for a new job
            if(running = true){
                pool->jobDone(this);
            }
        }

        mutex.unlock();
    }
    pool->stoppedThread(this);
}

void Thread::stopThread(){
    mutex.lock();
    QTextStream(stdout) << runnable->id() << "stopped" << endl;
    running = false;
    this->requestInterruption();
    cond.wakeOne();
    mutex.unlock();
}
