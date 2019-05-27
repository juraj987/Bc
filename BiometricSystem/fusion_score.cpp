#define FUSION_H
#include <verification.h>
#include <QString>
#include <QtDebug>
#include <QMessageBox>
#include <verification.h>
#include <ui_verification.h>
class fusion{


public:static bool fusionScore(QString fingerprintWinner, float fingerprintScore,QString handwritingWinner,float handwritingScore)

    {

        QMessageBox message;
        float threshold = 0.03;
        qDebug()<<"FingerPrintWinner"<<fingerprintWinner<<"Skore fingerprint"<<fingerprintScore<<"handwrting winnner"<<handwritingWinner<<"handwriting score"<<handwritingScore;

        if(handwritingScore>fingerprintScore)
        {
              if(handwritingScore>threshold)
              {
                  message.setText("Verifikácia prebehla úspešne  získané skóre je "+ QString::number(handwritingScore) +" osoba číslo "+ handwritingWinner );
                  message.exec();
              }
              else{
                  message.setText("Verifikácia prebehla neúspešne  získané skóre je "+ QString::number(handwritingScore));
                  message.exec();
              }
        }
        if (handwritingScore<fingerprintScore)
        {
            if(fingerprintScore>threshold)
            {
                message.setText("Verifikácia prebehla úspešne  získané skóre je "+ QString::number(fingerprintScore) +" osoba číslo "+ fingerprintWinner );
                message.exec();
            }else{
                message.setText("Verifikácia prebehla neúspešne  získané skóre je "+ QString::number(fingerprintScore));
                message.exec();

            }

        }


    }



};
