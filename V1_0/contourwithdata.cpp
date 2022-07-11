#include "contourwithdata.h"
#include <QDebug>
/*
void test01();
int main(){
    //test01();
    string ModuleName = "E:\\untitled90\\photo3\\";   // 模板图的绝对地址
    string ImageName  = "E:\\untitled90\\photo3\\";  // 对比图的绝对地址
    Mat Image;  // 对比图
    vector<Mat> modules;  // 模板容器
    for(int i = 0;i < 4;i++){
        Mat tempMod = imread(ModuleName + "photo" + (char)(i + 49) + ".jpg");  // 模板图
        if(tempMod.empty()){
            cout << "读取文件失败！！！" << endl;
            return 0;
        }
        modules.push_back(tempMod);
    }
    Image = imread(ImageName + "photo4-2.jpg");  // 2-4 有问题

    //Image = imread("E:\\untitled90\\blueModule\\blue02_1.jpg");  // 2-4 有问题

    if(Image.empty()){
        cout << "读取文件失败！！！" << endl;
        return 0;
    }
    ////// 创建一个 Angle_detector 类
    Angle_detector a(Image,modules);
    cout << "\t字符串结果为：" << endl;
    cout << "角度为：" << a.Angle_result() << endl;
    cout << "数字为：" << a.Number_result() << endl;

    return 0;
}

void test01(){
    Mat module,image;
    Mat mod1,mod2,mod3;

    module = imread("E:\\untitled90\\cun\\b.png");
    mod1 = imread("E:\\untitled90\\cun\\a.png");
    mod2 = imread("E:\\untitled90\\cun\\b.png");
    mod3 = imread("E:\\untitled90\\blueModule\\blue02_2.jpg");

    image  = imread("E:\\untitled90\\cun\\a.png");  // 对比图

    if(module.empty() || image.empty()){
        cout << "图片为空！！！" << endl;
        return;
    }
    if(mod1.empty() || mod2.empty() || mod3.empty()){
        cout << "图片为空！！！" << endl;
        return;
    }
    vector<Mat> Modules;
    Modules.push_back(module);
    Modules.push_back(mod1);
    Modules.push_back(mod2);
    Modules.push_back(mod3);
    Angle_detector a(image,Modules);

    cout << "\t字符串结果为：" << endl;
    cout << "角度为：" << a.Angle_result() << endl;
    cout << "数字为：" << a.Number_result() << endl;
    //waitKey();
}
*/
//////////////////   开始   /////////////////


Angle_detector::Angle_detector(Mat &Img,const vector<Mat> &modules) {
    if(Img.empty() || modules.empty()){
        cout << "error is Angle_detector!!!!" << endl;
        return ;
    }
    Angle_detector::myFunc(Img,modules);  // 函数入口
}
///// 入口函数
void Angle_detector::myFunc(const Mat &Img,const vector<Mat> &modules)
{
    if(Img.empty() || modules.empty()){
        cout << "error is myFunc!!!" << endl;
        return ;
    }
    cv::Mat module,image;  // 对比图和模板图

    string Result;  // 字符串结果
    ////// 输出 0 表示没有找到数字
    char TrueChar = '0';  // 接收每次识别正确的结果

    int angle = 1;   // 角度
    int EndAngle = 1;  // 最终角度
    int count = 0;  // 迭代变量

    ///该对象保存 角度，模板上对应的数字 以及 它的 ASC|| 码
    int temp_Angle[6][3] = {0}; // 第一维表示数字，第二维保存夹角，二维的第三个数表示正负号(正数用1负数用-1表示)
    // 记录这个模板图片上面数字与对比图的夹角

    // 保存它对应的字符
    char temp_Char[7];  // 保存模板图片上面对应的数字
    // 初始化
    for(int i = 0;i < 6;i++){
        temp_Char[i] = '0';   // 全部初始化为 0
    }

    for(count = 0; count < 4 && count < modules.size() ;count++) {
        cout << '\n' << count+1 << " : "<< endl;

        module = modules[count];  // 读取模板图
        image = Img.clone();  // 读取对比图

        cv::Mat dstImage;  // 用于数字识别
        dstImage = Img.clone(); /// 克隆


        /// 查找轮廓
        int ret_module = Angle_detector::find_lunCuo(module, module);
        if(ret_module < 0 || module.empty()){
            continue;
        }
        int ret_image  = Angle_detector::find_lunCuo(image, image);
        if(ret_image < 0 || image.empty()){
            continue;
        }
//        imshow("切割module",module);
//        imshow("切割image",image);
        //waitKey(1000);

        // 对比图和模板图分别进行高斯滤波
        cv::GaussianBlur(module, module, Size(3, 3), 1, 1);//高斯滤波，除噪点
        cv::GaussianBlur(image, image, Size(3, 3), 1, 1);//高斯滤波，除噪点

        // 对比图和模板图分别进行二值化处理
        cv::inRange(module, Scalar(0, 0, 128), Scalar(127, 127, 255),
                module); //红色阈值

        cv::inRange(image, Scalar(0, 0, 128), Scalar(127, 127, 255),
                image); //红色阈值


        /// 查找角度
        angle = Angle_detector::find_all(module, image);

        qDebug() << count+1 << "  角度为：" << angle << endl;
        if(angle > 450){
            continue;
        }
        cv::Mat endImage;

        bool one_1 = true;
        /// 用一正一负去进行数字识别
        for(int j = 0;j < 2;j++){
            /// 将得到的角度进行旋转
            Angle_detector::imageXuanZhuan(dstImage, endImage, angle);

            ///  用于数字识别的查找轮廓
            int ret_endImage = Angle_detector::find_lunCuo_FindNum(endImage, endImage);

//            imshow("旋转后",endImage);
//            waitKey(3000);
            if(ret_endImage < 0 || endImage.empty()){
                continue;
            }
            /// 开闭操作
            Angle_detector::open_close(endImage,endImage,3);

            /////// 进行数字识别
            char ret = Angle_detector::find_Number(endImage);

            if (ret != '0') {
                ///// 数字转字符串操作
                if(one_1){
                    TrueChar = ret; // 保存识别到的数字
                    one_1 = false;
                }

                temp_Angle[count + 1][j] = angle;  // 保存数字识别正确的角度
                if(angle >= 0){ // 正数
                    temp_Angle[count+1][2] = 1;   // 正数
                }
                else{
                    temp_Angle[count+1][2] = -1;
                }
                temp_Char[count+1] = TrueChar;   // 保存那个模板上面的数字
            }

            angle = -angle;   // 第二次循坏时是为 负数
        }

    }

   // cout << count+1 << " 数字结果: " << TrueChar << endl;
    cout << endl;
    for(int i = 0;i < 5;i++){
        cout << i+1 << " : "<< temp_Char[i] << endl;
    }

    //cout << "\n正确的数字为：" << TrueChar << endl;

    bool k = true;  // 标记是否找到数字
    for(int i = 0;i < 6;i++)  // 判断是否识别成功
    {  //
        if(TrueChar == temp_Char[i] && TrueChar == (char)(i + 48)){  // 识别到的数字和模板上的数字一样时
            qDebug() << "对应的顺序为 ：" << i+1 ;
            if(temp_Angle[i][2] == 1 ){  //正数
                EndAngle = temp_Angle[i][0];  // 正角度 // 逆时针
            }
            else{
                EndAngle = temp_Angle[i][1];  // 负角度 // 顺时针
            }
            k = false;
            break;
        }
    }
    if(k){  ///// 防止顺序识别失败
        for(int i = 0;i < 6;i++) {// 判断是否识别成功
            if (TrueChar == temp_Char[i]) {  // 识别到的数字和模板上的数字一样时
                qDebug() << "对应的顺序为 ：" << i + 1 ;
                if (temp_Angle[i][2] == 1) {  //正数
                    EndAngle = temp_Angle[i][0];  // 正角度 // 逆时针
                } else {
                    EndAngle = temp_Angle[i][1];  // 负角度 // 顺时针
                }
                k = false;
            }
        }
    }
    if(k){   // 找不到数字时直接判定为 垃圾
        qDebug()  << "数字识别结果失败" ;
        TrueChar = '0';
        EndAngle = 1;
    }

    ostringstream os;
    os << EndAngle;  // 数字转字符串操作

    // 将字符串叠加
    m_strAngle = os.str();  // 最终的字符串
    m_strNumber = TrueChar;
}

