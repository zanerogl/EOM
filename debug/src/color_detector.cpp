#include "color_detector.h"

color_detector::color_detector(cv::Mat imgOriginal)
{
    cv::Mat imgBGR;
    cv::Mat imgThresholded; // 阈值图像
    imgBGR = imgOriginal.clone();

    inRange(imgBGR, cv::Scalar(0, 0, 128), cv::Scalar(127, 127, 255),imgThresholded); //红色阈值

    cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)); // 设置结构元素
    morphologyEx(imgThresholded, imgThresholded, cv::MORPH_OPEN, element); // 开运算
    morphologyEx(imgThresholded, imgThresholded, cv::MORPH_CLOSE, element); // 闭运算

    int rowNumber = 0;
    int colNumber = 0;
    int WhiteNum = 0;
    rowNumber = imgThresholded.rows;
    colNumber = imgThresholded.cols;
    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < colNumber; j++)
        {
            if (imgThresholded.ptr<uchar>(i)[j] > 0)
            {
                WhiteNum++;
            }
        }
    }
    if(WhiteNum > 50)
    {  // 找到白色
        cout << "red" << endl;  //白色像素值大于20，则输出red
        color = "0";          //返回000代表有红色
    }
    else
    {
        cout << "no red" << endl;
        color = "1";          //返回001代表非红色
    }
}

//返回颜色结果
QString color_detector::color_result()
{
    return color;
}
