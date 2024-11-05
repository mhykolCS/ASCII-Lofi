#include "asciiLofi.h"
#include <ncurses.h>


int readOptions(){
    switch(getch()){
        case KEY_UP:
            return(0);
        case KEY_DOWN:
            return(1);
        case '\n':
            return(2);
        default:
            return(3);
    }
}

int main(){
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    system("mkdir -p data");
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);

    int video_width = 137;
    int video_height = 40;
    int selection = 0;
    bool confirmed = false;

    std::vector<std::string> videos;

    for(;;){
        move(0,0);

        attron(COLOR_PAIR(1));
        attron(A_BOLD);
        printw("<----Video to ASCII Media Player---->\n\n");
        attroff(A_BOLD);
        printw("Use arrow keys and enter to select an option\n\n");

        if(selection == 0) attrset(COLOR_PAIR(2));
        printw("Start Lofi Ascii Player\n");
        refresh();

        attrset(COLOR_PAIR(1));
        if(selection == 1) attrset(COLOR_PAIR(2));
        printw("Select Playback Folder\n");
        refresh();

        attrset(COLOR_PAIR(1));
        if(selection == 2) attrset(COLOR_PAIR(2));
        printw("Download Youtube Videos/Playlists\n");
        refresh();

        attrset(COLOR_PAIR(1));
        if(selection == 3) attrset(COLOR_PAIR(2));
        printw("Configure Player Resolution\n");
        refresh();

        attrset(COLOR_PAIR(1));
        if(selection == 4 )attrset(COLOR_PAIR(2));
        printw("Configure Player Art Type\n");
        refresh();

        attrset(COLOR_PAIR(1));
        if(selection == 5) attrset(COLOR_PAIR(2));
        printw("Exit");
        refresh();

        switch(readOptions()){
            case 0:
                if(selection == 0){
                    selection = 5;
                    break;
                }
                selection--;
                break;
            case 1:
                if(selection == 5){
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

        refresh();

        if(confirmed){
            
            switch(selection){
                case 0:
                    //endwin();
                    for(int i = 0; i < videos.size(); i++){
                        play_video(&videos.at(i), &video_width, &video_height);
                    }
                    //initscr();
                    break;
                case 1:
                    clear();
                    browse_and_select(&videos);
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    endwin();
                    return(0);
                default:
                    break;
            };
            confirmed = false;
        }
    }

    endwin();
    return(0);
}