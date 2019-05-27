#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <showperson.h>
#include <QMainWindow>
#include<verification.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionVerifik_cia_osoby_triggered();

    void on_actionZobrazenie_osob_triggered();

    void on_actionKoniec_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
