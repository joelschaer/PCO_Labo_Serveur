#include "requestprocess.h"
#include "requesthandler.h"
#include "option.h"

void RequestProcessing::run(){

    Response response;
    Option<Response> cachedResponse = cache->tryGetCachedResponse(request);

    if(cachedResponse.hasValue()){
        response = cachedResponse.value();
    } else {
        // creating the request handler
        response = RequestHandler(request, hasDebugLog).handle();
        cache->putResponse(response);
    }

    // push the response to the response buffer
    responses->put(response);

    finished = true;
}
