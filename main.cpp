#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>
#include <chrono>
#include <thread>

int main(){
    std::cout << "\e[48;2;0;0;0m"; //Set background colour to black
    std::cout << "\e[H"; //Set to 0,0
    std::cout << "\e[?25l"; //Remove cursor

    cv::Mat frame, resized_frame;
    cv::VideoCapture capture("test4.webm");

    auto startClock = std::chrono::high_resolution_clock::now(); 
    auto endClock = std::chrono::high_resolution_clock::now(); 
    auto actualDurationOfFrame = std::chrono::duration_cast<std::chrono::milliseconds>(endClock-startClock).count();

    int pixelBrightness = 0;
    const std::string CHAR_POOL = " ..--==++''**\%%\%%##";

    if(!capture.isOpened()) return(-1);

    capture.read(frame);
    int width = 450 ;
    int height = 125;
    double fps = capture.get(cv::CAP_PROP_FPS);
    double estimatedDurationOfFrame = 1000/fps;
    int currentFrame= 1;
    double expectedTime = estimatedDurationOfFrame*currentFrame;

    cv::Vec3b bgrPixel;
    startClock = std::chrono::high_resolution_clock::now(); 
    int currentTime;

    for(;;){
        currentFrame += 1;

        cv::resize(frame, resized_frame, cv::Size(width, height), cv::INTER_CUBIC);
        for(int row = 0; row < resized_frame.rows; row++){
            for(int col = 0; col < resized_frame.cols; col++){
                bgrPixel = resized_frame.at<cv::Vec3b>(row,col);
                pixelBrightness = (((int)bgrPixel[0] + (int)bgrPixel[1] + (int)bgrPixel[2]) / 3) / 16;
                std::cout << "\e[38;2;" << (int)bgrPixel[2] << ";" << (int)bgrPixel[1] << ";" << (int) bgrPixel[0] << "m" << CHAR_POOL[pixelBrightness];
            }
            std::cout << "\n";
        }

        std::cout << "\e[H";
        capture.read(frame);
        if(frame.empty()) break;
        
        expectedTime = estimatedDurationOfFrame*currentFrame;
        endClock = std::chrono::high_resolution_clock::now(); 
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(endClock-startClock).count();

        if(currentTime < expectedTime){
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(expectedTime-currentTime)));
        }
    }

    cv::destroyAllWindows();
    return(0);
}