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
#include "threadpool.h"
#include <QList>

#define POOL_SIZE 4

class RequestDispatcherThread: public QThread
{
    Q_OBJECT

public:
    /**
     * @brief RequestDispatcherThread constuctor of the requestDispatcher
     * @param requests Pointer to the requests buffer
     * @param responses Pointer to the responses buffer
     * @param hasDebugLog
     */
    RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog): requests(requests), responses(responses), hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");

        pool = new ThreadPool(POOL_SIZE);
    }

protected:
    /**
     * @brief run is running in a thread,it is waiting for requests to be put in the buffer, creates the runnable objects and transmits them to the thread poolfor execution.
     */
    void run();

private:
    AbstractBuffer<Request>* requests;         // buffer pointer where the requests ready for handle are enterring
    AbstractBuffer<Response>* responses;       // buffre pointer where the handled requests should be put
    bool hasDebugLog;
    ThreadPool* pool;                          // thread pool which is goining to handle the thread taht will do the job.
};

#endif // REQUESTDISPATCHERTHREAD_H
