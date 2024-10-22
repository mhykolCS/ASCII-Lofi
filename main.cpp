#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

int main(int argc, char** argv) 
{
    cv::Mat frame, resized_frame;
    cv::VideoCapture capture("test.webm");

    int pixelBrightness = 0;

    //const std::string CHAR_POOL = "⣿⠿⠶⠒⠂⠀";
    //const std::string CHAR_POOL = "█▇▆▅▄▃▂▁ ";
    const std::string CHAR_POOL = "@%#*+=-. ";

    if(!capture.isOpened()){
        std::cerr << "Error! Unable to open video\n";
        return(-1);
    }
    capture.read(frame);
    int width = frame.cols / 20;
    int height = frame.rows / 20;

    cv::Vec3b bgrPixel;

    std::cout << "Start Grabbing\nPress any key to stop\n";
    for(;;){
        cv::resize(frame, resized_frame, cv::Size(width, height), cv::INTER_LINEAR);
        for(int row = 0; row < resized_frame.rows; row++){
            for(int col = 0; col < resized_frame.cols; col++){
                bgrPixel = resized_frame.at<cv::Vec3b>(row,col);
                pixelBrightness = (((int)bgrPixel[0] + (int)bgrPixel[1] + (int)bgrPixel[2]) / 3) / 34;
                std::cout << CHAR_POOL[pixelBrightness];
            }
            std::cout << std::endl;
        }

        // cv::imshow("Live", resized_frame);
        // if(cv::waitKey(5) >= 0) break;

        capture.read(frame);
        if(frame.empty()){
            std::cerr << "Error! Blank frame\n";
            break;
        }
        std::system("clear");
    }

    cv::destroyAllWindows();
    return 0; 
}