///// 查找角度函数
int Angle_detector::find_all(const Mat &module,const Mat &image)
{  // 分割查找
    if(module.empty() || image.empty()){
        cout << "image is empty!!!" << endl;
        cout << "errr is find_all !!!" << endl;
        return 500;
    }
    Mat tempModule,tempImage;
    int angle = 0;   // 最后需要计算的角度

    int count = 5;  // 循环次数
    int sizeNum = 1;  // sizeNum 为开闭操作的大小

    vector<int> allAngle; // 保存每次循环的角度

    while(count--) {
        // 赋值，保证不改变原图的情况
        tempModule = module;
        tempImage = image;
//        // 形态学操作
        Angle_detector::open_close(tempModule, tempModule,sizeNum % 33 );//
        Angle_detector::open_close(tempImage, tempImage, sizeNum % 33);//

        // 容器用来保存找到的点
        // A 为 AKAZE
        vector<KeyPoint> keyPoint_module_A;   // 模板特征点 容器
        vector<KeyPoint> keyPoint_image_A;    // 对比图特征点 容器
        vector<DMatch> goodMatches_A;    // 最佳匹配点容器
        vector<DMatch> matches_ransac_A;   // 最佳匹配点通过 RANSAC 优化后的存入的容器，存入的是keypoint_ 两个上面这两个容器的下标

        // a 为 akaze
        vector<KeyPoint> keyPoint_module_a;   // 模板特征点 容器
        vector<KeyPoint> keyPoint_image_a;    // 对比图特征点 容器
        vector<DMatch> goodMatches_a;    // 最佳匹配点容器
        vector<DMatch> matches_ransac_a;  // 最佳匹配点通过RANSAC 优化后的存入的容器，存入的是keypoint_ 两个上面这两个容器的下标

        // 查找特征点
        int ret_A = Angle_detector::findSamePoint_AKAZE(tempModule, keyPoint_module_A, tempImage, keyPoint_image_A, goodMatches_A,
                                            matches_ransac_A);
        int ret_a = Angle_detector::findSamePoint_akaze(tempModule, keyPoint_module_a, tempImage, keyPoint_image_a, goodMatches_a,
                                            matches_ransac_a);

        if(ret_A <= 0 && ret_a <= 0){
            continue;   // 两个都找不到点
        }
        // 用来保存他们的返回角度
        int numAngle[4] = {0};
        vector<int> quanAngle;  // 记录给定权值后的角度

        int m = 0;  // 记录总权值
        // 计算他们的角度

        // 找到了最佳匹配点的角度
        numAngle[0] = Angle_detector::sumAll_K(goodMatches_A, keyPoint_module_A, keyPoint_image_A); // 权值为 3
        numAngle[1] = Angle_detector::sumAll_K(goodMatches_a, keyPoint_module_a, keyPoint_image_a); // 权值为 1
        // 计算优化后匹配点的角度
        numAngle[2] = Angle_detector::sumAll_K(matches_ransac_A, keyPoint_module_A, keyPoint_image_A);// 权值为 4
        numAngle[3] = Angle_detector::sumAll_K(matches_ransac_a, keyPoint_module_a, keyPoint_image_a);// 权值为 2

        // 图片为空或者找不到最佳匹配点 或者 最佳匹配点的数量小于2 时不具有参考价值
        for (int i = 0; i < 4; i++) {
            if (numAngle[i] < 450 && numAngle[i] > -450) {

                numAngle[i] = abs(numAngle[i]);  // 存绝对值
                //// 这里不需要了
//                if(i == 1 && abs(numAngle[0] - numAngle[1]) > 20){
//                    sizeNum += 2;
//                    continue;  // 如果第二个算法找到的点的角度与第一个算法找到的角度差值很大，那么就不需要它
//                }
//
//                if(i == 2 && abs(numAngle[2] - numAngle[1]) > 10){
//                      int swap = numAngle[1] * 2;
//                      quanAngle.push_back(-swap);
//                      m -= 2;
//                     // 如果第二个算法找到的点的角度与第一个算法找到的角度差值很大，那么就不需要它
//                }
//                if(i == 3 && abs(numAngle[2]) < 360 && abs(numAngle[2] - numAngle[3]) > 10){
//                    sizeNum += 2;
//                    continue;  // 如果第二个算法找到的点的角度与第一个算法找到的角度差值很大，那么就不需要它
//                }


                //cout << "angle["<< i << "] = " << numAngle[i] << endl;

                if(i == 0){  // AKAZE goodMatches_A
                    quanAngle.push_back(numAngle[i] * 4);  // 权值为 3
                    m += 4;  // 记录权值
                }
                else if(i == 1){  // akaze goodMatches_a
                    quanAngle.push_back(numAngle[i] * 2); // 权值为 1
                    m += 2; // 记录权值
                }
                else if(i == 2){// AKAZE matches_ransac_A
                    quanAngle.push_back(numAngle[i] * 80); // 权值为 4
                    m += 80;  // 记录权值
                }
                else{  // akaze matches_ransac_a
                    quanAngle.push_back(numAngle[i] * 2); // 权值为 2
                    m += 2;  // 记录权值
                }
            }
            // 大于等于 |450| 度说明为无用点
        }
        if (!quanAngle.empty()) {
            int sum_num = 0;
            for(int n : quanAngle){
                sum_num += n;
            }
            angle = sum_num / m;  // 除以总权值
            allAngle.push_back(abs(angle));
        }
        sizeNum += 2;
        //cout << endl;
    }
    if(allAngle.empty()){
        return 0;  // 返回 0 度
    }
    int sum = 0;  // 记录总数
    for(int i = 0;i < allAngle.size();i++){
        int swap = abs(allAngle[i]);
        sum += swap;
    }
    angle = sum / allAngle.size();  // 平均值

    return angle;
}

