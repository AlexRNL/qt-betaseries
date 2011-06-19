#ifndef REQUESTSHOWSEARCH_H
#define REQUESTSHOWSEARCH_H

#include "request.h"

class RequestShowSearch : public Request {
    Q_OBJECT
public:
    RequestShowSearch(QString strSearch);
    virtual ~RequestShowSearch();
    virtual void* processResult(QString data);
    virtual QString getPath() const;
    QString getStrSearch() const;
    void setStrSearch(QString strSearch);

private:
    QString _path;
    QString _strSearch;
};

#endif // REQUESTSHOWSEARCH_H
