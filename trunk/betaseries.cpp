#include "betaseries.h"

#include <QUrl>

Betaseries* Betaseries::_instance = NULL;

Betaseries::Betaseries(QObject *parent) :
    QObject(parent) {
    _api = new QHttp(DOMAIN, PORT_HTTP, this);

    connect(_api, SIGNAL(done(bool)), this, SLOT(received(bool)));
}

Betaseries* Betaseries::getInstance(QObject *parent) {
    if (Betaseries::_instance == NULL)
        Betaseries::_instance = new Betaseries(parent);
    return Betaseries::_instance;
}

void Betaseries::getStatus() {
    QUrl url;
    url.setPath("/status.xml");

    url.addQueryItem("key", KEY);
    url.addQueryItem("user-agent", USER_AGENT);
    _api->get(url.toString());
}

void Betaseries::received (bool error) {
    emit done(error, _api->readAll());
}
