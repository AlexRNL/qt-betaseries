#include "requeststatus.h"


RequestStatus::RequestStatus() :
    Request(), _path("/status.xml") {
    _url.setPath(_path);
}

RequestStatus::~RequestStatus() {

}

QString RequestStatus::getPath() const {
    return _path;
}

void* RequestStatus::processResult(QString data) {
    return new QString(data);
}
