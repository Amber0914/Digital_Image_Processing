#include<cstdio>
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

cv::Mat threshold(cv::Mat src);
cv::Mat threshold(cv::Mat src, int value){
    cv::Mat dst = src;
    Mat_<uchar>::iterator it_out = dst.begin<uchar>();
    Mat_<uchar>::iterator it_ori = src.begin<uchar>();
    Mat_<uchar>::iterator it_end = src.end<uchar>();
    for(;it_ori<it_end; it_ori++){
        if(static_cast<int>(*it_ori)<value){
            *it_ori=0;
        }
        else *it_ori=255;
    }
    return dst;
}

int main(int argc, char *argv[]){
    string in_file = argv[1];
    int value = atoi(argv[2]);
    string thresold_file = "threshold_" + in_file;

    cv::Mat in_img = imread(in_file, CV_LOAD_IMAGE_GRAYSCALE);
    
    cv::Mat result;
    result = threshold(in_img, value);
    imwrite(thresold_file, result);

    cout<<"process..ok"<<endl;
    return 0;
}
