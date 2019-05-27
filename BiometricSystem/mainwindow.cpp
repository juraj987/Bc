#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionVerifik_cia_osoby_triggered()
{
    Verification window;
    window.exec();
    window.setModal(true);

}

void MainWindow::on_actionZobrazenie_osob_triggered()
{
    ShowPerson window;
    window.exec();
    window.setModal(true);
}

void MainWindow::on_actionKoniec_triggered()
{
    QCoreApplication::exit();
}
