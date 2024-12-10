#include "Cursor.h"



namespace view {


    void Cursor::updateNewTriple(const Triple &t) {
        currentChar.line = t.line;
        currentChar.subLine = t.subLine;
        currentChar.index = t.index;
        updateDocumentTriple();
        moveCursor();
    }



    void Cursor::updateNewTriple(size_t newLines, size_t newCOLS) {
        // line is still gonna be the same
        if (isCursorHovering()) {
            // we are in insert mode and the cursor is pointing to a block with no character
            // we need to adjust the cursor to still
            moveLeft(oldCOLS);
        }

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
        curLINES = newLines;
        // we need to somehow translate the Cursor position to one that fits the new window dimensions
        updateNewTriple(newLines, newCOLS);

        // ofstream log("adjustCursor", ios_base::app);
        oldCOLS = newCOLS;
        

        moveCursor();
        updateDocumentTriple();
        oldCOLS = newCOLS;
        // log << "posn.y: " << posn.y << " " << "posn.x: " << posn.x << endl;
    }


    void Cursor::moveCursor() {
        int wrapped_line_index = 0;
        for (int i = 0; i < currentChar.line; i++) {
            wrapped_line_index += document.fetchWrappedLines()[i].size();
        }
        // if the line the cursor is pointing to is not in the view, we need to adjust the scrollOffset
        if (wrapped_line_index < scrollOffset) {
            scrollOffset = wrapped_line_index;
        }
        else if (wrapped_line_index >= scrollOffset + curLINES) {
            scrollOffset = wrapped_line_index - curLINES + 1;
        }

        // we need to adjust the posn of the cursor to match the currentChar
        posn.y = wrapped_line_index - scrollOffset + currentChar.subLine;
        posn.x = currentChar.index;
    }





















    void Cursor::moveUp(size_t windowCOLS) {
        // mvprintw(10, 45, "Up received");
        // mvprintw(11, 45, "Prev y: %d; Prev x: %d", posn.y, posn.x);
        if (insertModeHover) {
            moveLeft(windowCOLS);
        }

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

        aboveLineEnd = max((int)aboveLineEnd - 1, 0);
        
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
        updateDocumentTriple();
    }





    void Cursor::moveDown(size_t windowLINES, size_t windowCOLS) {

        if (insertModeHover) {
            moveLeft(windowCOLS);
        }

        // ofstream log("log3", ios_base::app);

        if (currentChar.line == document.getLinesSize() - 1) {
            // we are at the end of the file
            return;
        }

        // calculates how many wrapped lines (that we need to skip) are between the current cursor position and the line below
        int numberOfWrappedLinesBetween = document.fetchWrappedLines()[currentChar.line].size() - currentChar.subLine;

        // log << "numberOfWrappedLinesBetween: " << numberOfWrappedLinesBetween << endl;

        int numberOfWrappedLinesBelow = document.fetchWrappedLines()[currentChar.line + 1].size();

        // log << "numberOfWrappedLinesBelow: " << numberOfWrappedLinesBelow << endl;

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

        belowLineEnd = max((int)belowLineEnd - 1, 0);

        if (actualX > belowLineEnd) {
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
        updateDocumentTriple();
    }







    void Cursor::moveLeft(size_t windowCOLS) {
        insertModeHover = false;

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
                posn.x = windowCOLS - 2;
                currentChar.index = posn.x;
            }
            else {
                // we are at the first subLine of the current line
                // don't need to do anything. The Cursor is already at the leftmost position
            }
        }
        // we have to update actualX
        actualX = currentChar.subLine * windowCOLS + currentChar.index;


        // mvprintw(12, 45, "New y: %d; New x: %d", posn.y, posn.x);
        updateDocumentTriple();
    }







    void Cursor::moveRight(size_t windowCOLS) {

        // the length of the current line
        size_t curLineLength = document.fetchWrappedLines()[currentChar.line][currentChar.subLine].size();

        // ofstream log("log3", ios_base::app);

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
        updateDocumentTriple();
    }






    // allows the cursor to move one block to the right even if there is no character to the right
    // used only in insert mode when the cursor can go one extra block to the right
    void Cursor::moveRightInsertMode(size_t windowCOLS) {

        if (!isCursorHovering()) {
            insertModeHover = false;
        }
        else {
            return;
        }


        // the length of the current line
        // ofstream log("moveRightInsertMode", ios_base::app);
        size_t curLineLength = document.fetchWrappedLines()[currentChar.line][currentChar.subLine].size();

        if (posn.x < windowCOLS - 2) {
            if (curLineLength != 0) {
                // we are allowed to move to maximum one block to the right of end character
                if (posn.x < curLineLength) {
                    posn.x++;
                    currentChar.index++;
                    if (currentChar.index == curLineLength) {
                        insertModeHover = true;
                    }
                }
            }
        }
        else {
            if (currentChar.subLine == document.fetchWrappedLines()[currentChar.line].size() - 1) {
                // the cursor is at the end of the line
                // we can move it one block to the right, which is the first block down.
                posn.y++;
                currentChar.subLine++;
                posn.x = 0;
                currentChar.index = posn.x;
                insertModeHover = true;
            }
            else {
                // we are not at the last subLine of the current line
                // we need to move to the start of the line below
                posn.y++;
                currentChar.subLine++;
                posn.x = 0;
                currentChar.index = posn.x;
            }
        }

        actualX = currentChar.subLine * windowCOLS + currentChar.index;
        updateDocumentTriple();
    }













    Posn Cursor::getPosn() const {
        return posn;
    }

    size_t Cursor::getScrollOffset() const {
        // cout << "Returning scroll offset: " << scrollOffset << endl;
        return scrollOffset;
    }


    void Cursor::updateDocumentTriple() {
        document.updateTriple(currentChar);
    }


    bool Cursor::isCursorHovering() const {
        return (currentChar.subLine == document.fetchWrappedLines()[currentChar.line].size() ||
        (currentChar.index == document.fetchWrappedLines()[currentChar.line][currentChar.subLine].size()));
    }



}





