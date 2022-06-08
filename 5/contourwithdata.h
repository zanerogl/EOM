/************************************************************/
/************************************************************/
/*****      Author: WSM                                 *****/
/*****      email:  3226357731@qq.com                   *****/
/*****      Blog:                                       *****/
/*****      Github:                                     *****/
/************************************************************/
/************************************************************/

#ifndef CONTOURWITHDATA_H
#define CONTOURWITHDATA_H

//#include <QString>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

class ContourWithData {
public:

    // member variables ///////////////////////////////////////////////////////////////////////////
    std::vector<cv::Point> ptContour;           // contour
    cv::Rect boundingRect;                      // bounding rect for contour
    float fltArea;                              // area of contour

    bool checkIfContourIsValid() {                              // obviously in a production grade program
        if (fltArea < 100) return false;           // we would have a much more robust function for
        return true;                                            // identifying if a contour is valid !!
    }

    static bool sortByBoundingRectXPosition(const ContourWithData& cwdLeft, const ContourWithData& cwdRight) {      // this function allows us to sort
        return(cwdLeft.boundingRect.x < cwdRight.boundingRect.x);                                                   // the contours from left to right
    }

    /// 用旋转后的图片进行数字识别，返回识别到的数字
    char find_Number(const Mat &img);

};

/////////
class Angle_detector : public ContourWithData
{
public:

    string m_strAngle;  // 最终返回的角度
    string m_strNumber; // 最终返回的数字

    ContourWithData m_conWit;  // 占时不知道
////// 调用这个返回字符串结果
    string Angle_result();
    string Number_result();

////////// 构造函数，调用这个即可
    Angle_detector(Mat &Img,const vector<Mat> &modules);   // 构造函数
/// 入口函数
    void myFunc(const Mat &Img,const vector<Mat> &modules);

/// 开闭运算，先开后闭
    void open_close(Mat &inp,Mat &out,int sizeNum); // sizeNum 为 Size() 的参数

/// 查找角度总函数
    int find_all(const Mat &module,const Mat &image);

/// AKAZE 查找算法
/// 第一种
    int findSamePoint_AKAZE(const Mat &module,
                            vector<KeyPoint> &keyPoint_module,   // 模板特征点 容器
                            const Mat &image,
                            vector<KeyPoint> &keyPoint_image,    // 对比图特征点 容器
                            vector<DMatch> &goodmatches,    // 最佳匹配点容器
                            vector<DMatch> &matches_ransac   // 通过RANSAC 优化后的点，存入的是上面这两个容器的下标
    );
/// 第二种
    int findSamePoint_akaze(const Mat &module,
                            vector<KeyPoint> &keyPoint_module,   // 模板特征点 容器
                            const Mat &image,
                            vector<KeyPoint> &keyPoint_image,    // 对比图特征点 容器
                            vector<DMatch> &goodmatches,    // 最佳匹配点容器
                            vector<DMatch> &matches_ransac   // 通过RANSAC 优化后的点，存入的是上面这两个容器的下标
    );


/// RANSAC 优化特征匹配点结果
    void ransac(vector<DMatch> &goodMatches, // 最佳匹配点
                vector<KeyPoint> &KeyPoint_module,  // 模板图上找到的点
                vector<KeyPoint> &KeyPoint_image,  // 对比图上找到的点
                vector<DMatch> &matches_ransac   // 通过RANSAC 优化后的点，存入的是上面这两个容器的下标
    );
/// 计算最小汉明距离
    void match_min(vector<DMatch> &matches,vector<DMatch> &goodMatches,const int &length);

/// 计算最优匹配的点两两之间的角度(注意要使用不相同点)
/// 返回斜率加权后的角度值
    int sumAll_K(vector<DMatch> &dm,
                 vector<KeyPoint> &keyPoint_module,
                 vector<KeyPoint> &KeyPoint_image );

/// 计算他们的夹角
    int sumAngle(Point2f &ptMo_1,Point2f &ptMo_2,Point2f &ptIm_1, Point2f &ptIm_2); // Mo - Im


///// 查找轮廓函数，截取局部图  ，out
    int find_lunCuo(Mat &inp,Mat &out);

///// 用于数字识别的查找轮廓
    int find_lunCuo_FindNum(Mat &inp,Mat &out);
///// 图片旋转
    void imageXuanZhuan(Mat &inp, Mat &out, double rotangle);  // 后面为旋转角度
    bool find_yanSe(Mat &imgOriginal);   // 颜色识别，查轮廓时需要
    //QString angle_result();
};
#endif // CONTOURWITHDATA_H
