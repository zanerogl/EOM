/************************************************************/
/************************************************************/
/*****      Author: Alfred                              *****/
/*****      email:  alfredtrj3.14@gmail.com             *****/
/*****      Blog:                                       *****/
/*****      Github:https://github.com/Expelliarmus-3    *****/
/************************************************************/
/************************************************************/

#ifndef COLOR_DETECTOR_H
#define COLOR_DETECTOR_H

#include <QString>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

class color_detector
{
public:
    color_detector(cv::Mat imgOriginal);

    QString color_result();

private:
    QString color;  //红色为0，非红为1
};

#endif // COLOR_DETECTOR_H
