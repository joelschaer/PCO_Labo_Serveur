#include "requestprocess.h"
#include "requesthandler.h"

void RequestProcess::run(){
    RequestHandler handle = RequestHandler(request, hasDebugLog);
    Response response = handle.handle();
    responses->put(response);
}
