#ifndef REQUESTPROCESS_H
#define REQUESTPROCESS_H
#include <QThread>
#include "response.h"
#include "response.h"
#include "abstractbuffer.h"

class RequestProcess: public QThread
{
private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
public:
    RequestProcess(Request request, AbstractBuffer<Response>* responses, bool hasDebugLog): request(request), responses(responses), hasDebugLog(hasDebugLog) {
    }
protected:
    void run();
};

#endif // REQUESTPROCESS_H
