#ifndef BETASERIES_H
#define BETASERIES_H

#include <QObject>
#include <QHttp>
#include <QMap>

#include "showresult.h"
#include "request.h"

/**
  * Class which handles the requests to the API of Betaseries.
  *
  * This is a singleton
  */
class Betaseries : public QObject {
    Q_OBJECT
public:
    static Betaseries* getInstance(QObject *parent = 0);
    void getStatus ();
    void searchShow(QString search);
    void displayShow(QString url);

private:
    ///Construtor
    explicit Betaseries(QObject *parent = 0);
    ///Methods
    bool processErrors(QString data);
    //Attributes
    QHttp* _api;
    static Betaseries* _instance;
    QMap<int, Request*> _requestQueue;

signals:
    void done (bool error, QString data);
    void requestStarted (int id);
    void wrongRequest (QString errors);

public slots:
    void received (int id, bool error);
    void sent (int id);

};

#endif // BETASERIES_H
