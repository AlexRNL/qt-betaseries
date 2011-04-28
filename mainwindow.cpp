#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/favicon"));
    http = new QHttp(this);

    connect(http, SIGNAL(done(bool)), this, SLOT(updateForm(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on__sendRequest_clicked()
{
    QUrl url;
    url.setPath("/shows/episodes/detectiveconan.xml");

    url.addQueryItem("key", "4b4b65a6071d");
    url.addQueryItem("user-agent", "QtBetaseries");
    url.addQueryItem("seasons", "");
    //url.addQueryItem("episode", "4");

    http->setHost("api.betaseries.com");
    http->get(url.toString());
    ui->_result->setText("Sending...");
}

void MainWindow::updateForm (bool error) {
    if (!error) {
        ui->_result->setText(http->readAll());
    } else {
        ui->_result->setText("Fail...");
    }
}
