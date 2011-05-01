#ifndef BETASERIES_H
#define BETASERIES_H

#include <QObject>
#include <QHttp>
#include <QMap>

#include "showresult.h"

#define DOMAIN "api.betaseries.com"
#define PORT_HTTP 80
#define KEY "4b4b65a6071d"
#define USER_AGENT "QtBetaseries"

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

private:
    ///Types
    enum RequestType {
        STATUS,
        SHOWS_SEARCH,
        SHOWS_DISPLAY,
        SHOWS_EPISODES,
        SHOWS_ADD,
        SHOWS_REMOVE,
    };
    ///Construtor
    explicit Betaseries(QObject *parent = 0);
    ///Methods
    bool processErrors(QString data);
    //Attributes
    QHttp* _api;
    static Betaseries* _instance;
    QMap<int, RequestType> _requestQueue;

signals:
    void done (bool error, QString data);
    void requestStarted (int id);
    void wrongRequest (QString errors);

public slots:
    void received (int id, bool error);
    void sent (int id);

};

#endif // BETASERIES_H
