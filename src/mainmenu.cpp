#include <fmt/core.h>
#include "mainmenu.hpp"

int main(void){
    
    MainMenu mainmenu;

    while(mainmenu.isActive()){
        mainmenu.display();
        mainmenu.readInput();
        mainmenu.moveCursor();
        mainmenu.execute();
    }
    
    return(0);
}