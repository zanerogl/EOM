#include "angle_detector.h"

angle_detector::angle_detector(cv::Mat imgmo, cv::Mat imgce)
{


    Mat img1,img2;
    //	img1 = imread("F:\\exercise\\opencv\\untitled1\\photo1\\mo3.png");     //模板
    //	img = imread("F:\\exercise\\opencv\\untitled1\\photo1\\ce33.png");   //待检测
//    imgmo = imread("F:\\exercise\\opencv\\untitled1\\photo1\\mo1.png");     //模板
//    imgce = imread("F:\\exercise\\opencv\\untitled1\\photo1\\ce11.png");   //待检测

    //    cvtColor(img1,img1,COLOR_BGR2GRAY);
    //    cvtColor(img2,img2,COLOR_BGR2GRAY);

    //    resize(img2,img2,Size(),2,2);
    int iLowH = 100;
    int iHighH = 124;
    int iLowS = 43;
    int iHighS = 255;
    int iLowV = 46;
    int iHighV = 255;
    //Mat matSrc=imread("F:\\exercise\\opencv\\untitled1\\photo1\\ce333.jpg",IMREAD_UNCHANGED);
    Mat moHsv,ceHsv,imgThresholded,imgThresholded1;
    cvtColor(imgmo,moHsv,COLOR_BGR2HSV);
    inRange(moHsv, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS,iHighV),imgThresholded1);
    cvtColor(imgce,ceHsv,COLOR_BGR2HSV);
    inRange(ceHsv, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS,iHighV),imgThresholded);

    //开闭运算
    Mat element1;
    element1 = getStructuringElement(MORPH_RECT, Size(10, 10));
    Mat dstImage1;
    morphologyEx(imgThresholded1, dstImage1, MORPH_OPEN, element1);
    morphologyEx(dstImage1, img1, MORPH_CLOSE, element1);

    Mat element;
    element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat dstImage;
    morphologyEx(imgThresholded, dstImage, MORPH_OPEN, element);
    morphologyEx(dstImage, img2, MORPH_CLOSE, element);
    resize(img2,img2,Size(),0.5,0.5);

    Mat element3;
    element = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(img1,img1, element3);
    erode(img1,img1, element3);
    dilate(img2,img2, element3);
    erode(img2,img2, element3);

    //    imshow("1",img1);
    //    imshow("2",img2);
    //    waitKey();


    //均值，高斯，中值
    //    blur(img,ans1,Size(3,3));
    //    GaussianBlur(img,ans2,Size(3,3),3.0,3.0);
    //    medianBlur(img,ans3,3);
    blur(img1,img1,Size(3,3));
    blur(img2,img2,Size(3,3));
    resize(img2,img2,Size(),2,2);

    if (!img1.data||!img2.data)
    {
        printf("false");
        angle = "361";     //暂时以361表示匹配错误
    }
    imshow("input box", img1);
    //imshow("input box_in_scene", img2);
    double t1 = getTickCount();
    //检测特征点(非线性)
    Ptr<AKAZE>detector = AKAZE::create();
    //Ptr<KAZE>detector = KAZE::create();//KAZE检测
    //存放描述子
    Mat descriptor_obj,descriptor_scene;
    //img1特征点检测并计算描述子
    vector<KeyPoint> keypoints_obj;
    detector->detectAndCompute(img1, Mat(), keypoints_obj, descriptor_obj);
    //img2特征点检测并计算描述子
    vector<KeyPoint> keypoints_scene;
    detector->detectAndCompute(img2, Mat(), keypoints_scene,descriptor_scene);
    //	double t2 = getTickCount();
    //	double t = (t2 - t1) * 1000 / getTickFrequency();//结果转化为毫秒
    //	printf("need times(ms):%f\n", t);

    //使用FLANN匹配器比较两个关键点的匹配度
    FlannBasedMatcher fbMatcher(new flann::LshIndexParams(20,10,2));//用LshIndexParams

    /*这里不能使用FlannBasedMatcher fbMatcher();这条语句，因为它不支持CV_8UC1类型，
            会报错，OpenCv暂时还没有解决这一问题。*/
    //也可以使用暴力匹配(BFMatcher bfmatches;)

    BFMatcher bfmatches;
    vector<DMatch>matches;
    fbMatcher.match(descriptor_obj, descriptor_scene, matches);

    //绘制匹配线
    Mat resultImg;
    drawMatches(img1, keypoints_obj, img2, keypoints_scene, matches, resultImg,
                Scalar::all(-1), Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    /*最后一个参数使用DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS就可以把检测到的特征点隐去，
            只留下匹配到的特征点。*/

    //	imshow("AKAZE Matches", resultImg);

    /*那么上面的操作所显示的结果匹配到的特征点很多，为了减少多余的特征点，下面进行
            如下操作*/

    vector<DMatch>goodmatches;//保存从众多匹配点中找出的最优点
    /*
            1、遍历整个描述子；
            2、从描述子中找出最优匹配点(距离最小)
            */
    double minDist = 1000;//初始化
    double maxDist = 0;
    for (int i = 0; i < descriptor_obj.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist > maxDist)
        {
            maxDist = dist;
        }
        if (dist < minDist)
        {
            minDist = dist;
        }

    }
    for (int i = 0; i < descriptor_obj.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < max(2 * minDist, 0.02))
        {
            goodmatches.push_back(matches[i]);
        }
    }


    if(goodmatches.size() < 4)      //特征点少于4
    {
        cout << "false" << endl;
//        return 0;
    }

    Mat goodmatchesImg;
    drawMatches(img1, keypoints_obj, img2, keypoints_scene, goodmatches, goodmatchesImg,
                Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    resize(goodmatchesImg,goodmatchesImg,Size(),0.5,0.5);
    imshow("goodmatchesImg", goodmatchesImg);


    //输出坐标
    int index1, index2;
    for (int i = 0; i < int(goodmatches.size()); i++)//将匹配的特征点坐标赋给point
    {
        index1 = goodmatches.at(i).queryIdx;
        index2 = goodmatches.at(i).trainIdx;
    }

    //用线匹配不直观，用透视矩阵来做
    //-------------------平面对象识别(将匹配到的内容替换为矩形)--------------------------
    //生成透视变换矩阵
    vector<Point2f> obj;
    vector<Point2f> objinscene;

    for (size_t i = 0; i < goodmatches.size(); i++)
    {
        obj.push_back(keypoints_obj[goodmatches[i].queryIdx].pt);
        objinscene.push_back(keypoints_scene[goodmatches[i].trainIdx].pt);
    }

    //输出任意两个匹配点坐标
    //	cout << keypoints_obj[goodmatches[1].queryIdx].pt << "\n"
    //	     << keypoints_obj[goodmatches[2].queryIdx].pt << "\n"
    //	     << keypoints_scene[goodmatches[1].trainIdx].pt << "\n"
    //         << keypoints_scene[goodmatches[2].trainIdx].pt << endl;

    int x1,x2,x3,x4,y1,y2,y3,y4,a1,a2,b1,b2,angle_val,q;
    x1=keypoints_obj[goodmatches[1].queryIdx].pt.x;   //模型匹配点1的x轴坐标
    y1=keypoints_obj[goodmatches[1].queryIdx].pt.y;
    x2=keypoints_obj[goodmatches[2].queryIdx].pt.x;
    y2=keypoints_obj[goodmatches[2].queryIdx].pt.y;
    x3=keypoints_scene[goodmatches[1].trainIdx].pt.x;   //待测图匹配点1的x轴坐标
    y3=keypoints_scene[goodmatches[1].trainIdx].pt.y;
    x4=keypoints_scene[goodmatches[2].trainIdx].pt.x;
    y4=keypoints_scene[goodmatches[2].trainIdx].pt.y;

    a1=x2-x1;
    a2=x4-x3;
    b1=y2-y1;
    b2=y4-y3;
    q = acos((a1*a2+b1*b2)/(sqrt(pow(a1,2)+pow(b1,2))*(sqrt(pow(a2,2)+pow(b2,2)))))*180/CV_PI;
    angle_val = q;
    //判断顺逆旋转，逆时针为正
    if (x4<x3)
    {
        angle_val = -q;
    }
    cout <<"The angle_val of rotation is :  "<<  angle_val <<endl;
    //结果
    angle = QString::number(angle_val);    //将int转为QString
    //    return angle;
}

QString angle_detector::angle_result()
{
    return angle;
}
