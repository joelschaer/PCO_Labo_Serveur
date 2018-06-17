#ifndef REQUEST_H
#define REQUEST_H
#include <QString>

class Request {
private:
    QString filePath;       // path that is requested
    QString clientId;       // cliend id who's requesting the file

public:
    Request() {}
    Request(QString filePath, QString clientId): filePath(filePath), clientId(clientId) {}

    /**
     * @brief getFilePath (getter)
     * @return path to the file
     */
    QString getFilePath() {
        return filePath;
    }

    /**
     * @brief getClientId (getter)
     * @return if of the client
     */
    QString getClientId() {
        return clientId;
    }
};

#endif // REQUEST_H
