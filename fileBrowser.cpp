#include "asciiLofi.h"
#include <ncurses.h>
#include <dirent.h>

void browse_and_select(std::vector<std::string>* videos){

    move(0,0);

    std::vector<char*> allFiles;
    struct dirent *ent;
    std::string temp = "";


    DIR *dir = opendir("data/");

    if (dir == NULL){
        printw("Failed to open directory, press enter to continue\n");
        getch();
        return;
    }

    while((ent = readdir(dir)) != NULL){
        allFiles.push_back(ent->d_name);
    }

    for(int i = 0; i < allFiles.size(); i++){
        printw("%s\n", ent->d_name);
        getch();
    }

    closedir(dir);

    return;
}