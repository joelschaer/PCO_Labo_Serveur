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
#include "response.h"
#include "response.h"
#include "abstractbuffer.h"
#include "runnable.h"

class RequestProcessing: public Runnable
{
private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
    bool finished;
    QString m_id;

public:
    RequestProcessing(Request request, AbstractBuffer<Response>* responses, bool hasDebugLog, QString id)
        : request(request), responses(responses), hasDebugLog(hasDebugLog), finished(false), m_id(id) {
    }

protected:
    void run();

public:
    bool isFinished(){
        return finished;
    }

    QString id(){
        return m_id;
    }

};

#endif // REQUESTPROCESS_H
