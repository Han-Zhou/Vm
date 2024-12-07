#include "Cursor.h"



namespace view {

    void Cursor::getNewTriple(size_t newLines, size_t newCOLS) {
        // line is still gonna be the same
        int newSublineSize = newCOLS - 1;
        int oldLineIndex = currentChar.subLine * (oldCOLS - 1) + currentChar.index;

        int newNumSublines = document.fetchWrappedLines()[currentChar.line].size();
        for (int i = 0; i < newNumSublines; i++) {
            int curSublineSize = document.fetchWrappedLines()[currentChar.line][i].size();
            if (oldLineIndex < curSublineSize) {
                currentChar.subLine = i;
                currentChar.index = oldLineIndex;
                break;
            }
            oldLineIndex -= curSublineSize;
        }
    }




    void Cursor::adjustCursor(size_t newLines, size_t newCOLS) {
        // we need to somehow translate the Cursor position to one that fits the new window dimensions
        getNewTriple(newLines, newCOLS);

        // if the line the cursor is pointing to is not in the view, we need to adjust the scrollOffset
        if (currentChar.line < scrollOffset) {
            scrollOffset = currentChar.line;
        }
        else if (currentChar.line >= scrollOffset + newLines) {
            scrollOffset = currentChar.line - newLines + 1;
        }

        // we need to adjust the position of the cursor in the window
        posn.y = currentChar.line - scrollOffset;
        posn.x = currentChar.index % newCOLS;
    }






















    void Cursor::moveUp(size_t windowCOLS) {
        // mvprintw(10, 45, "Up received");
        // mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);

        if (currentChar.line == 0) {
            // we are at the beginning of the file
            return;
        }

        currentChar.line--;

        // calculates how many lines are between the first subline of the line above and the current cursor line
        int numberOfWrappedLines = document.fetchWrappedLines()[currentChar.line].size() + currentChar.subLine;

        if (numberOfWrappedLines <= posn.y) {
            // we have sufficient space in the view above the cursor
            // don't need to scroll the entire page
            posn.y -= numberOfWrappedLines;
        }
        else {
            // we need to scroll the entire page up
            scrollOffset -= (numberOfWrappedLines - posn.y);
            posn.y = 0;
        }

        // we are always at the first subLine when we move up
        currentChar.subLine = 0;


        // Now we determine where the cursor should be in the new line
        size_t aboveLineEnd = 0;
        auto newLine = document.fetchWrappedLines()[currentChar.line];
        for (int i = 0; i < newLine.size(); ++i) {
            aboveLineEnd += newLine[i].size();
        }
        
        if (actualX > aboveLineEnd) {
            // the line above the current cursor position is shorter than the current x position
            // so we move the cursor to the end of the line
            currentChar.subLine = newLine.size() - 1;
            posn.y += currentChar.subLine;
            int endOfNewSubline = newLine[currentChar.subLine].size() - 1;
            posn.x = max(0, endOfNewSubline);
        }
        else {
            // the line above the current cursor position is longer than the current x position or actualX
            // so we move the cursor to the same x position or actualX
            currentChar.subLine = actualX / windowCOLS;
            posn.y += currentChar.subLine;
            posn.x = actualX % windowCOLS;
        }
        currentChar.index = posn.x;

        // mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
    }





