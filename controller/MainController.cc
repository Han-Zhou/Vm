#include "MainController.h"
#include "../structs/Keys.h"
#include <csignal>


using namespace std;


namespace controller {


    string MainController::processInput() {
        ofstream log("log4err", ios_base::app);
        int ch = window.getChar();
        // mvprintw(0, 45, "Key pressed: %d", ch);
        // mvprintw(0, 45, "KeyUp: %d", KEY_UP_ARROW);
        switch (ch) {
            case KEY_UP_ARROW:
                // mvprintw(0, 45, "UP");
                cursor.moveUp(window.getCOLS());
                break;
            case KEY_DOWN_ARROW:
                try {
                    cursor.moveDown(window.getLINES() - 1, window.getCOLS());
                } catch (const exception &e) {
                    log << e.what() << endl;
                }
                break;
            case KEY_LEFT:
                cursor.moveLeft(window.getCOLS());
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

