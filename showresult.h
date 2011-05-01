#ifndef SHOWRESULT_H
#define SHOWRESULT_H

#include <QObject>

/**
  * Class that represent a show result in
  */
class ShowResult : public QObject {
    Q_OBJECT
public:
    explicit ShowResult(QObject *parent = 0);
    explicit ShowResult(QString title, QString url, QObject *parent = 0);
    ShowResult(ShowResult const& original);
    ShowResult& operator=(ShowResult const& original);
    QString getTitle() const;
    QString getURL() const;
    void setTitle(QString title);
    void setURL(QString url);
    QString toString() const;

private:
    QString _title;
    QString _url;

};

#endif // SHOWRESULT_H
