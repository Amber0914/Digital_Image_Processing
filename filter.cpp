#include<cstdio>
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

cv::Mat mean_filter(cv::Mat src);
cv::Mat median_filter(cv::Mat src);

cv::Mat mean_filter(cv::Mat src){
    cv::Mat dst = src.clone();
    for(int i=0; i<src.rows; i++){
        for(int j=0; j<src.cols; j++){
            int total=0, cnt=1;
            if(i-1>=0 && j-1>=0){
                total += static_cast<int>(src.at<uchar>(i-1,j-1));
                cnt++;
            }
            if(i-1>=0){
                total += static_cast<int>(src.at<uchar>(i-1,j));
                cnt++;
            }
            if(i-1>=0 && j+1<src.rows){
                total += static_cast<int>(src.at<uchar>(i-1,j+1));
                cnt++;
            }
            if(j-1>=0){
                total += static_cast<int>(src.at<uchar>(i,j-1));
                cnt++;
            }
            total += static_cast<int>(src.at<uchar>(i,j));
            if(j+1<src.cols){
                total += static_cast<int>(src.at<uchar>(i,j+1));
                cnt++;
            }
            if(i+1<src.rows && j-1>=0){
                total += static_cast<int>(src.at<uchar>(i+1,j-1));
                cnt++;
            }
            if(i+1<src.rows){
                total += static_cast<int>(src.at<uchar>(i+1,j));
                cnt++;
            }
            if(i+1<src.rows && j+1<src.cols){
                total += static_cast<int>(src.at<uchar>(i+1,j+1));
                cnt++;
            }
            dst.at<uchar>(i, j)= total/cnt;
        }
    }
    return dst;
}

cv::Mat median_filter(cv::Mat src){
    cv::Mat dst = src.clone();
    for(int i=0; i<src.rows; i++){
        for(int j=0; j<src.cols; j++){
            int tmp[9]={0}, cnt=0;
            if(i-1>=0 && j-1>=0)
                tmp[cnt++] = static_cast<int>(src.at<uchar>(i-1,j-1));
            if(i-1>=0)
                tmp[cnt++] = static_cast<int>(src.at<uchar>(i-1,j));
            if(i-1>=0 && j+1<src.rows)
                tmp[cnt++] = static_cast<int>(src.at<uchar>(i-1,j+1));
            if(j-1>=0)
                tmp[cnt++] = static_cast<int>(src.at<uchar>(i,j-1));
            tmp[cnt++] = static_cast<int>(src.at<uchar>(i,j));
            if(j+1<src.cols)
                tmp[cnt++] = static_cast<int>(src.at<uchar>(i,j+1));
            if(i+1<src.rows && j-1>=0)
                tmp[cnt++] = static_cast<int>(src.at<uchar>(i+1,j-1));
            if(i+1<src.rows)
                tmp[cnt++] = static_cast<int>(src.at<uchar>(i+1,j));
            if(i+1<src.rows && j+1<src.cols)
                tmp[cnt++] = static_cast<int>(src.at<uchar>(i+1,j+1));
            // sort
            for(int m=0; m<cnt-1; m++){
                for(int n=m+1; n<cnt; n++){
                    if(tmp[m]>tmp[n]){
                        int exchange = tmp[m];
                        tmp[m] = tmp[n];
                        tmp[n] = exchange;
                    }
                }
            }
            int median = cnt/2;
            dst.at<uchar>(i, j)= tmp[median];//choose the median one
        }
    }
    return dst;
}

int main(int argc, char *argv[]){
    string in_file = argv[1];
    string mean_file = "mean_" + in_file;
    string median_file = "median_" + in_file;
    cv::Mat in_img = imread(in_file, CV_LOAD_IMAGE_GRAYSCALE);
   
    cv::Mat mean;
    mean = mean_filter(in_img);  // 3x3 filter
    imwrite(mean_file, mean);
    
    cv::Mat median;
    median = median_filter(in_img); // 3x3 filter
    imwrite(median_file, median);
    
    cout<<"process..ok"<<endl;
    return 0;
}
