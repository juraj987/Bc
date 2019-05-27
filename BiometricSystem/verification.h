#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <matcher.h>
#include <extraction.h>
#include <preprocessing.h>
#include <QObject>
#include <QMultiMap>
#include <QString>
#include <opencv2/calib3d/calib3d.hpp>
#include <QDebug>
#include "matchhandwriting.cpp";
#include "fusion_score.cpp"


namespace Ui {
class Verification;
}

class Verification : public QDialog
{
    Q_OBJECT

public:
    explicit Verification(QWidget *parent = nullptr);
    ~Verification();
    int size_database;
private:
    float maxScoreFingerprint=0.422;
    Preprocessing database_pre;
    Preprocessing person_pre;
    Extraction  database_ext;
    Extraction  person_ext;
    Matcher match_person;
    int counter=1;
    float personScoreFingerPrint;
    QMap <QString,float> resultHandwriting;
    QString bestSubjectFingerprint;
    bool verificationFingerprint=false;
    int chechSizeDatabase();





    QMultiMap<QString, QVector<MINUTIA>> database;


private slots:
       void startProces();
       void on_choose_handwriting_clicked();
       void on_choose_fingerprint_clicked();
       void on_verifi_clicked();
       void preprocessingPersonDoneSlot(PREPROCESSING_RESULTS result);
       void preprocessingDatabaseDoneSlot(QMap<QString, PREPROCESSING_RESULTS> results);
       void extractionPersonDoneSlot(QVector<MINUTIA>results);
       void extractionDatabaseDoneSlot(QMap<QString,  QVector<MINUTIA>> results);
       void matcherDoneSlot(bool sucess, QString bestSubject , float score);
       void matcher_eror(int eror);
       void includeDatabase();
       void extractionDatabaseErorr(int erorr_code);



private:
    Ui::Verification *ui;
    QString  hand_writing_path="";
    QString fingerprint_path="";
};


#endif VERIFICATION_H
