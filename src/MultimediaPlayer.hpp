#include "asciiLofi.hpp"
#include <string>
#include <vector>

#ifndef MULTIMEDIAPLAYER_H
#define MULTIMEDIAPLAYER_H

class MultimediaPlayer{
    public:
        MultimediaPlayer(int width, int height) : v_width(width), v_height(height) {};


        void appendFilename(std::string filename){filenames.push_back(filename);};
        void clearFilenames(){filenames.clear();};
        void playbackReset(){currentFile = 0;};

        void setWidth(int width){v_width = width;};
        void setHeight(int height){v_height = height;};

        int* getWidth_P(){return(&v_width);};
        int* getHeight_P(){return(&v_height);};
        int getTotalFiles(){return(filenames.size());};
        int getCurrentFileIndex(){return(currentFile);};
        std::string getNextFile();
        std::string getFilenameAtIndex(int i){return(filenames.at(i));};
        std::string* getFilenameAtIndex_P(int i){return(&filenames.at(i));};

    private:
        int v_height;
        int v_width;
        int currentFile = 0;
        std::vector<std::string> filenames;
};

#endif