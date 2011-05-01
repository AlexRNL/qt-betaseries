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


//TODO process errors
void Betaseries::received (int id, bool error) {
    QString result = "",
            data(_api->readAll());

    if (processErrors(data))
        return;

    switch (_requestQueue[id]) {
        case SHOWS_SEARCH:
            foreach (const ShowResult currentShow, ShowResult::processSearch(data)) {
                result += currentShow.toString() + "\n";
            }
            result.chop(1);
            break;
        case STATUS:
            result = data;
            break;
        default:
            result = data;
            break;
    }
    _requestQueue.remove(id);

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
    _requestQueue.insert(_api->get(url.toString()), STATUS);
}

void Betaseries::searchShow(QString search) {
    QUrl url;
    url.setPath("/shows/search.xml");
    url.addQueryItem("key", KEY);
    url.addQueryItem("user-agent", USER_AGENT);
    url.addQueryItem("title", search);
    _requestQueue.insert(_api->get(url.toString()), SHOWS_SEARCH);
}

//Try to get this const
bool Betaseries::processErrors(QString data) {
    QString errors = "";
    QDomDocument doc;
    doc.setContent(data);
    QDomElement root = doc.documentElement();
    root = root.firstChildElement();

    while (!root.isNull()) {
        if (root.tagName() == "errors") {
            QDomElement error = root.firstChildElement();
            while (!error.isNull()) {
                errors += "Error(s):\n";
                QDomElement errorComponent = error.firstChildElement();
                while (!errorComponent.isNull()) {
                    if (errorComponent.tagName() == "code")
                        errors += "  Code: " + errorComponent.text()+"\n";
                    else if (errorComponent.tagName() == "content")
                        errors += "  Text: " + errorComponent.text()+"\n";
                    errorComponent = errorComponent.nextSiblingElement();
                }
                error = error.nextSiblingElement();
            }
            errors.chop(1);
        }
        root = root.nextSiblingElement();
    }

    if (!errors.isEmpty()) {
        emit wrongRequest(errors);
        return true;
    } else {
        return false;
    }
}
