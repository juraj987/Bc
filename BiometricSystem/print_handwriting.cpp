#ifndef PRINT_H
#define PRINT_H
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QString>
#include <QFile>
#include <QDebug>
#include <limits.h>
using namespace cv;
using namespace std;

class print{

public:static Mat printPicture(QString url){

        QString pole,pole1;

        int array_x[1000000],array_y[1000000],countTextLine =0,i,max_y=0,max_x=0,miny=numeric_limits<int>::max(),minx=numeric_limits<int>::max();
        double tmp;

        QFile Filename(url);
    if(!Filename.open(QFile::ReadOnly) )
       {
       qDebug() <<"Problem ";
       }
  else{
        while(!Filename.atEnd())
            {
             pole=Filename.readLine();
             QStringList pieces = pole.split(" ");
             array_x[i]=pieces[0].toInt();
             array_y[i]=pieces[1].toInt();

            if(array_y[i]>max_y)
                {
                    max_y=array_y[i];
                }
           if(array_x[i]>max_x)
                {
                    max_x=array_x[i];
                }
           if(array_y[i]<miny)
               {
                   miny=array_y[i];
               }
          if(array_x[i]<minx)
               {
                   minx=array_x[i];
               }
      i++;
      }
}


Mat img(300,300,CV_8UC3);


img.setTo(255);

   for(int tmp=0;tmp<i-1;tmp++)
    {

        line(img,Point(array_x[tmp]-minx,array_y[tmp]-miny),Point(array_x[tmp+1]-minx,array_y[tmp+1]-miny),Scalar(0,0,0));

    }


    return img;



}

};
#endif
