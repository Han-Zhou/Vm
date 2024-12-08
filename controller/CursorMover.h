#ifndef CURSORMOVER_H
#define CURSORMOVER_H

#include "../view/Cursor.h"
#include "../view/Window.h"
#include "../structs/Keys.h"
#include "../structs/Triple.h"



namespace controller {

    // moves the cursor on the window
    class CursorMover {
        view::Cursor &cursor;
        view::Window &window;
        
    public:



        CursorMover(view::Cursor &cursor, view::Window &window): cursor{cursor}, window{window} {}

        void moveUp() {
            cursor.moveUp(window.getCOLS());
        }

        void moveDown() {
            cursor.moveDown(window.getLINES() - 1, window.getCOLS());
        }

        void moveLeft() {
            cursor.moveLeft(window.getCOLS());
        }

        void moveRight() {
            cursor.moveRight(window.getCOLS());
        }

        // moves the cursor to the right by one character
        // This is special as it allows the cursor to not necessarily point to a character
        // only allowed in insertmode and when normal mode turns to insert mode
        void moveCursorRightInsertMode() {
            cursor.moveRightInsertMode(window.getCOLS());
        }

        void moveToFrontOfLine() {
            cursor.moveToFrontOfLine(window.getLINES());
        }

        void updateCursorTriple(const Triple &t) {
            cursor.updateNewTriple(t);
            cursor.moveCursor(window.getLINES());
        }
    };
}












#endif