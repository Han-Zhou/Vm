#include "Cursor.h"



namespace view {


    void Cursor::moveUp() {
        mvprintw(10, 45, "Up received");
        mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);
        if (posn.y > 0) {
            posn.y--;
        }
        else {
            if (scrollOffset > 0) {
                scrollOffset--;
            }
        }
        size_t aboveLineEnd = document.fetchWrappedLines()[scrollOffset + posn.y].size();
        if (posn.x > aboveLineEnd) {
            // actualX = posn.x;
            posn.x = (aboveLineEnd == 0) ? 0 : aboveLineEnd - 1;
        }
        else {
           if (actualX > aboveLineEnd - 1) {
               posn.x = (aboveLineEnd == 0) ? 0 : aboveLineEnd - 1;
           }
           else {
               posn.x = actualX;
           }
        }
        mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
    }


    void Cursor::moveDown(size_t windowLINES) {
        mvprintw(10, 45, "Down received");
        mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);
        // we haven't reached the end of the file yet
        if (posn.y < document.getWrappedLinesSize() - 1) {
            if (posn.y < windowLINES - 1) {
                posn.y++;
            }
            else {
                // we scroll the entire page down
                if (scrollOffset < document.getWrappedLinesSize() - windowLINES) {
                    scrollOffset++;
                }
            }
        }
        size_t belowLineEnd = document.fetchWrappedLines()[scrollOffset + posn.y].size();
        if (posn.x > belowLineEnd - 1) {
            // actualX = posn.x;
            posn.x = (belowLineEnd == 0) ? 0 : belowLineEnd - 1;
        }
        else {
            if (actualX > belowLineEnd) {
                posn.x = (belowLineEnd == 0) ? 0 : belowLineEnd - 1;
            }
            else {
                posn.x = actualX;
            }
        }
        mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
    }


    void Cursor::moveLeft() {
        mvprintw(10, 45, "Left received");
        mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);
        if (posn.x > 0) {
            posn.x--;
            actualX = posn.x;
        }
        mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
    }


    void Cursor::moveRight(size_t windowCOLS) {
        mvprintw(10, 45, "Right received");
        mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);
        size_t lineLength = document.fetchWrappedLines()[posn.y].size();
        if ((posn.x < windowCOLS - 1) && (lineLength != 0) && (posn.x < lineLength - 1)) {
            posn.x++;
            actualX = posn.x;
        }
        mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
    }







    Posn Cursor::getPosn() const {
        return posn;
    }

    size_t Cursor::getScrollOffset() const {
        // cout << "Returning scroll offset: " << scrollOffset << endl;
        return scrollOffset;
    }




}





