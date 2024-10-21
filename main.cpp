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

    std::cout << "Start Grabbing\nPress any key to stop\n";
    for(;;){
        capture.read(frame);
        if(frame.empty()){
            std::cerr << "Error! Blank frame\n";
            break;
        }

        cv:imshow("Live", frame);
        if(cv::waitKey(5) >= 0) break;
    }

    return 0; 
}
