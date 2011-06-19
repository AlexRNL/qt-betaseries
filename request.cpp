#include "request.h"

Request::Request(QObject *parent) :
    QObject (parent) {
    _url.addQueryItem("key", KEY);
    _url.addQueryItem("user-agent", USER_AGENT);
}

Request::~Request() {

}

QString Request::getRequest() const {
    return _url.toString();
}
