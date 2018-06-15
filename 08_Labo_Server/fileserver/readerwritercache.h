#ifndef READERWRITERCACHE_H
#define READERWRITERCACHE_H
#include <QHash>
#include <QThread>
#include <QMutex>
#include <QDateTime>
#include "option.h"
#include "request.h"
#include "response.h"
#include "readerwriterlock.h"

class ReaderWriterCache
{
private:
	struct TimestampedResponse {
        Response response;
		long timestamp;
	};

	class InvalidationTimer: public QThread {
        friend ReaderWriterCache;

	private:
		ReaderWriterCache* cache;

	public:
		InvalidationTimer(ReaderWriterCache* cache): cache(cache) {}

	protected:
		void run() {

            while(true){
                sleep(cache->invalidationDelaySec);

                long now = QDateTime::currentSecsSinceEpoch();

                QHashIterator<QString, TimestampedResponse> i(cache->map);
                cache->lock.lockWriting();
                while(i.hasNext()){
                    i.next();

                    if(now - i.value().timestamp > cache->staleDelaySec){
                        cache->map.remove(i.key());
                    }
                }
                cache->lock.unlockWriting();
            }

        }
	};

	QHash<QString, TimestampedResponse> map;
	int invalidationDelaySec;
	int staleDelaySec;
	InvalidationTimer* timer;
	ReaderWriterLock lock;

public:
	ReaderWriterCache(int invalidationDelaySec, int staleDelaySec);
    ~ReaderWriterCache();

	Option<Response> tryGetCachedResponse(Request& request);
	void putResponse(Response& response);
};

#endif // READERWRITERCACHE_H
