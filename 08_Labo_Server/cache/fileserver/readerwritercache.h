/*******************************
** ReaderWriterCache
** ReaderWriterCache.h/.cpp
**
** Yann Lederrey and Joel Schär
**
** Cache base on writer/reader with max timer for his element. The shared resource is un map of QString and TimestampedResponse
** The QString correspond to the request
** The timestampResponse is an inner struct containing one response and the timestamp (when the request was put in the cache)
**
** The duration of an element in the cache is manage by the threaded inner class InvalidationTimer.
**
**/

#ifndef READERWRITERCACHE_H
#define READERWRITERCACHE_H
#include <QHash>
#include <QThread>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include "option.h"
#include "request.h"
#include "response.h"
#include "readerwriterlock.h"

class ReaderWriterCache
{

private:

    /* Struct to define the value type of the map
    ** Contain the response and a timestamp who correspond to the time since 1970 when the
    ** element was put in the map
    */
	struct TimestampedResponse {
            Response response;
            long timestamp;
	};

    /*  Internal class InvalidationTimer who test every <invalidationDelaySec> if the added request
     ** is older than staleDelaySec
     **
    */
	class InvalidationTimer: public QThread {
        friend ReaderWriterCache;

	private:
		ReaderWriterCache* cache;

	public:
        /**
         * @brief constructor with the cache
         * @param cache the cache where the element are put.
         */
		InvalidationTimer(ReaderWriterCache* cache): cache(cache) {}

	protected:
        /**
         * @brief test every <invalidationDelaySec> if the added request
         * is older than staleDelaySec
         */
		void run() {

            while(!QThread::currentThread()->isInterruptionRequested()){
                sleep(cache->invalidationDelaySec);

                long now = QDateTime::currentSecsSinceEpoch();

                QHashIterator<QString, TimestampedResponse> i(cache->map);
                cache->lock.lockWriting();
                while(i.hasNext()){
                    i.next();

                    if(now - i.value().timestamp > cache->staleDelaySec){
                        cache->map.remove(i.key());
                        QTextStream(stdout) << "entry deleted from cache" << endl;
                    }
                }
                cache->lock.unlockWriting();
            }

        }
	};

    QHash<QString, TimestampedResponse> map; //shared ressource
    int invalidationDelaySec; //time between test of validity
    int staleDelaySec; //time before the element is removed from the map (cache)
    InvalidationTimer* timer; // inner class to test the timers
    ReaderWriterLock lock; // lock to prevent concurrent acces to the resource

public:

    /**
     * @brief constructor of this cache.
     * @param invalidationDelaySec time between test of validity as seconds
     * @param staleDelaySec time before the element is removed from the map (cache) as seconds
     */
	ReaderWriterCache(int invalidationDelaySec, int staleDelaySec);
    ~ReaderWriterCache();

    /**
     * @brief try to extract a response in the cache.
     * @param request the resquest the request to search.
     * @return the response encapsulated in an Option class.
     */
	Option<Response> tryGetCachedResponse(Request& request);

    /**
     * @brief put a response in the cache
     * @param response a response of a previous request.
     */
	void putResponse(Response& response);
};

#endif // READERWRITERCACHE_H
