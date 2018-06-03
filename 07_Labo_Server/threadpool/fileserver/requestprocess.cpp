#include "requestprocess.h"
#include "requesthandler.h"

void RequestProcessing::run(){

    // creating the request handler
    RequestHandler handle = RequestHandler(request, hasDebugLog);

    // handling the request
    Response response = handle.handle();

    // push the response to the response buffer
    responses->put(response);

    finished = true;
}
