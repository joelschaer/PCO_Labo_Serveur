#include "readerwritercache.h"
#include "option.h"
#include <QDateTime>
#include <QList>
#include <QDebug>

ReaderWriterCache::ReaderWriterCache(int invalidationDelaySec, int staleDelaySec):
    invalidationDelaySec(invalidationDelaySec), staleDelaySec(staleDelaySec)
{
    timer = new InvalidationTimer(this);
    timer->start(); // We start the testing of elements in cache
}

ReaderWriterCache::~ReaderWriterCache()
{
    timer->requestInterruption();
    timer->wait();
    delete timer;
}

void ReaderWriterCache::putResponse(Response &response) {
   lock.lockWriting();

   TimestampedResponse tr;
   tr.response = response;
   tr.timestamp = QDateTime::currentSecsSinceEpoch(); //Actual timestamp since 1970
   map.insert(response.getRequest().getFilePath(), tr);

   QTextStream(stdout) << "entry put in cache" << endl;

   lock.unlockWriting();
}

Option<Response> ReaderWriterCache::tryGetCachedResponse(Request &request) {
    lock.lockReading();
    if(map.contains(request.getFilePath())){
        TimestampedResponse tr = map.value(request.getFilePath());
        lock.unlockReading();

        QTextStream(stdout) << "entry found in cache" << endl;

        return Option<Response>::some(tr.response); //return a Option based on the response.
    }
    else{
        lock.unlockReading();
        return Option<Response>::none(); //return an empty Option
    }
}
