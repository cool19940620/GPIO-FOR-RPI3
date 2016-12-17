#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <raspicam/raspicam.h>

using namespace cv;        //cv::
using namespace std;       //std::
//
int main(int argc, char **argv)
{
    Mat image = imread("test.png", CV_LOAD_IMAGE_COLOR);
    namedWindow("test", CV_WINDOW_NORMAL);
    imshow("test", image);
    waitKey(0);
    return 0;
}
