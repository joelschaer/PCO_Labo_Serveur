#include "requestdispatcherthread.h"

void RequestDispatcherThread::run()
{
    while(true) {

        // check process thread list to delete the finished ones
        while(!processthreads.empty()){
            RequestProcessing* procthread = processthreads.first();
            if(procthread->isFinished()){
                processthreads.pop_front();
                delete procthread;
            }
            else{
                break;
            }
        }
        if (hasDebugLog)
            qDebug() << "Waiting for request...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request to handle, start thread";

        // create thread for processing the request
        RequestProcessing* processing = new RequestProcessing(req, responses, hasDebugLog);

        // keeps thread pointer in a list to check if they're finished and delete them at next request.
        processthreads.push_back(processing);
        processing->start();

    }
}
