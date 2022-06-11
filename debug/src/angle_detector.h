#ifndef ANGLE_DETECTOR_H
#define ANGLE_DETECTOR_H

#include <QString>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class angle_detector
{
public:
    angle_detector(cv::Mat imgmo, cv::Mat imgce);

    QString angle_result();

private:
    QString angle;

};

#endif // ANGLE_DETECTOR_H
