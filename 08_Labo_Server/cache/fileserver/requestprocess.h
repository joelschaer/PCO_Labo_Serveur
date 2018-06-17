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
#include "readerwritercache.h"

class RequestProcessing: public Runnable
{
private:
    Request request;        // request to be handelt
    AbstractBuffer<Response>* responses;    // response buffer pointer where to put the response in
    bool hasDebugLog;
    bool finished;          // keeps track if the handel is donne
    QString m_id;
    ReaderWriterCache *cache;

public:
    RequestProcessing(Request request, AbstractBuffer<Response>* responses, bool hasDebugLog, QString id, ReaderWriterCache* cache)
        : request(request), responses(responses), hasDebugLog(hasDebugLog), finished(false), m_id(id), cache(cache){
    }

protected:
    void run();

public:

    /**
     * @brief isFinished (getter)
     * @return isFinished value
     */
    bool isFinished(){
        return finished;
    }

    /**
     * @brief id (getter
     * @return value of id
     */
    QString id(){
        return m_id;
    }

};

#endif // REQUESTPROCESS_H
