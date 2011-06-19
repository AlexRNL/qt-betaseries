#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/favicon"));
    betaserie = Betaseries::getInstance(this);

    connect(betaserie, SIGNAL(done(bool,QStringList)), this, SLOT(updateForm(bool,QStringList)));
    connect(betaserie, SIGNAL(requestStarted(int)), this, SLOT(updateStatusBar(int)));
    connect(betaserie, SIGNAL(wrongRequest(QString)), this, SLOT(critical(QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on__sendRequest_clicked() {
    //betaserie->getStatus();
    if (ui->_searchInput->text().isEmpty())
        return;
    betaserie->searchShow(ui->_searchInput->text());
}

void MainWindow::updateForm (bool error, QStringList data) {
    ui->_result->clear();
    if (!error) {
        ui->_result->addItems(data);
    } else {
        ui->_result->addItem("Fail...");
    }
    ui->statusBar->showMessage("Done");
}

void MainWindow::updateStatusBar (int id) {
    ui->statusBar->showMessage("Sending request...");
}

void MainWindow::critical(QString errorText) {
    QMessageBox::critical(this, "Error !", errorText);
}
