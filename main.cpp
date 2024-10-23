#include "opencv2/opencv.hpp"
#include <curses.h>
#include <string>
#include <chrono>
#include <thread>


void initColors(){
    init_color(  1,    0,    0,  666 ); //Dark Blue
    init_color(  2,    0,  666,    0 ); //Dark Green
    init_color(  3,    0,  666,  666 ); //Dark Cyan
    init_color(  4,  333,  333,  333 ); //Dark Grey
    init_color(  5,  333,  333, 1000 ); //Light Blue
    init_color(  6,  333, 1000,  333 ); //Light Green
    init_color(  7,  333, 1000, 1000 ); //Light Cyan
    init_color(  8,  666,    0,    0 ); //Dark Red
    init_color(  9,  666,    0,  666 ); //Dark Purple
    init_color( 10,  666,  333,    0 ); //Orange
    init_color( 11,  666,  666,  666 ); //Light Grey
    init_color( 12, 1000,  333,  333 ); //Light Red
    init_color( 13, 1000,  333, 1000 ); //Light Purple
    init_color( 14, 1000, 1000,  333 ); //Light Yellow
    init_color( 15, 929, 847, 847 ); //White
    

    for(int i = 0; i < 16; i++){
        init_pair(i, i, 0);
    }

    return;
}

int returnColor(int r, int g, int b){

    if(r < 63 && g < 63 && b < 100) return(4);
    if(r < 63 && g < 93 && b < 220) return(1);
    if(r < 63 && g < 127 && b < 63) return(2);
    if(r < 63 && g < 127 && b < 191) return(3);
    if(r < 127 && g < 150 && b < 150) return(4);
    if(r < 127 && g < 191 && b < 255) return(5);
    if(r < 127 && g < 255 && b < 127) return(6);
    if(r < 127 && g < 255 && b < 255) return(7);
    if(r < 191 && g < 63 && b < 63) return(8);
    if(r < 191 && g < 63 && b < 650) return(9);
    if(r < 191 && g < 127 && b < 63) return(10);
    if(r < 191 && g < 191 && b < 191) return(11);
    if(r < 255 && g < 127 && b < 127) return(12);
    if(r < 255 && g < 127 && b < 255) return(13);
    if(r < 255 && g < 100 && b < 127) return(14);
    if(r < 255 && g < 255 && b < 255) return(15);

    return 15;
}


int main(int argc, char** argv) 
{
    initscr();
    start_color();
    initColors();

    curs_set(0);
    cv::Mat frame, resized_frame;
    cv::VideoCapture capture("test1.webm");

    int totalFrames = capture.get(cv::CAP_PROP_FRAME_COUNT);
    int videoLength = 165;
    int fps = totalFrames / videoLength / 2;

    int pixelBrightness = 0;
    const std::string CHAR_POOL = " .-=+`*%#";

    if(!capture.isOpened()) return(-1);

    capture.read(frame);
    int width = 130;
    int height = 40;

    cv::Vec3b bgrPixel;

    for(;;){
        cv::resize(frame, resized_frame, cv::Size(width, height), cv::INTER_CUBIC);
        for(int row = 0; row < resized_frame.rows; row++){
            for(int col = 0; col < resized_frame.cols; col++){
                bgrPixel = resized_frame.at<cv::Vec3b>(row,col);
                pixelBrightness = (((int)bgrPixel[0] + (int)bgrPixel[1] + (int)bgrPixel[2]) / 3) / 29;
                attrset(COLOR_PAIR(returnColor(bgrPixel[2], bgrPixel[1], bgrPixel[0])));

                printw("%c", CHAR_POOL[pixelBrightness]);
            }
            refresh();
            printw("\n");
        }

        capture.read(frame);
        if(frame.empty()) break;

        

        std::this_thread::sleep_for(std::chrono::milliseconds(fps));

        move(0,0);
    }

    cv::destroyAllWindows();
    endwin();
    return 0; 
}
