#include <ncurses.h>
#include <filesystem>
#include <iostream>

class MainMenu{
    public:
        MainMenu();
        ~MainMenu();
        void display();
        void readInput();
        void moveCursor();
        void execute();
        int isActive();
    private:
        enum KeyStrokes {KeyUp, KeyDown, KeyEnter, KeyInvalid};
        KeyStrokes keyPress = KeyInvalid;
        int option = 0;
        int confirmed = 0;
        int active = 1;

};

MainMenu::MainMenu(){
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    if (!std::filesystem::exists("data")) std::filesystem::create_directory("data");
}

MainMenu::~MainMenu(){
    endwin();
}

void MainMenu::display(){
    clear();
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
    printw("<----Video to ASCII Media Player---->\n\n");
    attroff(A_BOLD);
    printw("Use arrow keys and enter to select an option\n\n");
 
    if(option == 0) attrset(COLOR_PAIR(2));
    printw("Start Lofi Ascii Player\n");

    attrset(COLOR_PAIR(1));
    if(option == 1) attrset(COLOR_PAIR(2));
    printw("Select Playback Folder\n");

    attrset(COLOR_PAIR(1));
    if(option == 2) attrset(COLOR_PAIR(2));
    printw("Download Youtube Videos/Playlists\n");

    attrset(COLOR_PAIR(1));
    if(option == 3) attrset(COLOR_PAIR(2));
    printw("Configure Player Resolution\n");

    attrset(COLOR_PAIR(1));
    if(option == 4 )attrset(COLOR_PAIR(2));
    printw("Configure Player Art Type\n");

    attrset(COLOR_PAIR(1));
    if(option == 5 )attrset(COLOR_PAIR(2));
    printw("Configure Sound Device\n");

    attrset(COLOR_PAIR(1));
    if(option == 6) attrset(COLOR_PAIR(2));
    printw("Exit");

    return;
}

void MainMenu::readInput(){

    switch(getch()){
        case KEY_UP:
            keyPress = KeyUp;
            break;
        case KEY_DOWN:
            keyPress = KeyDown;
            break;
        case '\n':
            keyPress = KeyEnter;
            break;
        default:
            keyPress = KeyInvalid;
    }
    return;
}

void MainMenu::moveCursor(){

    switch(keyPress){

        case KeyUp:
            option--;
            if(option == -1) option = 6;
            break;

        case KeyDown:
            option++;
            if(option == 7) option = 0;
            break;
        
        case KeyEnter:
            confirmed = true;
            break;
        
        case KeyInvalid:
            break;

        default:
            break;
    };

    return;
}

void MainMenu::execute(){

    if(confirmed){
        switch(option){
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                active = false;
                break;
            default:
                break;
        };
        confirmed = false;
    }

}

int MainMenu::isActive(){
    return(active);
}