///// AKAZE 查找算法 第一种，识别精度较高
int Angle_detector::findSamePoint_AKAZE(const Mat &module,
                        vector<KeyPoint> &keyPoint_module,   // 模板特征点 容器
                        const Mat &image,
                        vector<KeyPoint> &keyPoint_image,    // 对比图特征点 容器
                        vector<DMatch> &goodmatches,    // 最佳匹配点容器
                        vector<DMatch> &matches_ransac   // 通过RANSAC 优化后的点，存入的是上面这两个容器的下标
)
{
    if (module.empty() || image.empty()) {
        cout << "image is empty!!!" << endl;
        cout << "error is findSamePoint_AKAZE!!!" << endl;
        return -1;
    }
    Mat m_dstModule, i_dstImage;
    m_dstModule = module;
    i_dstImage = image;

    Ptr<AKAZE> akaze = AKAZE::create();
    Mat descriptors_module, descriptors_image;

    akaze->detectAndCompute(m_dstModule, Mat(), keyPoint_module, descriptors_module, false);
    akaze->detectAndCompute(i_dstImage, Mat(), keyPoint_image, descriptors_image, false);

    if(descriptors_module.empty() || descriptors_image.empty()){
        cout << "findSamePoint_AKAZE is no find Point!!!" << endl;
        return -1;
    }

    auto matcher = DescriptorMatcher::create(DescriptorMatcher::MatcherType::BRUTEFORCE);
    vector<DMatch> matches;
    matcher->match(descriptors_module, descriptors_image, matches);  // 特征点匹配

    if(matches.empty()){
        cout << " findSamePoint_AKAZE is no find Point!!!" << endl;
        return -1;
    }

    float maxdist = matches[0].distance;
    for (int i = 0; i < matches.size(); i++)
    {
        if (maxdist < matches[i].distance)
        {
            maxdist = matches[i].distance;
        }
    }

    float thresh = 0.5;  // 设置距离
    for (int j = 0; j < matches.size(); j++)
    {
        if (matches[j].distance < thresh * maxdist)
        {
            goodmatches.push_back(matches[j]);
        }
    }

    if (goodmatches.size() < 2){
        cout << "findSamePoint_AKAZE is no find Point!!!" << endl;
        return -1;
    }
//    Mat result;
//    // 画出匹配结果图
//    drawMatches(module, keyPoint_module, image, keyPoint_image, goodmatches, result,
//                Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

//    imshow("AKAZE最佳",result);
//    waitKey(1000);

    //  用 RANSAC 优化特征匹配点结果
    Angle_detector::ransac(goodmatches,keyPoint_module,keyPoint_image,matches_ransac);
//    if(!matches_ransac.empty()){
//        Mat result;
//        // 画出匹配结果图
//        drawMatches(module, keyPoint_module, image, keyPoint_image, matches_ransac, result,
//                    Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//
////        imshow("AKAZE优化",result);
////        waitKey(1000);
//    }

    return goodmatches.size(); // 返回最佳匹配点的数量(因为优化后的结果点不会大于最佳匹配点数量)
}

