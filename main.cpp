#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>  

int main(int argc, char** argv) 
{
    cv::Mat frame;
    cv::VideoCapture capture("test.webm");

    if(!capture.isOpened()){
        std::cerr << "Error! Unable to open video\n";
        return(-1);
    }

    int fps = capture.get(cv::CAP_PROP_FPS);
    int frame_count = (int) capture.get(cv::CAP_PROP_FRAME_COUNT);
    double duration = frame_count/fps;

    capture.read(frame);

    uint8_t* pixelPtr = (uint8_t*)frame.data;
    int cn = frame.channels();
    cv::Scalar_<uint8_t> bgrPixel;  

    std::cout << "Start Grabbing\nPress any key to stop\n";
    for(;;){
        capture.read(frame);
        if(frame.empty()){
            std::cerr << "Error! Blank frame\n";
            break;
        }

        for(int i = 0; i < frame.rows; i++){
            for(int j = 0; j < frame.cols; j++){
                bgrPixel.val[0] = pixelPtr[i * frame.cols * cn + j * cn + 0]; // B
                bgrPixel.val[1] = pixelPtr[i * frame.cols * cn + j * cn + 1]; // G
                bgrPixel.val[2] = pixelPtr[i * frame.cols * cn + j * cn + 2]; // R
            }
        }

        cv:imshow("Live", frame);
        if(cv::waitKey(5) >= 0) break;
    }

    return 0; 
}
