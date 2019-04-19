#include <iostream>
#include <cmath>
#include <vector>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

void RGB2CMY(Mat &src, Mat &dst) {
    vector<Mat> rgbComponent, cmyComponent;
    for(int i = 0;i<3;i++) {
        cmyComponent.push_back(Mat(src.size(), CV_8UC1));
    }
    split(src, rgbComponent);
    
    for(int i = 0;i<src.rows;i++) {
        for(int j = 0;j<src.cols;j++) {
            float r = rgbComponent[2].at<uchar>(i, j);
            float g = rgbComponent[1].at<uchar>(i, j);
            float b = rgbComponent[0].at<uchar>(i, j);
            
            float c = 255 - r;
            float m = 255 - g;
            float y = 255 - b;
            
            cmyComponent[2].at<uchar>(i, j) = c;
            cmyComponent[1].at<uchar>(i, j) = m;
            cmyComponent[0].at<uchar>(i, j) = y;
        }
    }
    merge(cmyComponent, dst);
}

void RGB2HSV(Mat &src, Mat &dst) {
    cvtColor(src, dst, COLOR_BGR2HSV);
    
    vector<Mat> hsvComponent;
    split(dst, hsvComponent);
    
    for(int i = 0;i<src.rows;i++) {
        for(int j = 0;j<src.cols;j++) {
            float v = hsvComponent[2].at<uchar>(i, j);
            hsvComponent[2].at<uchar>(i, j) = 0.6 * v;
        }
    }
    merge(hsvComponent, dst);
}

void RGB2YCbCr(Mat &src, Mat &dst) {
    cvtColor(src, dst, COLOR_BGR2YCrCb);
    
    vector<Mat> yccComponent;
    split(dst, yccComponent);
    
    for(int i = 0;i<src.rows;i++) {
        for(int j = 0;j<src.cols;j++) {
            float y = yccComponent[0].at<uchar>(i, j);
            yccComponent[0].at<uchar>(i, j) = y * 0.5;
        }
    }
    merge(yccComponent, dst);
}

int main(int argc, const char *argv[]) {
    
    string imageName("/Users/jason/Desktop/lena_color.png");
    
    if(argc > 1) imageName = argv[1];
    
    Mat image, temp;
    image = imread(imageName.c_str(), IMREAD_COLOR);
    temp = image;
    if(image.empty()) {
        cout << "Could not open or find the image " << endl;
        return -1;
    }
    
    Mat dst = Mat::zeros(image.size(), image.type());
    imshow("source image", image);
    
    RGB2YCbCr(image, dst);
    cvtColor(dst, image, COLOR_YCrCb2BGR);
    imshow("YCbCr image", image);
    image = temp;
    
    dst = Mat::zeros(image.size(), image.type());
    RGB2CMY(image, dst);
    imshow("CMY image", dst);
    
    dst = Mat::zeros(image.size(), image.type());
    RGB2HSV(image, dst);
    cvtColor(dst, image, COLOR_HSV2BGR);
    imshow("HSV image", image);

    waitKey();
    
    return 0;
}
