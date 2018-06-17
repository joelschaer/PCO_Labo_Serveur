#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"

class RequestHandler
{
private:
    Request request;    // Request to be handlet
    bool hasDebugLog;

public:
    RequestHandler(Request request, bool hasDebugLog): request(request), hasDebugLog(hasDebugLog) {}

    /**
     * @brief handles the request
     * @return the calculated response object
     */
    Response handle();
};

#endif // REQUESTHANDLER_H
