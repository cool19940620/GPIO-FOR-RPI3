//g++ VideoCapture.cpp -o VideoCapture -I/usr/local/include/ -lraspicam -lraspicam_cv -lopencv_core -lopencv_highgui
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    //VideoCapture video(0);
    raspicam::RaspiCam_Cv video;
    if (!video.open())
    {
      cerr<<"Error opening the camera"<<endl;
      return -1;
    }
    Size videoSize = Size((int)video.get(CV_CAP_PROP_FRAME_WIDTH),(int)video.get(CV_CAP_PROP_FRAME_HEIGHT));
    namedWindow("video_demo", CV_WINDOW_AUTOSIZE);
    Mat videoFrame;

    while(1)
    {
        video.grab();   // get a new frame from camera
        video.retrieve ( videoFrame);
        if(videoFrame.empty())
        {
            break;
        }
        imshow("video_demo", videoFrame);
        waitKey(1);
    }
    video.release();
    return 0;
}