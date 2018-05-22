#include "requestdispatcherthread.h"
#include "request.h"
#include <QDebug>
#include "requestprocess.h"

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for request...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request to handle, start thread";
        // create thread for request handling
        RequestProcess* process = new RequestProcess(req, responses, hasDebugLog);
        process->start();
    }
}
