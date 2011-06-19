#include "requestshowsearch.h"
#include "showresult.h"

RequestShowSearch::RequestShowSearch(QString strSearch) :
        Request(), _path("/shows/search.xml"), _strSearch(strSearch) {
    _url.setPath(_path);
    _url.addQueryItem("title", _strSearch);
}

RequestShowSearch::~RequestShowSearch() {

}

QString RequestShowSearch::getPath() const {
    return _path;
}

QString RequestShowSearch::getStrSearch() const {
    return _strSearch;
}

void RequestShowSearch::setStrSearch(QString strSearch) {
    _strSearch = strSearch;
}

void* RequestShowSearch::processResult(QString data) {
    QString *result = new QString;
    foreach (const ShowResult currentShow, ShowResult::processSearch(data)) {
        *result += currentShow.toString() + "\n";
    }
    result->chop(1);
    return result;
}
