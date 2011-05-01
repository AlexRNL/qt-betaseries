#include "showresult.h"

#include <QDomDocument>

ShowResult::ShowResult (QObject *parent) :
    QObject(parent) {

}

ShowResult::ShowResult (QString title, QString url, QObject *parent) :
    QObject(parent), _title(title), _url(url) {

}

ShowResult::ShowResult (ShowResult const& original) :
    _title(original.getTitle()), _url(original.getURL()) {

}

ShowResult& ShowResult::operator= (ShowResult const& original) {
    if (this != &original) {
        _title = original.getTitle();
        _url = original.getURL();
    }
    return *this;
}

QString ShowResult::getTitle () const {
    return _title;
}

QString ShowResult::getURL () const {
    return _url;
}

void ShowResult::setTitle (QString title) {
    this->_title = title;
}

void ShowResult::setURL (QString url) {
    this->_url = url;
}

QString ShowResult::toString () const {
    return getTitle() + " (" + getURL() + ")";
}

QList<ShowResult> ShowResult::processSearch(QString data) {
    QList<ShowResult> searchResult;
    QDomDocument doc;
    doc.setContent(data);
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
    return searchResult;
}
