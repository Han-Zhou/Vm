#include "InsertMode.h"


namespace mode {

    ReturnMessage InsertMode::processInput(vector<int> input) {
        if (input.size() > 1) {
            // ofstream log("errorInsertMode", ios_base::app);
            // log << "Error: InsertMode::processInput: input size > 1" << endl;
            // for (int ch : input) {
            //     log << ch;
            // }   
            // log << endl;
            return ReturnMessage::ERROR;
        }

        if (input[0] == KEY_UP_ARROW) {
            cursorMover.moveUp();
        }
        else if (input[0] == KEY_DOWN_ARROW) {
            cursorMover.moveDown();
        } 
        else if (input[0] == KEY_LEFT_ARROW) {
            cursorMover.moveLeft();
        } 
        else if (input[0] == KEY_RIGHT_ARROW) {
            cursorMover.moveCursorRightInsertMode();
        }
        else if (input[0] == KEY_ESC) {
            cursorMover.moveLeft();
            return ReturnMessage::NORMAL;
        }
        else if (input[0] == KEY_TAB) {
            // insert 4 spaces
            for (int i = 0; i < 4; i++) {
                insertChar(' ');
            }
        }
        else if (input[0] == KEY_DELETE_override) {
            deleteChar();
        }
        else {
            insertChar(input[0]);
        }
        // document.updateDocument();
        return ReturnMessage::RUNNING;
    }




    void InsertMode::insertChar(int ch) {

        // ofstream  log("InsertMode", ios_base::app);
        document.insertChar(ch);
 
        // judge if ch belongs to printable characters
        if ((ch >= 32) && (ch <= 126)) {
            cursorMover.moveCursorRightInsertMode();
        }
        // if we have a newline character
        else if (ch == KEY_ENTER_override){
            cursorMover.moveDown();
            cursorMover.moveToFrontOfLine();
        }
    }



    void InsertMode::deleteChar() {
        // NOTE: every time we delete, we are removing the char before the cursor

        int line = document.currentCursorChar.line;
        int subLine = document.currentCursorChar.subLine;
        int index = document.currentCursorChar.index;

        // the index of the char we are deleting in lines
        int deleteIndex = static_cast<int>(subLine * document.wrapped_lines[line][0].size() + index) - 1;

        if (deleteIndex == -1) { // we are at the beginning of the line
            if (line == 0) { // we are at the beginning of the file
                return;
            }
            else { // we need to append the current line to the previous line
                // first we delete the newline character at the end of the previous line
                int currentLine = line - 1;
                int currentSubLine = document.wrapped_lines[currentLine].size() - 1;
                int currentIndex = document.wrapped_lines[currentLine][currentSubLine].size();

                

                document.lines[currentLine].pop_back();
                document.lines[currentLine].append(document.lines[line]);
                document.lines.erase(document.lines.begin() + line);

                Triple t = {currentLine, currentSubLine, currentIndex};
                cursorMover.updateCursorTriple(t);
            }
        }
        else {
            document.lines[line].erase(deleteIndex, 1);
            cursorMover.moveLeft();
        }
    }














}
