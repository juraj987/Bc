#include "verification.h"
#include "ui_verification.h"
#include <QFileDialog>

Verification::Verification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verification)
{
    ui->setupUi(this);
    qRegisterMetaType<PREPROCESSING_RESULTS>("PREPROCESSING_RESULTS");
    connect(&person_pre,SIGNAL(preprocessingDoneSignal(PREPROCESSING_RESULTS)),this,SLOT(preprocessingPersonDoneSlot(PREPROCESSING_RESULTS)));

    qRegisterMetaType<PREPROCESSING_RESULTS>("QMap <QString,PREPROCESSING_RESULTS>");
    connect(&database_pre,SIGNAL(preprocessingSequenceDoneSignal(QMap <QString,PREPROCESSING_RESULTS>)),this,SLOT(preprocessingDatabaseDoneSlot(QMap<QString, PREPROCESSING_RESULTS>)));

    qRegisterMetaType<QVector<MINUTIA>>("QVector<MINUTIA>");
    connect(&person_ext,SIGNAL(extractionDoneSignal(QVector<MINUTIA>)),this,SLOT(extractionPersonDoneSlot(QVector<MINUTIA>)));

    qRegisterMetaType<QMap<QString,  QVector<MINUTIA>>>("QMap<QString,  QVector<MINUTIA>>");
    connect(&database_ext,SIGNAL(extractionSequenceDoneSignal(QMap<QString,  QVector<MINUTIA>>)),this,SLOT(extractionDatabaseDoneSlot(QMap<QString,  QVector<MINUTIA>>)));

    connect(&match_person,SIGNAL(identificationDoneSignal(bool, QString , float)),this,SLOT(matcherDoneSlot(bool, QString , float)));

    connect(&database_ext,SIGNAL(extractionErrorSignal(int)),this,SLOT(extractionDatabaseErorr(int)));
    connect(&match_person, SIGNAL(matcherErrorSignal(int )), this, SLOT(matcher_eror(int )));


}

Verification::~Verification()
{
    delete ui;

}

void Verification::on_choose_handwriting_clicked()
{
     hand_writing_path=QFileDialog::getOpenFileName(this,tr("Choose handwriting"),"/home/jk/Bakalarska_praca/databaza_BC","Text file (*.txt)" );
}

void Verification::on_choose_fingerprint_clicked()
{
     fingerprint_path=QFileDialog::getOpenFileName(this,tr("Choose fingerprint"),"/home/jk/Bakalarska_praca/databaza_BC","Image file (*.tif)" );
}

void Verification::on_verifi_clicked()
{
     if(fingerprint_path.isEmpty() || hand_writing_path.isEmpty())
     {
         QMessageBox::critical(this,"ERORR","Načítaj podpis a odtlačok !!");
     }else
     {

      resultHandwriting=match::matchHandwriting(hand_writing_path);

      startProces();


     }
}



void Verification::startProces()
{

    chechSizeDatabase();
    includeDatabase();


}


 void Verification::preprocessingPersonDoneSlot( PREPROCESSING_RESULTS result)
 {
  person_ext.loadInput(result);
  person_ext.start();
 }

 void Verification::preprocessingDatabaseDoneSlot(QMap<QString, PREPROCESSING_RESULTS> results)
 {

   database_ext.loadInput(results);
   database_ext.setFeatures(0,0,0);
   database_ext.start();
 }

 void Verification::extractionPersonDoneSlot(QVector<MINUTIA> result)
 {
   qDebug()<<"extractionDatabase";
   if(!result.isEmpty())
   {


   for(int k=0;k<result.size();k++)
    {
        result[k].quality=100;
    }
   match_person.setMatcher(suprema);
   match_person.identify(result,database);
   }else{
       QMessageBox::critical(this,"ERORR","Nenašiel sa žiaden kľúčový bod. Vyberte iný odtačok");

   }
 }
 void Verification::extractionDatabaseDoneSlot(QMap<QString,  QVector<MINUTIA>> results)
 {
        QString key;
         foreach(key,results.keys())
           {
             if(!results[key].isEmpty())
              {
                 for (int i=0;i<results[key].size();i++)
                 {
                     results[key][i].quality=100;
                 }
                  database.insert(QString::number(counter),results[key]);
              }

           }

             counter++;
             results.clear();
             key.clear();
             qInfo()<<"nacitanie databázy do QMultiMap ";
    if(counter<=size_database)
        {
        includeDatabase();

        }
    else {
        person_pre.loadInput(fingerprint_path);
        person_pre.start();

         }

 }

 void Verification::matcherDoneSlot(bool success, QString bestSubject, float score)
 {
   qDebug()<<"odtlacok score"<<score<<"bestSubject"<<bestSubject;


   fusion::fusionScore(bestSubject,score/maxScoreFingerprint,QString::number(resultHandwriting["BestSubject"]),resultHandwriting["BestScore"]);






 }


 int Verification::chechSizeDatabase()
 {
     int max_int = INT_MAX;
     for (int tmp=1;tmp<=max_int;tmp++)
     {
         QString osoba=QString::number(tmp);
         QString path="/home/jk/Bakalarska_praca/databaza_BC/databaza_system/odtlacky/osoba"+osoba+"/"+osoba+"_1.tif";
         QFile Fout(path);
          if(Fout.exists())
          {
              size_database=tmp-1;
          }
          else
          {
              break;
          }
     }
     return size_database;
 }


 void Verification::includeDatabase()
 {
     QVector<cv::Mat> loadImages;
     for (int tmp=1;tmp<=5;tmp++) {
             QString tmp_person=QString::number(counter);
             QString tmp_fingerprint=QString::number(tmp);
             QString path="/home/jk/Bakalarska_praca/databaza_BC/databaza_system/odtlacky/osoba"+tmp_person+"/"+tmp_person+"_"+tmp_fingerprint+".tif";
             cv::Mat image= cv::imread(path.toStdString(),cv::IMREAD_GRAYSCALE);
             loadImages.append(image);
             tmp_person.clear();
             tmp_fingerprint.clear();
             path.clear();

         }
    database_pre.loadInput(loadImages);
    loadImages.clear();
    database_pre.start();

 }

 void Verification::extractionDatabaseErorr(int erorr)
 {
     qDebug()<<"Extraction database erorr "<<erorr;
 }


 void Verification::matcher_eror(int erorr)
 {
     qDebug()<<"Matcher erorr"<<erorr;
 }
