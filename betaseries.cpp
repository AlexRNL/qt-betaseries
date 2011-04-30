#include "betaseries.h"

#include <QUrl>

Betaseries* Betaseries::_instance = NULL;

Betaseries::Betaseries(QObject *parent) :
    QObject(parent) {
    _api = new QHttp(DOMAIN, PORT_HTTP, this);

    connect(_api, SIGNAL(requestStarted(int)), this, SLOT(sent(int)));
    connect(_api, SIGNAL(requestFinished(int,bool)), this, SLOT(received(int, bool)));
}

Betaseries* Betaseries::getInstance(QObject *parent) {
    if (Betaseries::_instance == NULL)
        Betaseries::_instance = new Betaseries(parent);
    return Betaseries::_instance;
}


//TODO handle id!
void Betaseries::received (int id, bool error) {
    emit done(error, _api->readAll());
}

void Betaseries::sent (int id) {
    emit requestStarted(id);
}

void Betaseries::getStatus() {
    QUrl url;
    url.setPath("/status.xml");

    url.addQueryItem("key", KEY);
    url.addQueryItem("user-agent", USER_AGENT);
    _api->get(url.toString());
}

QList<ShowResult> Betaseries::searchShow(QString search) {
    QUrl url;
    url.setPath("/shows/search.xml");
    url.addQueryItem("key", KEY);
    url.addQueryItem("user-agent", USER_AGENT);
    url.addQueryItem("title", search);
    _api->get(url.toString());

    QList<ShowResult> searchResult;
    ShowResult tmp("Test", "test");

    searchResult.append(tmp);

    return searchResult;
}
