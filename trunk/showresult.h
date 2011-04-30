#ifndef SHOWRESULT_H
#define SHOWRESULT_H

#include <QObject>

/**
  * Class that represent a show result in
  */
class ShowResult : public QObject {
    Q_OBJECT
public:
    explicit ShowResult(QString title, QString url, QObject *parent = 0);
    ShowResult(ShowResult const& original);
    ShowResult& operator=(ShowResult const& original);
    QString getTitle() const;
    QString getURL() const;

private:
    QString _title;
    QString _url;

};

#endif // SHOWRESULT_H