///// AKAZE 查找算法 第二种，识别精度较低
int Angle_detector::findSamePoint_akaze( const Mat &module,
                         vector<KeyPoint> &keyPoint_module,   // 模板特征点 容器
                         const Mat &image,
                         vector<KeyPoint> &keyPoint_image,    // 对比图特征点 容器
                         vector<DMatch> &goodmatches,    // 最佳匹配点容器
                         vector<DMatch> &matches_ransac   // 通过RANSAC 优化后的点，存入的是上面这两个容器的下标
)
{
    // 判断图片是否为空
    if (module.empty() || image.empty()){
        cout << "image is empty!!!" << endl;
        cout << "error is findSamePoint_akaze!!!" << endl;
        return -1;
    }

    Mat dstModule,dstImage;
    dstModule = module;
    dstImage  = image;

    //检测特征点(非线性)
    Ptr<AKAZE> detector = AKAZE::create();

    //存放描述子
    Mat descriptor_module,descriptor_image;

    //module特征点检测并计算描述子
    detector->detectAndCompute(dstModule, Mat(), keyPoint_module, descriptor_module);
    //image 特征点检测并计算描述子
    detector->detectAndCompute(dstImage, Mat(), keyPoint_image,descriptor_image);

    if(descriptor_module.empty() || descriptor_image.empty()){
        cout << "error is findSamePoint_akaze!!!" << endl;
        return -1;
    }

//
//      // 使用暴力特征点匹配
//    vector<DMatch> matches;  // 存放匹配结果的变量
//    BFMatcher matcher(NORM_HAMMING);  // 定义特征点匹配的类，使用汉明距离
//    matcher.match(descriptor_module, descriptor_image,matches); // 进行特征点匹配

    //使用FLANN匹配器比较两个关键点的匹配度
    vector<DMatch> matches;  // 存放匹配结果的变量
    FlannBasedMatcher fbMatcher(new flann::LshIndexParams(20,10,2));//用LshIndexParams
    fbMatcher.match(descriptor_module, descriptor_image, matches);

    if(matches.size() < 3){
        cout << "error is findSamePoint_akaze!!!" << endl;
        return -1;
    }
    // 用汉明距离查找距离最小点
    Angle_detector::match_min(matches,goodmatches,descriptor_module.rows);

    if(goodmatches.size() < 2){
        cout << "error is findSamePoint_akaze!!!" << endl;
        return -1;
    }

//    Mat result;
//    // 画出匹配结果图
//    drawMatches(module, keyPoint_module, image, keyPoint_image, goodmatches, result,
//                Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

//    imshow("akaze",result);
//    waitKey(1000);

    /// 优化检测结果
    Angle_detector::ransac(goodmatches,keyPoint_module,keyPoint_image,matches_ransac);

    return goodmatches.size(); // 返回最佳匹配点的数量(因为优化后的结果点不会大于最佳匹配点数量)
}

///// RANSAC 优化特征匹配点结果
void Angle_detector::ransac(vector<DMatch> &goodMatches, // 最佳匹配点
            vector<KeyPoint> &KeyPoint_module,  // 模板图上找到的点
            vector<KeyPoint> &KeyPoint_image,  // 对比图上找到的点
            vector<DMatch> &matches_ransac   // 通过RANSAC 优化后的点，存入的是上面这两个容器的下标
)
{
    if(goodMatches.size() < 3){
        return;
    }
    // 定义保存匹配点对坐标
    //vector<Point2f> modulePoints(goodMatches.size()),imagePoints(goodMatches.size()); // 注意此处的问题
    vector<Point2f> modulePoints,imagePoints;
    // 保存从关键点中提取到的匹配点对的坐标
    for(int i = 0;i < goodMatches.size();i++)
    {
        modulePoints.push_back(KeyPoint_module[goodMatches[i].queryIdx].pt);
        imagePoints.push_back(KeyPoint_image[goodMatches[i].trainIdx].pt);
    }

    if(modulePoints.size() < 4 ||  imagePoints.size() < 4 ){ // 点数太少了
        return ;
    }
    if(modulePoints.size() + modulePoints.size() < 9 ){  // 点数过少
        return;
    }
    // 匹配点对进行RANSAC过滤
    vector<int> inliersMask(modulePoints.size());
    cv::findHomography(modulePoints,imagePoints,RANSAC,5,inliersMask);//RANSAC
    // 函数参数课本 P 319 页
    // 手动保留 RANSAC 过滤后的匹配点对
    for(int i = 0;i < inliersMask.size();i++)
    {
        if(inliersMask[i])
        {
            matches_ransac.push_back(goodMatches[i]);
        }
    }
}
///// 计算最小汉明距离
void Angle_detector::match_min(vector<DMatch> &matches,vector<DMatch> &goodMatches,const int &length)
{  // length 为for循环的迭代次数
    if(matches.empty()){
        cout << "error is match_min"<< endl;
        return ;
    }
    double minDist = 1000;  // 最小距离
    double maxDist = 0; //初始化
    // 通过汉明距离筛选匹配结果

    for (int i = 0; i < length; i++)
    {
        double dist = matches[i].distance;  // 距离
        if (dist > maxDist)
            maxDist = dist;
        if (dist < minDist)
            minDist = dist;
    }

    // 将汉明距离较大的匹配点进行删除
    for (int i = 0; i < length; i++)
    {
        double dist = matches[i].distance; // 距离
        //比最小距离还小的就是最优匹配点
        if (dist < max(2 * minDist, 0.05))
        {
            goodMatches.push_back(matches[i]);   // 将那两个容器的下标分别存进 goodmatches 容器中
        }
    }
}


