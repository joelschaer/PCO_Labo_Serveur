#ifndef RESPONSE_H
#define RESPONSE_H

#include <QJsonObject>
#include <QJsonDocument>
#include "request.h"

class Response {
private:
    Request request;    // associated request
    QString response;   // generated response according to the request

public:
    Response(){}
    Response(Request request, QString response):
        request(request), response(response) {}

    /**
     * @brief toJson converts the response object to a json payload
     * @return json paylod with the request and the response
     */
    QString toJson() {
        QJsonObject obj;
        obj["request"] = request.getFilePath();
        obj["response"] = response;
        QJsonDocument doc(obj);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        return strJson;
    }

    /**
     * @brief getRequest (getter)
     * @return the request object
     */
    Request getRequest() {
        return request;
    }

    /**
     * @brief getResponse (getter)
     * @return the response string
     */
    QString getResponse() {
        return response;
    }
};
#endif // RESPONSE_H
