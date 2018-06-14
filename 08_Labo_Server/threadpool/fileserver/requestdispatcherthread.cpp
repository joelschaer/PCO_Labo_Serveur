#include "requestdispatcherthread.h"

void RequestDispatcherThread::run()
{
    int nbRequests = 0;
    while(true) {

        if (hasDebugLog)
            qDebug() << "Waiting for request...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request to handle, start thread";

        QString id = QString("%1 ").arg(nbRequests);
        nbRequests++;
        // create thread for processing the request
        RequestProcessing* processing = new RequestProcessing(req, responses, hasDebugLog,  id);

        pool->start(processing);

    }
}
