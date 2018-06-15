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

   TimestampedResponse resp;

   resp.response = response;
   resp.timestamp = QDateTime::currentSecsSinceEpoch();
   map.insert(response.getRequest(),resp);
   lock.unlockWriting();
}

Option<Response> ReaderWriterCache::tryGetCachedResponse(Request &request) {
    Option<Response> res = Option<Response>::none();
    lock.lockReading();
    res.some(map.find(request));
    lock.unlockReading();
    return res;
}
