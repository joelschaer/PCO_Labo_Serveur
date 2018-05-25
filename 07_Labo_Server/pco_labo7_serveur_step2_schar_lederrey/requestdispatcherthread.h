/*******************************
** RequetsDispatcherThread
** requestdispatcherthread.h/.cpp
**
** Yann Lederrey and Joel Schär
**
** Dispatches the incomming requests and starts each of them in a new request processing thread.
**
**/

#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "request.h"
#include "response.h"
#include "requestprocess.h"
#include <QList>

class RequestDispatcherThread: public QThread
{
    Q_OBJECT

public:
    RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog): requests(requests), responses(responses), hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");
    }

protected:
    void run();

private:
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    QList<RequestProcessing*> processthreads;
    bool hasDebugLog;
};

#endif // REQUESTDISPATCHERTHREAD_H
