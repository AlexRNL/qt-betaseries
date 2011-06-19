#ifndef REQUESTSTATUS_H
#define REQUESTSTATUS_H

#include "request.h"

class RequestStatus : public Request {
    Q_OBJECT
public:
    RequestStatus();
    virtual ~RequestStatus();
    virtual void* processResult(QString data);
    virtual QString getPath() const;

private:
    QString _path;
};

#endif // REQUESTSTATUS_H
