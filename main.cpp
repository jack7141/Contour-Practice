#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat src_gray;
Mat Image;
void thresh_callback(int,void*);
int main()
{
     Image = imread("C:/Users/ksrnd/Desktop/Light/google_Light.png");
     cvtColor(Image,src_gray,CV_RGB2GRAY);
     blur(src_gray,src_gray, Size(3,3));
     thresh_callback(0,0);
     waitKey();
}
void thresh_callback(int, void*)
{
    Mat src_canny;
    Canny( src_gray, src_canny, 100, 200);

    vector<vector<Point>> contours;
    findContours( src_canny, contours, CV_RETR_TREE, CHAIN_APPROX_SIMPLE );


    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> centers(contours.size());
    vector<float> radius(contours.size());

    for ( size_t i=0; i<contours.size(); i++) {
        approxPolyDP(contours[i],contours_poly[i],3,true);
        boundRect[i]=boundingRect(contours_poly[i]);
        minEnclosingCircle(contours_poly[i],centers[i],radius[i]);
    }

//    Mat drawing = Mat::zeros( src_canny.size(), CV_8UC3 );

    for ( size_t i=0; i<contours.size(); i++ ) {

        drawContours( Image,contours_poly,i,Scalar(255,255,0) );
        rectangle( Image, boundRect[i].tl(), boundRect[i].br(), Scalar(255,255,0), 2);
        circle( Image, centers[i], radius[i], Scalar(255,255,0), 2);
    }
    imshow("show",Image);
}
