#include "asciiLofi.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <ncurses.h>


void listenForKeyPress(){
    
}

void render(int* width, int* height, std::string video_name){
    std::cout << "\x1b]2;" << video_name << "\x07";
    auto startClock = std::chrono::high_resolution_clock::now(); 
    auto endClock = std::chrono::high_resolution_clock::now(); 
    auto actualDurationOfFrame = std::chrono::duration_cast<std::chrono::milliseconds>(endClock-startClock).count();

    int pixelBrightness = 0;
    const std::string CHAR_POOL = " ..--==++''**\%%\%%##";
    std::string outputStream = "";
    //const std::string CHAR_POOL = "#####################";

    std::string filepath = "data/" + video_name;

    cv::Mat frame, resized_frame;
    cv::VideoCapture capture(filepath);

    if(!capture.isOpened()) return;

    capture.read(frame);
    double fps = capture.get(cv::CAP_PROP_FPS);
    double estimatedDurationOfFrame = 1000/fps;
    int currentFrame= 1;
    double expectedTime = estimatedDurationOfFrame*currentFrame;

    cv::Vec3b bgrPixel;
    startClock = std::chrono::high_resolution_clock::now(); 
    int currentTime;

    for(;;){
        currentFrame += 1;

        cv::resize(frame, resized_frame, cv::Size(*width, *height), cv::INTER_CUBIC);
        for(int row = 0; row < resized_frame.rows; row++){

            for(int col = 0; col < resized_frame.cols; col++){
                
                bgrPixel = resized_frame.at<cv::Vec3b>(row,col);
                pixelBrightness = (((int)bgrPixel[0] + (int)bgrPixel[1] + (int)bgrPixel[2]) / 3) / 16;
                outputStream += "\e[38;2;" + std::to_string((int)bgrPixel[2]) + ";" + std::to_string((int)bgrPixel[1]) + ";" + std::to_string((int) bgrPixel[0]) + "m\u2588";
                //outputStream += "\e[38;2;" + std::to_string((int)bgrPixel[2]) + ";" + std::to_string((int)bgrPixel[1]) + ";" + std::to_string((int) bgrPixel[0]) + "m" + CHAR_POOL[pixelBrightness];
            }
            std::cout << outputStream;
            outputStream = "";
            std::cout << "\n";
            std::cout << "\e[0G";
        }
        //if(currentFrame % (int)fps == 0) std::cout << "\e[2J";
        std::cout << "\e[H";
        capture.read(frame);
        if(frame.empty()) break;
        
        expectedTime = estimatedDurationOfFrame*currentFrame;
        endClock = std::chrono::high_resolution_clock::now(); 
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(endClock-startClock).count();
        
        if(currentTime < expectedTime){
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(expectedTime-currentTime)));
        }

        if(currentTime > expectedTime){
            currentFrame+=;
            capture.read(frame);
        }
        
    }
}



void play_video(MultimediaPlayer* multimediaPlayer){
    std::cout << "\e[48;2;0;0;0m"; //Set background colour to black
    std::cout << "\e[H"; //Set to 0,0
    std::cout << "\e[?25l"; //Remove cursor

    render(multimediaPlayer->getWidth_P(), multimediaPlayer->getHeight_P(), multimediaPlayer->getNextFile());

    listenForKeyPress();

    cv::destroyAllWindows();

    return;

}