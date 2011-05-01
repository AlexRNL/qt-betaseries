#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHttp>
#include "betaseries.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Betaseries* betaserie;

private slots:
    void on__sendRequest_clicked();
    void updateForm (bool error, QString data);
    void updateStatusBar (int id);
    void critical (QString errorText);
};

#endif // MAINWINDOW_H