    void Cursor::moveDown(size_t windowLINES, size_t windowCOLS) {
        // mvprintw(10, 45, "Down received");
        // mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);
        // we haven't reached the end of the file yet

        ofstream log("log3", ios_base::app);

        if (currentChar.line == document.getLinesSize() - 1) {
            // we are at the end of the file
            return;
        }

        log << "---------------------------------" << endl;
        log << "---moving down---" << endl;
        log << "---------------------------------" << endl;
        log << "currentChar.line: " << currentChar.line << endl;
        log << "currentChar.subLine: " << currentChar.subLine << endl;
        log << "currentChar.index: " << currentChar.index << endl;
        log << "actualX: " << actualX << endl;
        log << "posn.y: " << posn.y << endl;
        log << "posn.x: " << posn.x << endl;



        // calculates how many wrapped lines (that we need to skip) are between the current cursor position and the line below
        int numberOfWrappedLinesBetween = document.fetchWrappedLines()[currentChar.line].size() - currentChar.subLine;

        log << "numberOfWrappedLinesBetween: " << numberOfWrappedLinesBetween << endl;

        int numberOfWrappedLinesBelow = document.fetchWrappedLines()[currentChar.line + 1].size();

        log << "numberOfWrappedLinesBelow: " << numberOfWrappedLinesBelow << endl;

        currentChar.line++;

        // ensure that there is enough space for the entirity of the line below
        if (numberOfWrappedLinesBetween + numberOfWrappedLinesBelow - 1 < (windowLINES - posn.y)) {
            // we have sufficient space in the view below the cursor
            // don't need to scroll the entire page
            posn.y += numberOfWrappedLinesBetween;
        }
        else {
            // we need to scroll the entire page down
            scrollOffset += (numberOfWrappedLinesBetween + numberOfWrappedLinesBelow - (windowLINES - posn.y));
            posn.y = windowLINES - numberOfWrappedLinesBelow;
        }

        // we are always at the first subLine when we move down
        currentChar.subLine = 0;


        // Now we determine where the cursor should be in the new line
        size_t belowLineEnd = 0;
        auto newLine = document.fetchWrappedLines()[currentChar.line];
        for (int i = 0; i < newLine.size(); ++i) {
            belowLineEnd += newLine[i].size();
        }

        if (actualX> belowLineEnd) {
            // the line below the current cursor position is shorter than the current x position
            // so we move the cursor to the end of the line
            currentChar.subLine = newLine.size() - 1;
            posn.y += currentChar.subLine;
            int endOfNewSubline = newLine[currentChar.subLine].size() - 1;
            posn.x = max(0 , endOfNewSubline);
        }
        else {
            // the line below the current cursor position is longer than the current x position
            // so we move the cursor to the same x position or actualX
            currentChar.subLine = actualX / windowCOLS;
            posn.y += currentChar.subLine;
            posn.x = actualX % windowCOLS;
        }

        currentChar.index = posn.x;

        log << "-" << endl;
        log << "new currentChar.line: " << currentChar.line << endl;
        log << "new currentChar.subLine: " << currentChar.subLine << endl;
        log << "new currentChar.index: " << currentChar.index << endl;
        log << "new actualX: " << actualX << endl;
        log << "new posn.y: " << posn.y << endl;
        log << "new posn.x: " << posn.x << endl;


        // mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
    }







    void Cursor::moveLeft(size_t windowCOLS) {
        // mvprintw(10, 45, "Left received");
        // mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);

        if (posn.x > 0) {
            posn.x--;
            currentChar.index--;
        }
        else {
            // the cursor is at the start of the line
            // we need to decide if moveLeft would move it the the rightmost position of the line above
            // i.e. the line above and the current line belongs the the same line in the document, just wrapped
            if (currentChar.subLine > 0) {
                // we are not at the first subLine of the current line
                // we need to move to the end of the line above 
                posn.y--;
                currentChar.subLine--;
                posn.x = windowCOLS - 1;
                currentChar.index = posn.x;
            }
            else {
                // we are at the first subLine of the current line
                // don't need to do anything. The Cursor is already at the leftmost position
            }
        }
        // we have to update actualX
        actualX = currentChar.subLine * windowCOLS + currentChar.index;


        mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
    }







    void Cursor::moveRight(size_t windowCOLS) {
        // mvprintw(10, 45, "Right received");
        // mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);

        // the length of the current line
        size_t curLineLength = document.fetchWrappedLines()[currentChar.line][currentChar.subLine].size();

        ofstream log("log3", ios_base::app);

        if (posn.x < windowCOLS - 2) {
            if (curLineLength != 0) {
                // we need to move right and have the space to do so
                if (posn.x < curLineLength - 1) {
                    posn.x++;
                    currentChar.index++;
                }
            }
        }
        else {
            // the cursor is at the end of the line
            // we need to decide if moveRight would move it the the leftmost position of the line below
            // i.e. the line below and the current line belongs the the same line in the document, just wrapped
            // log << "Moving right at end of line" << endl;
            // log << "currentChar.line: " << currentChar.line << endl;
            // log << "currentChar.subLine: " << currentChar.subLine << endl;
            // log << "currentChar.index: " << currentChar.index << endl;
            // log << "document.fetchWrappedLines()[currentChar.line].size(): " << document.fetchWrappedLines()[currentChar.line].size() << endl;
            // log << "_____________________________________________________" << endl;
            if (currentChar.subLine < document.fetchWrappedLines()[currentChar.line].size() - 1) {
                // we are not at the last subLine of the current line
                // we need to move to the start of the line below
                posn.y++;
                currentChar.subLine++;
                posn.x = 0;
                currentChar.index = posn.x;
            }
            else {
                // we are at the last subLine of the current line
                // don't need to do anything. The Cursor is already at the rightmost position
            }
        }

         // we have to update actualX
        actualX = currentChar.subLine * windowCOLS + currentChar.index;

        // mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
    }







    Posn Cursor::getPosn() const {
        return posn;
    }

    size_t Cursor::getScrollOffset() const {
        // cout << "Returning scroll offset: " << scrollOffset << endl;
        return scrollOffset;
    }




}





