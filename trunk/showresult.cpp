#include "showresult.h"

ShowResult::ShowResult(QString title, QString url, QObject *parent) :
        QObject(parent), _title(title), _url(url) {

}

ShowResult::ShowResult(ShowResult const& original) :
        _title(original.getTitle()), _url(original.getURL()) {

}

ShowResult& ShowResult::operator=(ShowResult const& original) {
    if (this != &original) {
            _title = original.getTitle();
            _url = original.getURL();
        }
    return *this;
}

QString ShowResult::getTitle() const {
    return _title;
}

QString ShowResult::getURL() const {
    return _url;
}
