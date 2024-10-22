#include "opencv2/opencv.hpp"
#include <curses.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>


int main(int argc, char** argv) 
{
    // initscr();
    // cbreak();
    // noecho();

    cv::Mat frame, resized_frame;
    cv::VideoCapture capture("test.webm");

    int pixelBrightness = 0;
    const std::string CHAR_POOL = " .-=+*#%@";

    if(!capture.isOpened()){
        std::cerr << "Error! Unable to open video\n";
        return(-1);
    }
    capture.read(frame);
    int width = frame.cols / 20;
    int height = frame.rows / 35;
    std::string height_string = std::to_string(height);
    std::string resetSequence = "\033[<" + height_string + ">A";

    cv::Vec3b bgrPixel;

    std::cout << "Start Grabbing\nPress any key to stop\n";
    for(;;){
        cv::resize(frame, resized_frame, cv::Size(width, height), 0, 0, cv::INTER_LINEAR_EXACT);
        for(int row = 0; row < resized_frame.rows; row++){
            for(int col = 0; col < resized_frame.cols; col++){
                bgrPixel = resized_frame.at<cv::Vec3b>(row,col);
                pixelBrightness = (((int)bgrPixel[0] + (int)bgrPixel[1] + (int)bgrPixel[2]) / 3) / 28;
                std::cout << CHAR_POOL[pixelBrightness];
            }
            std::cout << std::endl;
        }

        std::cout << resetSequence;

        // cv::imshow("Live", resized_frame);
        if(cv::waitKey(5) >= 0) break;

        capture.read(frame);
        if(frame.empty()){
            std::cerr << "Error! Blank frame\n";
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        system("clear");
        
    }

    cv::destroyAllWindows();
    return 0; 
}
