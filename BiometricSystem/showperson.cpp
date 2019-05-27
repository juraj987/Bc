#include "showperson.h"
#include "ui_showperson.h"
using namespace cv;
ShowPerson::ShowPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowPerson)
{
    ui->setupUi(this);
    QString text = "Osoba";

    for(int i=1;i<=80;i++)
    {

         ui->listWidget->addItem(text+ QString::number(i));
    }

}

ShowPerson::~ShowPerson()
{
    delete ui;

    ui->setupUi(this);

}

void ShowPerson::on_pushButton_clicked()
{
    int numberPeroson=ui->listWidget->currentRow();
    QString person= QString::number(numberPeroson+1);
    QString url_fingerprint = "/home/jk/Bakalarska_praca/databaza_BC/databaza_system/odtlacky/osoba"+person+"/"+person+"_1.tif";
    QString url_Handwriting= "/home/jk/Bakalarska_praca/databaza_BC/databaza_system/podpisy/osoba"+person+"/1.txt";

    Mat img2= cv::imread(url_fingerprint.toStdString(),cv::IMREAD_GRAYSCALE);
    cv::imshow("Podpis",print::printPicture(url_Handwriting));
    cv::imshow("Odtlacok",img2);


}
