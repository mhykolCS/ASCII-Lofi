#include "asciiLofi.hpp"
#include <ncurses.h>
#include <dirent.h>

struct file{
    std::string name;
    bool enabled;
    int ID;
};

extern int readOptions();

void browse_and_select(MultimediaPlayer* multimediaPlayer){

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);

    move(0,0);

    std::vector<file> allFiles;
    struct dirent *ent;
    int selection = 0;
    bool confirmed = false;
    
    DIR *dir = opendir("data/");

    if (dir == NULL){
        printw("Failed to open directory, press enter to continue\n");
        getch();
        return;
    }

    while((ent = readdir(dir)) != NULL){
        if(std::string(ent->d_name) == "." || std::string(ent->d_name) == "..") continue;
        allFiles.push_back({std::string(ent->d_name), false, selection});
        selection++;
    }

    selection = 0;

    for(int i = 0; i < multimediaPlayer->getTotalFiles(); i++){
        for(int j = 0; j < allFiles.size(); j++){
            if (multimediaPlayer->getFilenameAtIndex(i) == allFiles.at(j).name) allFiles.at(j).enabled = true;
        }
    }

    for(;;){
        attron(COLOR_PAIR(1));  
        attron(A_BOLD);
        printw("<----Video to ASCII Media Player---->\n\n");
        attroff(A_BOLD);
        printw("Use the arrow keys and the enter key to select and deselect video files\n\n");

        for(std::vector<file>::iterator it = allFiles.begin(); it != allFiles.end(); it++){
            attrset(COLOR_PAIR(1));
            if(it->enabled) attrset(COLOR_PAIR(2));
            if(it->ID == selection) attrset(COLOR_PAIR(3));
            printw("%s\n", it->name.c_str());
            refresh();

        }

        attrset(COLOR_PAIR(1));
        if(selection == allFiles.size()) attrset(COLOR_PAIR(3));
        printw("\nSave and Exit\n");
        refresh();

        attrset(COLOR_PAIR(1));
        if(selection == allFiles.size()+1) attrset(COLOR_PAIR(3));
        printw("Exit without Saving\n");
        refresh();

        refresh();

        switch(readOptions()){
            case 0:
                if(selection == 0){
                    selection = allFiles.size() + 1;
                    break;
                }
                selection--;
                break;
            case 1:
                if(selection == allFiles.size()+1) {
                    selection = 0;
                    break;   
                }
                selection++;
                break;
            case 2:
                confirmed = true;
                break;

            default:
                break;
        };

        if(confirmed){

            if(selection == allFiles.size()){
                multimediaPlayer->clearFilenames();
                for(int i = 0; i < allFiles.size(); i++){
                    if(allFiles.at(i).enabled) {
                        multimediaPlayer->appendFilename(std::string(allFiles.at(i).name));
                    }
                }
                closedir(dir);
                clear();
                move(0,0);
                return;
            }
            if(selection == allFiles.size()+1){
                closedir(dir);
                clear();
                move(0,0);
                return;
            } 

            (allFiles.at(selection).enabled) ? allFiles.at(selection).enabled = false : allFiles.at(selection).enabled = true;
            confirmed = false;
        }

        refresh();

        move(0,0);
    }


    return;
}