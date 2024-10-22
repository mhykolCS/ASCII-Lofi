#include "opencv2/opencv.hpp"
#include <curses.h>
#include <string>
#include <chrono>
#include <thread>


int main(int argc, char** argv) 
{
    initscr();
    curs_set(0);
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

    cv::Vec3b bgrPixel;

    for(;;){
        cv::resize(frame, resized_frame, cv::Size(width, height), 0, 0, cv::INTER_LINEAR_EXACT);
        for(int row = 0; row < resized_frame.rows; row++){
            for(int col = 0; col < resized_frame.cols; col++){
                bgrPixel = resized_frame.at<cv::Vec3b>(row,col);
                pixelBrightness = (((int)bgrPixel[0] + (int)bgrPixel[1] + (int)bgrPixel[2]) / 3) / 28;
                printw("%c", CHAR_POOL[pixelBrightness]);
            }
            refresh();
            printw("\n");
        }

        capture.read(frame);
        if(frame.empty()) break;

        
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

        move(0,0);
    }

    cv::destroyAllWindows();
    endwin();
    return 0; 
}
