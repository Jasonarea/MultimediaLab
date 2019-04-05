#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

Mat mean_filter(Mat& image_in, int kernel)
{
    assert(image_in.type() == CV_8UC1);
    assert(kernel % 2 == 1);
    assert(kernel >= 1);
    
    int padding = (kernel - 1) / 2;
    
    int mean = 0.0;
    int final = 0;
    int nlines, ncols;
    cv::Mat img_temp;
    
    nlines = image_in.size().height;
    ncols = image_in.size().width;
    copyMakeBorder(image_in, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    // allocate the output image as grayscale as the input is grayscale as well
    Mat image_out = Mat::zeros(nlines, ncols, CV_8UC1);
    
    // loop over whole image
    for (unsigned int j = padding; j<nlines + padding; j++){
        for (unsigned int z = padding; z<ncols + padding; z++){
            mean = 0.0;
            // loop over kernel area
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    // accumulate all pixel-values
                    mean += img_temp.at<uchar>(j + x, z + y);
                }
            }
            
            mean = mean / (kernel * kernel);
            final = round(mean);
            image_out.at<uchar>(j - padding, z - padding) = (uchar)final;
        }
    }
    
    return image_out;
}

int main(int argc, const char *argv[]) {
    
    string imageName("/Users/jason/Desktop/lena_gray.bmp");
    
    if(argc > 1)
        imageName = argv[1];
    
    Mat image;
    image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
    
    if(image.empty()) {
        cout << "Could not open or find the image " << endl;
        return -1;
    }
    
    int kernel_size = 15;
    Mat dst = Mat::zeros(image.size(), image.type());
    dst = mean_filter(image, kernel_size);
    
    imshow("Image", dst);
    waitKey();
    return 0;
}
