#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

const double PI = 3.141592;

void gaussian_filter(Mat src, Mat &dst, int kernel, double sigma) {
    
    double **filter = new double *[kernel];
    
    for(int i = 0;i<kernel;i++)
        filter[i] = new double[kernel];
    
    double temp = 0;
    for(int i = 0;i<kernel;i++) {
        for(int j = 0;j<kernel;j++) {
            int x = i - kernel / 2;
            int y = i - kernel / 2;
            filter[i][j] = (1 / (2 * PI * sigma * sigma)) * exp(-(x*x + y*y) / (2 * sigma * sigma));
            temp += filter[i][j];
        }
    }
    
    int ksize = kernel / 2;
    
    for(int i = 0;i<src.rows;i++) {
        for(int j = 0;j<src.cols;j++) {
            double sum = 0;
            for(int k = -ksize;k<=ksize;k++) {
                for(int l = -ksize;l<=ksize;l++) {
                    int nx = i + k;
                    int ny = j + l;
                    if(nx < 0 || nx >= src.rows || ny < 0 || ny >= src.cols) continue;
                    
                    sum += src.at<Vec3d>(nx, ny)[0]*filter[k + ksize][l + ksize];
                }
            }
            double gray = sum / temp;
            dst.at<Vec3d>(i, j) = {gray, gray, gray};
        }
    }
}

int main(int argc, const char *argv[]) {
    
    string imageName("/Users/jason/Desktop/lena512_gray.bmp");
    
    if(argc > 1) imageName = argv[1];
    
    Mat image;
    image = imread(imageName.c_str(), IMREAD_COLOR);
    
    if(image.empty()) {
        cout << "Could not open or find the image " << endl;
        return -1;
    }
    
    image.convertTo(image, CV_64F);
    image /= 255;
    
    int kernel_size = 11;
    double sigma = 5.0;
    Mat dst = Mat::zeros(image.size(), image.type());
    dst.convertTo(dst, CV_64F);
    gaussian_filter(image, dst, kernel_size, sigma);
    
    namedWindow("Window", WINDOW_AUTOSIZE);
    imshow("source image", image);
    imshow("result image", dst);
    waitKey();
    
    return 0;
}
