#ifndef BETASERIES_H
#define BETASERIES_H

#include <QObject>
#include <QHttp>

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

private:
    ///Construtor
    explicit Betaseries(QObject *parent = 0);
    ///Methods

    //Attributes
    QHttp* _api;
    static Betaseries* _instance;

signals:
    void done (bool error, QString data);

public slots:
    void received (bool error);

};

#endif // BETASERIES_H