///// 计算最优匹配的点两两之间的角度(注意要使用不相同点)
///// 返回斜率加权后的角度值
int Angle_detector::sumAll_K(vector<DMatch> &dm,
             vector<KeyPoint> &keyPoint_module,
             vector<KeyPoint> &KeyPoint_image )
{  // 返回加权后的平均值
    if(dm.size() < 3){
        return 500;  // 返回一个大于450度的数
    }
    int angle = 1;
    int i,j;  // 迭代变量
    vector<int> allAngle;  // 保存角度

    // 用冒泡法计算两两之间形成的角度
    auto temp_end = dm.end();
    temp_end--;  // 防止容器越界
    i = 0;
    for(auto it_i = dm.begin(); i < 30 && it_i != temp_end ;it_i++,i++) // 最多计算 30 个点
    {
        j = i+1;
        // it_j == it_i + 1;
        for(auto it_j = it_i + 1 ; j < 30 && it_j != dm.end() ;it_j++,j++)
        {
            if(it_i->queryIdx != it_j->queryIdx && it_i->trainIdx != it_j->trainIdx)
            {  // 计算角度
                Point2f ptModule1 = keyPoint_module[it_i->queryIdx].pt;
                Point2f ptModule2 = keyPoint_module[it_j->queryIdx].pt;

                Point2f ptImg1 = KeyPoint_image[it_i->trainIdx].pt;
                Point2f ptImg2 = KeyPoint_image[it_j->trainIdx].pt;

                // 计算这四个点形成的角度
                int temp_angle = Angle_detector::sumAngle(ptModule1,ptModule2,ptImg1,ptImg2);
                if(temp_angle <= 360 && temp_angle >= -360)
                {
                    temp_angle = abs(temp_angle);
                    allAngle.push_back( temp_angle );  // 保存角度的绝对值
                }
            }
        }
    }

    if(allAngle.size() < 2)  // 防止识别不出来
        return 500;  // 返回  500 表示空

    //  加权求平均数
    // 排序，将角度相差为 5 的取平均值
    sort(allAngle.begin(),allAngle.end(),[](int a,int b)->bool{
        return (a > b ? true:false);
    } );

    int maxNum = 0;  // 赋初值，比较的是最大次数 count
    int sum;  // 记录总数
    int count; // 记录出现次数
    // 查找出现次数最多的角度
    for(i = 0;i < allAngle.size();i++) {
        sum = allAngle[i];
        count = 1;
        j = i + 1;
        while (j < allAngle.size() && allAngle[i] - allAngle[j] < 10) // 每个数的范围误差为 10 度
        {
            sum += allAngle[j];  // 记录那个角度的和，后面用来求那个角度的平均数
            count++;  // 记录出现次数
            j++;
        }
        if (count > maxNum) // 如果出现次数多于前面
        {
            angle = sum / count;  // 等于出现次数最多的那个角度的平均值
            maxNum = count;
        }
        i = j - 1;
    }
    return angle;
}
///// 计算他们的夹角且于 x 轴的夹角
int Angle_detector::sumAngle(Point2f &ptMo_1,Point2f &ptMo_2,Point2f &ptIm_1, Point2f &ptIm_2) // Mo - Im
{
    // 向量夹角公式 ：cos x = a-> * b-> / (|a->| * |b->|)
    int angle;
    const double Pi = 3.14;
    int t1,t2,t3,t4;

    t1 = ptMo_1.x - ptMo_2.x;  // 模板上面的点之间的向量
    t2 = ptMo_1.y - ptMo_2.y;

    t3 = ptIm_1.x - ptIm_2.x;  // 对比图上面的点的向量
    t4 = ptIm_1.y - ptIm_2.y;

    // cos x 的值(绝对值)
    double num1,num2;
    double temp = (sqrt(t1*t1 + t2*t2))*(sqrt(t3*t3 + t4*t4));
    if(temp < 0.0001 && temp > -0.0001){
        temp = 0.0001;   // 防止除数为 0
    }

    //向量夹角公式： cos x = a * b / (|a|*|b|) ;
    num1 = (t1*t3 + t2*t4) / temp; // 有正负号
    // 反余弦公式，返回的是弧度
    num2 = acos(num1);  // 向量 1 与 向量 2 的夹角
    // 此处 angle 为绝对值

    angle = (int)(num2 * (180.0 / Pi));  // 保存向量1 与 向量2 的夹角，不分正负号
    angle = abs(angle);  // 取绝对值
    return angle;
}

///// 开闭运算，先开后闭
void Angle_detector::open_close(Mat &inp,Mat &out,int sizeNum) // sizeNum 为 Size() 的参数
{
    if(inp.empty()){
        cout << "image is empty!!!" << endl;
        cout << "error is open_close!!!" << endl;
        return ;
    }
    //开运算
    Mat m_element,m_dstModule;
    m_element = getStructuringElement(MORPH_ELLIPSE, Size(sizeNum, sizeNum));
    morphologyEx(inp, m_dstModule, MORPH_OPEN, m_element);//

    //闭运算
    Mat m_element1;
    m_element1 = getStructuringElement(MORPH_ELLIPSE, Size(sizeNum, sizeNum));
    morphologyEx(m_dstModule, out, MORPH_CLOSE, m_element1);
}


