#include "MainController.h"
#include "../structs/Keys.h"


using namespace std;


namespace controller {


    string MainController::processInput() {
        int ch = window.getChar();
        mvprintw(0, 45, "Key pressed: %d", ch);
        mvprintw(0, 45, "KeyUp: %d", KEY_UP_ARROW);
        switch (ch) {
            case KEY_UP_ARROW:
                mvprintw(0, 45, "UP");
                cursor.moveUp();
                break;
            case KEY_DOWN_ARROW:
                mvprintw(0, 45, "DOWN");
                cursor.moveDown(window.getLINES());
                break;
            case KEY_LEFT:
                cursor.moveLeft();
                break;
            case KEY_RIGHT:
                cursor.moveRight(window.getCOLS());
                break;
            case 'q':
                return "quit";
                break;
        }
        return "";
    }












}

