#include "betaseries.h"

#include <QUrl>
#include <QDomDocument>

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
    QList<ShowResult> searchResult;
    QDomDocument doc;
    doc.setContent(_api->readAll());
    QDomElement root = doc.documentElement();
    root = root.firstChildElement();

    while (!root.isNull()) {
        if (root.tagName() == "shows") {
            QDomElement show = root.firstChildElement();
            while (!show.isNull()) {
                ShowResult currentResult;
                QDomElement showComponent = show.firstChildElement();
                while (!showComponent.isNull()) {
                    if (showComponent.tagName() == "url")
                        currentResult.setURL(showComponent.text());
                    else if (showComponent.tagName() == "title")
                        currentResult.setTitle(showComponent.text());
                    showComponent = showComponent.nextSiblingElement();
                }
                searchResult.append(currentResult);
                show = show.nextSiblingElement();
            }
        }
        root = root.nextSiblingElement();
    }

    QString result = "";
    foreach (const ShowResult currentShow, searchResult) {
        result += currentShow.toString() + "\n";
    }
    result.chop(1);

    emit done(error, result);
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

void Betaseries::searchShow(QString search) {
    QUrl url;
    url.setPath("/shows/search.xml");
    url.addQueryItem("key", KEY);
    url.addQueryItem("user-agent", USER_AGENT);
    url.addQueryItem("title", search);
    _api->get(url.toString());
}
