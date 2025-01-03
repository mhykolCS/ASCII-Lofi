#include "asciiLofi.hpp"
#include "MultimediaPlayer.hpp"
#include <string>
#include <vector>

std::string MultimediaPlayer::getNextFile(){
    std::string nextFile = this->getFilenameAtIndex(currentFile);
    currentFile += 1;
    if(currentFile < this->getTotalFiles()-1){
        return("");
    }
    return(nextFile);
}