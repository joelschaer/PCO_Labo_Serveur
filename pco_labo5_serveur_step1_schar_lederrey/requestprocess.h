/*******************************
** RequestProcessing
** requestprocessing.h/.cpp
**
** Yann Lederrey and Joel Schär
**
** Defines the working threads which will handle each request in a separate thread
**
**/
#ifndef REQUESTPROCESS_H
#define REQUESTPROCESS_H
#include <QThread>
#include "response.h"
#include "response.h"
#include "abstractbuffer.h"

class RequestProcessing: public QThread
{
private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;

public:
    RequestProcessing(Request request, AbstractBuffer<Response>* responses, bool hasDebugLog)
        : request(request), responses(responses), hasDebugLog(hasDebugLog) {}

protected:
    void run();
};

#endif // REQUESTPROCESS_H
