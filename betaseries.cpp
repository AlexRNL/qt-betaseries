#include "betaseries.h"

#include <QUrl>
#include <QDomDocument>
#include "requeststatus.h"
#include "requestshowsearch.h"

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
    QString data(_api->readAll());
    QString* result;

    if (processErrors(data))
        return;

    result = static_cast<QString*> (_requestQueue[id]->processResult(data));

    delete _requestQueue[id];
    _requestQueue.remove(id);

    emit done(error, *result);
}

void Betaseries::sent (int id) {
    emit requestStarted(id);
}

void Betaseries::getStatus() {
    RequestStatus *req = new RequestStatus();
    _requestQueue.insert(_api->get(req->getRequest()), req);
}

void Betaseries::searchShow(QString search) {
    RequestShowSearch *req = new RequestShowSearch(search);
    _requestQueue.insert(_api->get(req->getRequest()), req);
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
