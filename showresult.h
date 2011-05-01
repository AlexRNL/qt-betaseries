#ifndef SHOWRESULT_H
#define SHOWRESULT_H

#include <QObject>
#include <QList>

/**
  * Class that represent a show result in
  */
class ShowResult : public QObject {
    Q_OBJECT
public:
    ///Constructors
    explicit ShowResult(QObject *parent = 0);
    ShowResult(QString title, QString url, QObject *parent = 0);
    ShowResult(ShowResult const& original);
    ShowResult& operator=(ShowResult const& original);
    //Accessors
    QString getTitle() const;
    QString getURL() const;
    //Mutators
    void setTitle(QString title);
    void setURL(QString url);
    //Other methods
    QString toString() const;
    static QList<ShowResult> processSearch(QString data);


private:
    QString _title;
    QString _url;

};

#endif // SHOWRESULT_H