/////  实现图片旋转任意角度
void Angle_detector::imageXuanZhuan(Mat &inp, Mat &out, double rotangle)  // 后面为旋转角度
{
    if(inp.empty()){
        cout << "image is empty!!!" << endl;
        cout << "error is iamgeXuanZhuan!!!" << endl;
        return ;
    }
    Mat inputimage = inp;
    Mat	outputimage = Mat::zeros(inputimage.size(), inputimage.type());//输出图像
    double input_clos = inputimage.cols;
    double input_rows = inputimage.rows;
    Point center = Point(input_clos / 2, input_rows / 2);//旋转中心
    double angle = rotangle;//旋转角度

    /***************************************计算缩放比例*****************************************************/
    double distance1 = sqrt(input_clos*input_clos+ input_rows* input_rows);//求取对角线长度

    double distance2 = min(input_clos, input_rows);

    double scale =  (distance2/ distance1);  //缩放因子

    /***************************************获取变换矩阵进行变换*****************************************************/
    Mat  rotMat(2, 3, CV_32FC1);//定义初始变换矩阵 用于存储变化矩阵
    rotMat = getRotationMatrix2D(center, angle, scale);
    warpAffine(inputimage, outputimage, rotMat, outputimage.size());//图像旋转变换
    if(outputimage.empty()){  // 无法旋转
        out = inp;
    }
    else{
        out = outputimage; ////
    }
    //resize(outputimage,outputimage,Size(),0.2,0.2);
}


