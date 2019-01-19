#include<cstdio>
#include<iostream>
#include<opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;
void voidsobel_filter(cv::Mat src, string h, string v, string s, string mode);
void sobel_filter(cv::Mat src, string h, string v, string s, string mode){
    int Gx[9] = {0};
    int Gy[9] = {0};
    if(mode.compare("sobel")==0){
        int v[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1}; //vertical
        int h[9] = {1, 0, -1, 2, 0, -2, 1, 0 , -1};//horizontal
        for(int i=0; i<9; i++){
            Gx[i]=v[i];
            Gy[i]=h[i];
        }
    }
    else if(mode.compare("prewitt")==0){
        int v[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};//vertical
        int h[9] = {1, 1, 1, 0, 0, 0, -1, -1 , -1};//horizontal
        for(int i=0; i<9; i++){
            Gx[i]=v[i];
            Gy[i]=h[i];
        }
    }
    else if(mode.compare("robert")==0){
        int v[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};//vertical
        int h[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};//horizontal
        for(int i=0; i<9; i++){
            Gx[i]=v[i];
            Gy[i]=h[i];
        }
    }
    // convolution
    cv::Mat dst_hor = src.clone();
    cv::Mat dst_ver = src.clone();
    cv::Mat dst_both = src.clone();
    for(int i=0; i<src.rows; i++){
        for(int j=0; j<src.cols; j++){
            int x=0, y=0;
            if(i-1>=0 && j-1>=0){
                x += Gx[0]*static_cast<int>(src.at<uchar>(i-1,j-1));
                y += Gy[0]*static_cast<int>(src.at<uchar>(i-1,j-1));
            }
            if(i-1>=0){
                x += Gx[1]*static_cast<int>(src.at<uchar>(i-1,j));
                y += Gy[1]*static_cast<int>(src.at<uchar>(i-1,j));
            }
            if(i-1>0 && j+1<src.cols){
                x += Gx[2]*static_cast<int>(src.at<uchar>(i-1,j+1));
                y += Gy[2]*static_cast<int>(src.at<uchar>(i-1,j+1));
            }
            if(j-1>=0){
                x += Gx[3]*static_cast<int>(src.at<uchar>(i,j-1));
                y += Gy[3]*static_cast<int>(src.at<uchar>(i,j-1));
            }
            if(j+1<src.cols){
                x += Gx[5]*static_cast<int>(src.at<uchar>(i,j+1));
                y += Gy[5]*static_cast<int>(src.at<uchar>(i,j+1));
            }
            if(i+1<src.rows && j-1>=0){
                x += Gx[6]*static_cast<int>(src.at<uchar>(i+1,j-1));
                y += Gy[6]*static_cast<int>(src.at<uchar>(i+1,j-1));
            }
            if(i+1<src.rows){
                x += Gx[7]*static_cast<int>(src.at<uchar>(i+1,j));
                y += Gy[7]*static_cast<int>(src.at<uchar>(i+1,j));
            }
            if(i+1<src.rows && j+1<src.cols){
                x += Gx[8]*static_cast<int>(src.at<uchar>(i+1,j+1));
                y += Gy[8]*static_cast<int>(src.at<uchar>(i+1,j+1));
            }
            
            if(x<0) x= -x;
            dst_ver.at<uchar>(i, j)= x;
            if(y<0) y =-y;
            dst_hor.at<uchar>(i, j)= y;
            dst_both.at<uchar>(i, j) = sqrt(((x*x)+(y*y)));
        }
    }
    imwrite(h, dst_hor);
    imwrite(v, dst_ver);
    imwrite(s, dst_both);
}
int main(int argc, char*argv[]){
    string in_file = argv[1];
    string mode = argv[2];
    string vertical_file = "ver_" + in_file;
    string horizon_file = "hor_" + in_file;
    string sobel_file = mode + "_" + in_file;
    cv::Mat in_img = imread(in_file, CV_LOAD_IMAGE_GRAYSCALE);
    sobel_filter(in_img, vertical_file, horizon_file, sobel_file, mode);
    cout<<"process..ok"<<endl;
    return 0;
}
