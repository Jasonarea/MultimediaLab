#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

double alpha; /* Simple contrast control */
double beta; /* Simple brightness control */

int main(int argc, const char *argv[]) {
    
    string imageName("/Users/jason/Desktop/zzekkak2.jpeg");
    string secondImageName("/Users/jason/Desktop/nexters.jpg");
    
    if(argc > 1)
        imageName = argv[1];
    
    Mat image, image2;
    image = imread(imageName.c_str(), IMREAD_COLOR);
    image2 = imread(secondImageName.c_str(), IMREAD_COLOR);
    
    if(image.empty() || secondImageName.empty()) {
        cout << "Could not open or find the image " << endl;
        return -1;
    }
    
    Mat copy;
    resize(image2, copy, Size(image2.cols * 2, image2.rows * 2), 0, 0, INTER_LINEAR);
    image2 = copy;
    
    Mat dst = Mat::zeros(image.size(), image.type());
    
    cout << "Basic Linear Transforms " << '\n';
    cout << "------------------------" << '\n';
    cout << "* Enter the alpha value [0.0 - 1.0] : ";
    cin >> alpha;
    beta = 1 - alpha;
    
    for(int i = 0;i<image.rows;i++) {
        for(int j = 0;j<image.cols;j++){
            for(int k = 0;k<3;k++) {
                dst.at<Vec3b>(i, j)[k] =
                saturate_cast<uchar>(alpha * image.at<Vec3b>(i, j)[k] + beta * image2.at<Vec3b>(i, j)[k]);
            }
        }
    }
    
    namedWindow("Linear Window", 1);
    
    imshow("Linear Window", dst);
    
    
    waitKey();
    return 0;
}
