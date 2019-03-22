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

    vector<RotatedRect> minRect(contours.size());
    vector<RotatedRect> minEllipse(contours.size());

    for ( size_t i=0; i<contours.size(); i++) {

        minRect[i] = minAreaRect( contours[i] );
        if( contours[i].size() > 5) {
            minEllipse[i] = fitEllipse( contours[i] );
        }
    }

    for ( size_t i=0; i<contours.size(); i++ ) {

        drawContours( Image,contours,i,Scalar(255,255,0) );
        ellipse(Image, minEllipse[i], Scalar(255,255,0),2);
        Point2f rect_point[4];
        minRect[i].points(rect_point);
        for ( int j = 0; j < 4; j++ ) {
            line(Image,rect_point[j],rect_point[(j+1)%4], Scalar(255,255,0));
        }

    }
    imshow("show",Image);
}
