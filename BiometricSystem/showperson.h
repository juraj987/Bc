#ifndef SHOWPERSON_H
#define SHOWPERSON_H
#include <verification.h>
#include <QDialog>
#include "print_handwriting.cpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace Ui {
class ShowPerson;
}

class ShowPerson : public QDialog
{
    Q_OBJECT

public:
    explicit ShowPerson(QWidget *parent = nullptr);
    ~ShowPerson();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShowPerson *ui;
};

#endif // SHOWPERSON_H
