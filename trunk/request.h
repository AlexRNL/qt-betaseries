#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QUrl>

#define DOMAIN "api.betaseries.com"
#define PORT_HTTP 80
#define KEY "4b4b65a6071d"
#define USER_AGENT "QtBetaseries"


class Request : public QObject {
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);
    virtual ~Request();
    virtual void* processResult(QString data) = 0;
    virtual QString getPath() const = 0;
    QString getRequest() const;

protected:
    QUrl _url;

};

#endif // REQUEST_H
