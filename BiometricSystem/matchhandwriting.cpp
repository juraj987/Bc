
#define MATCH_H
#include<QString>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/core.hpp>
#include  <verification.h>
#include "print_handwriting.cpp"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

class match{
public:static QMap<QString,float> matchHandwriting(QString pathHandwriting)
{
        Mat image1=print::printPicture(pathHandwriting);
        QMap <QString,int> bestMatches;
        QMap <QString,float> result;
       // Verification ver;

        for (int personDatabase=1;personDatabase<=80;personDatabase++) {
             cout << "osoba cislo  " <<personDatabase << endl;

            for (int handwriting_tmp=1;handwriting_tmp<=13;handwriting_tmp++) {
                QString person=QString::number(personDatabase);
                QString numberHandwriting=QString::number(handwriting_tmp);
                QString pathHandwriting2= "/home/jk/Bakalarska_praca/databaza_BC/databaza_system/podpisy/osoba"+person+"/"+numberHandwriting+".txt";
                Mat image2=print::printPicture(pathHandwriting2);

                Ptr<FeatureDetector> detector;
                Ptr<DescriptorExtractor> extractor;

                detector=SurfFeatureDetector::create();
                extractor=SiftDescriptorExtractor::create();

                vector<KeyPoint> keypoints1, keypoints2;
                detector->detect(image1, keypoints1);
                detector->detect(image2, keypoints2);
               
                

                //cout << "# keypoints of image1 :" << keypoints1.size() << endl;
               // cout << "# keypoints of image2 :" << keypoints2.size() << endl;

                Mat descriptors1,descriptors2;
                extractor->compute(image1,keypoints1,descriptors1);
                extractor->compute(image2,keypoints2,descriptors2);

            //    cout << "Descriptors size :" << descriptors1.cols << ":"<< descriptors1.rows << endl;

                vector< vector<DMatch> > matches12, matches21;
                Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
                matcher->knnMatch( descriptors1, descriptors2, matches12, 2 );
                matcher->knnMatch( descriptors2, descriptors1, matches21, 2 );
               // cout << "Matches1-2:" << matches12.size() << endl;
               // cout << "Matches2-1:" << matches21.size() << endl;

                std::vector<DMatch> good_matches1, good_matches2;

                for(int i=0; i < matches12.size(); i++){
                    const float ratio = 0.8;
                    if(matches12[i][0].distance < ratio * matches12[i][1].distance)
                        good_matches1.push_back(matches12[i][0]);
                }

                for(int i=0; i < matches21.size(); i++){
                    const float ratio = 0.8;
                    if(matches21[i][0].distance < ratio * matches21[i][1].distance)
                        good_matches2.push_back(matches21[i][0]);
                }

              //  cout << "Good matches1:" << good_matches1.size() << endl;
              //  cout << "Good matches2:" << good_matches2.size() << endl;

                // Symmetric Test
                std::vector<DMatch> better_matches;
                for(int i=0; i<good_matches1.size(); i++){
                    for(int j=0; j<good_matches2.size(); j++){
                        if(good_matches1[i].queryIdx == good_matches2[j].trainIdx && good_matches2[j].queryIdx == good_matches1[i].trainIdx){
                            better_matches.push_back(DMatch(good_matches1[i].queryIdx, good_matches1[i].trainIdx, good_matches1[i].distance));
                            break;
                        }
                    }
                }

 // qDebug()<<better_matches.size();
  bestMatches.insert(QString::number(personDatabase)+"_"+QString::number(handwriting_tmp),better_matches.size());


            }





    }
        QString key;
        QString bestSubject;
        float bestScore=0;

        foreach(key,bestMatches.keys())
          {
            if(bestMatches[key] >bestScore)
            {
                bestScore=bestMatches[key];
                bestSubject=key;
            }
        }
        QStringList BS=bestSubject.split("_");
        qDebug()<<bestSubject<<bestScore;
        result.insert("BestSubject",BS[0].toFloat());
        result.insert("BestScore",bestScore/95);
        return result ;





    }
};