///// 查找轮廓函数，截取局部图  ，out
int Angle_detector::find_lunCuo(Mat &inp,Mat &out)
{
    if(inp.empty()){
        cout << "image is empty !!!" << endl;
        cout << "error is find_luncuo!!!" << endl;
        out = Mat();  // 为空
        return -1;
    }
    //resize(inp,inp,Size(),0.5,0.5);
    Mat tempImg = inp;
    if(Angle_detector::find_yanSe(tempImg)){   // 不是红色
        cout << "image is no red!!! " << endl;
        out = Mat();  // 为空
        return -1;
    }

    /// 高斯降噪
    //GaussianBlur(inp, inp, Size(5, 5), 4,4);//高斯滤波，除噪点
    Angle_detector::open_close(inp,inp,5);

    Mat img;
    img = inp;  // 保存没有变化之前的原图
    /// 二值化
    inRange(inp, Scalar( 0,0,128), Scalar( 127,127,255),
            inp); //红色阈值

    threshold(inp,inp,100,255,THRESH_BINARY);
    /// 开闭操作
    Angle_detector::open_close(inp,inp,31); // 后面的数越大越好

    if(inp.empty()){
        cout << "image is empty !!!" << endl;
        cout << "error is find_luncuo!!!" << endl;
        out = Mat();  // 为空
        return -1;
    }
//    imshow("查轮廓二值化",inp);
    //waitKey(300);
    vector<vector<Point> > contours;//contours的类型，双重的vector

    vector<Vec4i> hierarchy;//Vec4i是指每一个vector元素中有四个int型数据。

    /// 查找轮廓
    findContours(inp.clone(), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

    if(contours.empty() || hierarchy.empty()){  ///// 杂图
        cout << "no find!!!" << endl;
        cout << "error is find_luncuo!!!" << endl;
        out = Mat();  // 为空
        return -1;
    }
    if(contours.size() > 10)
    {
        cout << "no find yuan!!!" << endl;
        out = Mat();  // 为空
        return -1;
    }

    ///////////// 计算圆心
    /// 计算矩
    vector<Moments> mu(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        mu[i] = moments(contours[i], false);
    }
    ///  计算矩中心:
    vector<Point2f> mc(contours.size());
    int r = 100;  // 半径
    int maxR[2] = {0};
    for (int i = 0; i < contours.size(); i++)
    {   // 圆心
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
        /// 计算面积然后求半径
        double Area = contourArea(contours[i]);   // 面积
        r = sqrt(Area / 3.1415);  //半径
        if(maxR[0] < r){
            maxR[0] = r;
            maxR[1] = i;
        }
    }

    if(mc.empty()){  //防止找不到圆心时
        mc[0].x = img.rows/3;
        mc[0].y = img.cols/3;
    }
    ///// 截图
    /// 用于进行数字角度查找，范围较小
    int temp = maxR[0] * 0.75;  /// 在这里调截图的大小
    ////////////


    //out = img(Rect(mc[0].x - 100,mc[0].y - 100, 200,200));
    if(mc[maxR[1]].x - temp < 0 || mc[maxR[1]].y - temp < 0 || mc[maxR[1]].x + temp >= img.cols || mc[maxR[1]].y + temp >= img.rows){
        out = Mat();
        cout <<__LINE__ << ":error is find_luncuo!!!" << endl;
        return -1;
    }
    out = img(Rect(mc[maxR[1]].x - temp,mc[maxR[1]].y - temp, 2 * temp,2 * temp)); // 用圆的半径去截图

    //resize(out,out,Size(),0.5,0.5);
    return 10;
}

///// 用于数字识别的查找轮廓
int Angle_detector::find_lunCuo_FindNum(Mat &inp,Mat &out)
{
    if(inp.empty()){
        cout << "image is empty !!!" << endl;
        cout << "error is find_luncuo_FindNum !!!" << endl;
        out = Mat();
        return -1;
    }

    if(inp.rows > 2000 && inp.cols > 2000){
        resize(inp,inp,Size(),0.5,0.5);
    }

    Mat tempImg = inp;
    if(tempImg.empty()){
        return -1;
    }
    if(Angle_detector::find_yanSe(tempImg)){   // 不是红色
        cout  << __LINE__  <<"image is no red!!! " << endl;
        return -1;
    }

    /// 高斯降噪
    //GaussianBlur(inp, inp, Size(3, 3), 1,1);//高斯滤波，除噪点
    Angle_detector::open_close(inp,inp,3);

    Mat img;
    img = inp;  // 保存没有变化之前的原图

    /// 二值化
    inRange(inp, Scalar( 0,0,128), Scalar( 127,127,255),
            inp); //红色阈值


    threshold(inp,inp,100,255,THRESH_BINARY);
    /// 开闭操作
    Angle_detector::open_close(inp,inp,33); // 后面的数越大越好

    vector<vector<Point> > contours;//contours的类型，双重的vector

    vector<Vec4i> hierarchy;//Vec4i是指每一个vector元素中有四个int型数据。

    /// 查找轮廓
    findContours(inp.clone(), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
    if(contours.empty() || hierarchy.empty()){   ///// 杂图
        cout << "no find!!!" << endl;
        cout << "error is find_luncuo_FindNum !!!" << endl;
        out = Mat();
        return -1;
    }
    if(contours.size() > 1){
        cout << "no find yuan!!!" << endl;
        out = Mat();
        return -1;
    }

    ///////////// 计算圆心
    /// 计算矩
    vector<Moments> mu(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        mu[i] = moments(contours[i], false);
    }
    ///  计算矩中心:
    vector<Point2f> mc(contours.size());
    int r = 100;  // 半径
    for (int i = 0; i < contours.size(); i++)
    {   // 圆心
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
        /// 计算面积然后求半径
        double Area = contourArea(contours[i]);
        r = sqrt(Area / 3.1415);  //半径
    }

    if(mc.empty()){  //防止找不到圆心时
        mc[0].x = inp.rows/3;
        mc[0].y = inp.cols/3;
    }
    if(r <= 20){
        r = 21;
    }
    int temp = r * 0.6;   //////// 在这里调截图的大小


    if(mc[0].x - temp < 0 || mc[0].y - temp < 0 || mc[0].x + temp >= img.cols || mc[0].y + temp >= img.rows){
        out = Mat();
        cout << "error is find_luncuo!!!" << endl;
        return -1;
    }
    ///// 截图
    /// 用于进行数字角度查找，范围较小
    //out = img(Rect(mc[0].x - 60,mc[0].y - 60, 120,120));
    out = img(Rect(mc[0].x - temp,mc[0].y - temp, 2*temp,2*temp));
    if(out.empty()){
        cout << "error is find_lunCuo_FindNum!!!" << endl;
        out = Mat();
        return -1;
     }
    return 10;
}

///// 调用这个返回字符串
string Angle_detector::Angle_result(){
    return m_strAngle;
}

string Angle_detector::Number_result() {
    return m_strNumber;
}

///// 用旋转后的图片进行数字识别，返回识别到的数字
char ContourWithData::find_Number(const Mat &img)
{
    if(img.empty()){
        cout << "image is empty!!!" << endl;
        cout << "error is find_Number!!!" << endl;
        return '0';
    }
///////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<ContourWithData> allContoursWithData;           // declare empty vectors,
    std::vector<ContourWithData> validContoursWithData;         // we will fill these shortly

    // read in training classifications ///////////////////////////////////////////////////

    cv::Mat matClassificationInts;      // we will read the classification numbers into this variable as though it is a vector

    cv::FileStorage fsClassifications("./classifications.xml", cv::FileStorage::READ);        // open the classifications file

    if (!fsClassifications.isOpened()) {    // 打开文件失败                                                  // if the file was not opened successfully
        std::cout << "error, unable to open training classifications file, exiting program\n\n";    // show error message
        return '0';                                                                                  // and exit program
    }

    fsClassifications["classifications"] >> matClassificationInts;      // read classifications section into Mat classifications variable
    fsClassifications.release();                                        // close the classifications file

    // read in training images ////////////////////////////////////////////////////////////

    cv::Mat matTrainingImagesAsFlattenedFloats;         // we will read multiple images into this single image variable as though it is a vector

    cv::FileStorage fsTrainingImages("./images.xml", cv::FileStorage::READ);          // open the training images file

    if (!fsTrainingImages.isOpened()) {     // 打开文件失败                                                // if the file was not opened successfully
        std::cout << "error, unable to open training images file, exiting program\n\n";         // show error message
        return '0';                                                                              // and exit program
    }

    fsTrainingImages["images"] >> matTrainingImagesAsFlattenedFloats;           // read images section into Mat training images variable
    fsTrainingImages.release();                                                 // close the traning images file

    // train //////////////////////////////////////////////////////////////////////////////

    cv::Ptr<cv::ml::KNearest>  kNearest(cv::ml::KNearest::create());            // instantiate the KNN object

    // finally we get to the call to train, note that both parameters have to be of type Mat (a single Mat)
    // even though in reality they are multiple images / numbers
    kNearest->train(matTrainingImagesAsFlattenedFloats, cv::ml::ROW_SAMPLE, matClassificationInts);

    // test ///////////////////////////////////////////////////////////////////////////////
    Mat imgBGR;
//        cv::Mat matTestingNumbers = cv::imread("E:\\untitled90\\cun\\new4.png");
    // 读需要识别的图片
    cv::Mat matTestingNumbers = img;
    resize(matTestingNumbers,matTestingNumbers,Size(150,150));

    if (matTestingNumbers.empty()) {                                // if unable to open image
        // show error message on command line
        return '0';                                                  // and exit program
    }

    cv::Mat matGrayscale;           //
    cv::Mat matBlurred;             // declare more image variables
    cv::Mat matThresh;              //
    cv::Mat matThreshCopy;          //

    cv::cvtColor(matTestingNumbers, matGrayscale, COLOR_BGR2GRAY);         // convert to grayscale

    // blur
    cv::GaussianBlur(matGrayscale,              // input image
                     matBlurred,                // output image
                     cv::Size(5, 5),            // smoothing window width and height in pixels
                     0);                        // sigma value, determines how much the image will be blurred, zero makes function choose the sigma value

    // filter image from grayscale to black and white
    cv::adaptiveThreshold(matBlurred,                           // input image
                          matThresh,                            // output image
                          255,                                  // make pixels that pass the threshold full white
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C,       // use gaussian rather than mean, seems to give better results
                          cv::THRESH_BINARY_INV,                // invert so foreground will be white, background will be black
                          11,                                   // size of a pixel neighborhood used to calculate threshold value
                          2);                                   // constant subtracted from the mean or weighted mean

    matThreshCopy = matThresh.clone();              // make a copy of the thresh image, this in necessary b/c findContours modifies the image

    std::vector<std::vector<cv::Point> > ptContours;        // declare a vector for the contours
    std::vector<cv::Vec4i> v4iHierarchy;                    // declare a vector for the hierarchy (we won't use this in this program but this may be helpful for reference)

    cv::findContours(matThreshCopy,             // input image, make sure to use a copy since the function will modify this image in the course of finding contours
                     ptContours,                             // output contours
                     v4iHierarchy,                           // output hierarchy
                     cv::RETR_EXTERNAL,                      // retrieve the outermost contours only
                     cv::CHAIN_APPROX_SIMPLE);               // compress horizontal, vertical, and diagonal segments and leave only their end points

    for (int i = 0; i < ptContours.size(); i++) {               // for each contour
        ContourWithData contourWithData;                                                    // instantiate a contour with data object
        contourWithData.ptContour = ptContours[i];                                          // assign contour to contour with data
        contourWithData.boundingRect = cv::boundingRect(contourWithData.ptContour);         // get the bounding rect
        contourWithData.fltArea = cv::contourArea(contourWithData.ptContour);               // calculate the contour area
        allContoursWithData.push_back(contourWithData);                                     // add contour with data object to list of all contours with data
    }

    for (int i = 0; i < allContoursWithData.size(); i++) {                      // for all contours
        if (allContoursWithData[i].checkIfContourIsValid()) {                   // check if valid
            validContoursWithData.push_back(allContoursWithData[i]);            // if so, append to valid contour list
        }
    }
    // sort contours from left to right
    std::sort(validContoursWithData.begin(), validContoursWithData.end(), ContourWithData::sortByBoundingRectXPosition);

    std::string strFinalString;         // declare final string, this will have the final number sequence by the end of the program

    for (int i = 0; i < validContoursWithData.size(); i++) {            // for each contour

        // draw a green rect around the current char
        cv::rectangle(matTestingNumbers,                            // draw rectangle on original image
                      validContoursWithData[i].boundingRect,        // rect to draw
                      cv::Scalar(0, 255, 0),                        // green
                      2);                                           // thickness

        cv::Mat matROI = matThresh(validContoursWithData[i].boundingRect);          // get ROI image of bounding rect

        cv::Mat matROIResized;
        cv::resize(matROI, matROIResized, cv::Size(20,30));     // resize image, this will be more consistent for recognition and storage

        cv::Mat matROIFloat;
        matROIResized.convertTo(matROIFloat, CV_32FC1);             // convert Mat to float, necessary for call to find_nearest

        cv::Mat matROIFlattenedFloat = matROIFloat.reshape(1, 1);

        cv::Mat matCurrentChar(0, 0, CV_32F);

        kNearest->findNearest(matROIFlattenedFloat, 1, matCurrentChar);     // finally we can call find_nearest !!!

        float fltCurrentChar = (float)matCurrentChar.at<float>(0, 0);

        strFinalString = strFinalString + char(int(fltCurrentChar));        // append current char to full string
    }

//    imshow("识别的图像",matTestingNumbers);
//    waitKey(1000);
    for(int i = 0;i < strFinalString.size();i++){
        if(strFinalString[i] == '1' || strFinalString[i] == '2' ||  strFinalString[i] == '3' ||  strFinalString[i] == '4')
        {
            qDebug() << "正确数字为：" << strFinalString[i];
//            cv::imshow("正确识别的图像", matTestingNumbers);
//            waitKey(2000);
            return strFinalString[i];
        }
    }
    // 找不到数字时默认返回
    qDebug() << "数字识别失败";
    return '0';
}
bool Angle_detector::find_yanSe(Mat &imgOriginal) // 颜色识别,识别红色
{
    if(imgOriginal.empty()){
        cout << "image is empty!!!" << endl;
        cout << "error is find_yanSe!!!" << endl;
        return true;
    }
    if(imgOriginal.rows > 800 && imgOriginal.cols > 800){
        resize(imgOriginal, imgOriginal, Size(500,500)); // 重新设置图片大小
    }
    Mat imgBGR;
    Mat imgThresholded; // 阈值图像
    imgBGR = imgOriginal.clone();

    inRange(imgBGR, Scalar(0, 0, 128), Scalar(127, 127, 255),
            imgBGR); //红色阈值
    threshold(imgBGR,imgBGR,100,255,THRESH_BINARY);

    imgThresholded = imgBGR;
    if(imgThresholded.empty()){
        cout << "image is empty!!" << endl;
        return true;
    }
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5)); // 设置结构元素
    morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element); // 开运算
    morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element); // 闭运算

//    imshow("颜色识别",imgThresholded);
//    waitKey(2000);

    int rowNumber = 0;
    int colNumber = 0;
    int WhiteNum = 0;
    rowNumber = imgThresholded.rows;
    colNumber = imgThresholded.cols;
    for (int i = 0; i < rowNumber; i++) {
        for (int j = 0; j < colNumber; j++) {
            if (imgThresholded.ptr<uchar>(i)[j] > 150) {
                WhiteNum++;
                if(WhiteNum > 600)
                {  // 找到白色
                    //cout << "red" << endl;
                    return false;  // 红色
                }
            }
        }
    }
    //cout << "Is no red" << endl;
    return true;  // 不是红色
}

//  //  //  //  //  //  end  //  //  //  //  //  //



