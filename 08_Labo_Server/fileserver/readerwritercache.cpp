#include "readerwritercache.h"
#include "option.h"
#include <QDateTime>
#include <QList>
#include <QDebug>

ReaderWriterCache::ReaderWriterCache(int invalidationDelaySec, int staleDelaySec):
    invalidationDelaySec(invalidationDelaySec), staleDelaySec(staleDelaySec)
{}

ReaderWriterCache::~ReaderWriterCache()
{}

void ReaderWriterCache::putResponse(Response &response) {
   lock.lockWriting();

   TimestampedResponse tr;// = {response, QDateTime::currentSecsSinceEpoch()};
   tr.response = response;
   tr.timestamp = QDateTime::currentSecsSinceEpoch();
   map.insert(response.getRequest(), tr);
   lock.unlockWriting();
}

Option<Response> ReaderWriterCache::tryGetCachedResponse(Request &request) {
    lock.lockReading();
    if(map.contains(request.getFilePath())){
        TimestampedResponse tr = map.value(request.getFilePath());
        lock.unlockReading();

        return Option<Response>::some(tr.response);
    }
    else{
        lock.unlockReading();
        return Option<Response>::none();
    }
}
