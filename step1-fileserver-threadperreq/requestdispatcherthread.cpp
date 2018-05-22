#include "requestdispatcherthread.h"

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for request...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request to handle, start thread";

        // create thread for processing the request
        RequestProcessing* processing = new RequestProcessing(req, responses, hasDebugLog);
        // set connect thereby the thread will be deleted it has finished the job
        connect(processing, &RequestProcessing::finished, processing, &QObject::deleteLater);
        processing->start();
    }
}
