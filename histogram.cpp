#include<cstdio>
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

cv::Mat HistEqualization(cv::Mat img);
cv::Mat GetHistoImg(cv::Mat &src);
int Round(double number);

cv::Mat HistEqualization(cv::Mat img){
    // occurrence number of a pixel of level i=0~256
    int px[256]={0};
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            int idx;
            idx = static_cast<int>(img.at<uchar>(i,j));
            px[idx]++;
        }
    }
    // calculate CDF corresponding to px
    int CDF[256]={0};
    int accumulation=0;
    for(int i=0; i<256; i++){
        accumulation += px[i];
        CDF[i] = accumulation;
    }
    // using general histogram equalization formula
    int normalize[256]={0};
    for(int i=0; i<256; i++){
        normalize[i] = ((CDF[i]-CDF[0])*255)/(img.rows*img.cols-CDF[0]);
        normalize[i] = Round(normalize[i]);
    }
    // get result
    cv::Mat output(img.rows, img.cols, CV_8U);
    Mat_<uchar>::iterator it_out = output.begin<uchar>();
    
    Mat_<uchar>::iterator it_ori = img.begin<uchar>();
    Mat_<uchar>::iterator itend_ori = img.end<uchar>();
    for(;it_ori!=itend_ori;it_ori++){
        int pixel_value = static_cast<int>(*it_ori);
        *it_out = normalize[pixel_value];
        it_out++;
    }
    return output;
}
int Round(double number)
{
    return (number > 0.0) ? (number + 0.5) : (number - 0.5);
}
cv::Mat GetHistImg(cv::Mat &src){
    // calculate histogram
    int histSize = 256;
    float range[] = {0, 255} ;
    const float* histRange = {range};
    Mat hist_img;
    calcHist(&src, 1, 0, Mat(), hist_img, 1, &histSize, &histRange);
    
    // draw
    cv::Mat dst(256, 256, CV_8UC1, Scalar(255));
    float max = 0;
    for(int i=0; i<histSize; i++){
        if( max < hist_img.at<float>(i))
            max = hist_img.at<float>(i);
    }
    float scale = (0.9*256)/max;
    for(int i=0; i<histSize; i++){
        int intensity = static_cast<int>(hist_img.at<float>(i)*scale);
        line(dst,Point(i,255),Point(i,255-intensity),Scalar(0));
    }
    return dst;
}

int main(int argc, char *argv[]){
    string in_file = argv[1];
    string out_file = argv[2];
    string in_hist_file = "hist_" + in_file;
    string out_hist_file = "hist_" + out_file;

    cv::Mat in_img = imread(in_file, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat in_hist_img;
    in_hist_img = GetHistImg(in_img);
    imwrite(in_hist_file, in_hist_img);
    
    cv::Mat out_img, out_hist_img;
    out_img = HistEqualization(in_img);
    imwrite(out_file, out_img);
    out_hist_img = GetHistImg(out_img);
    imwrite(out_hist_file, out_hist_img);
    
    cout<<"process..ok\n";
    cout << "Information\n";
    cout << "input file name: " << in_file <<endl;
    cout << "widthxheight: " << in_img.size << endl;
    cout << "output file name: " << out_file <<endl;
    
    return 0;
}
