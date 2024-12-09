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
            int line = document.currentCursorChar.line;
            int subLine = document.currentCursorChar.subLine;
            int index = document.currentCursorChar.index;
            // log << "---" << endl;
            // log << "line: " << line << endl;
            // log << "subLine: " << subLine << endl;
            // log << "index: " << index << endl;
            // log << "---" << endl;

            // printable characters
            if ((ch >= 32) && (ch <= 126)) {

                size_t numberOfWrappedLines = document.wrapped_lines[line].size();
                // log << "numberOfWrappedLines: " << numberOfWrappedLines << endl;
                // log << "document.wrapped_lines[line][subLine].size(): " << document.wrapped_lines[line][subLine].size() << endl;

                if ((subLine == numberOfWrappedLines) || (index == document.wrapped_lines[line][subLine].size())) { // the cursor is at the end of the line. This indicates that if we insert char we would append to the end of the document.
                    // we need to avoid inserting at the end of the line which contains a newline character
                    document.lines[line].insert(document.lines[line].size() - 1, 1, ch);
                }
                else { // we just insert at the appropriate index
                    int indexToInsert = subLine * document.wrapped_lines[line][0].size() + index;
                    document.lines[line].insert(indexToInsert, 1, ch);
                    // log << "indexToInsert: " << indexToInsert << endl;
                }
                document.updateWrappedLines();
                cursorMover.moveCursorRightInsertMode();
            }
            // if we have a newline character
            else if (ch == KEY_ENTER_override){
                int curIndex = subLine * document.wrapped_lines[line][0].size() + index;
                string newLine = document.lines[line].substr(curIndex);
                document.lines[line].erase(curIndex);
                document.lines[line].push_back('\n');
                document.lines.insert(document.lines.begin() + line + 1, newLine);
                document.updateWrappedLines();
                cursorMover.moveDown();
                cursorMover.moveToFrontOfLine();

                // string newLine = "";
                // vector<string> newSubLine;
                // newSubLine.push_back(newLine);
                // document.wrapped_lines.insert(document.wrapped_lines.begin() + document.currentCursorChar.line + 1, newSubLine);
                // cursorMover.moveDown();
            }
        }



        void InsertMode::deleteChar() {
            // NOTE: every time we delete, we are removing the char before the cursor

            int line = document.currentCursorChar.line;
            int subLine = document.currentCursorChar.subLine;
            int index = document.currentCursorChar.index;

            // the index of the char we are deleting in lines
            int deleteIndex = static_cast<int>(subLine * document.wrapped_lines[line][0].size() + index) - 1;

            // ofstream log("InsertMode", ios_base::app);

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

                    // log << "----" << endl;
                    // log << "currentLine: " << currentLine << endl;
                    // log << "currentSubLine: " << currentSubLine << endl;
                    // log << "currentIndex: " << currentIndex << endl;
                    // log << "----" << endl;

                    Triple t = {currentLine, currentSubLine, currentIndex};
                    cursorMover.updateCursorTriple(t);
                }
            }
            else {
                document.lines[line].erase(deleteIndex, 1);
                cursorMover.moveLeft();
            }



            // size_t numberOfWrappedLines = document.wrapped_lines[line].size();

            // if (line == 0 && subLine == 0 && index == 0) { // we are at the beginning of the file
            //     return;
            // }

            // if (subLine == 0 && index == 0) {
            //     // we are at the beginning of the current line
            // }

            // else if (subLine == numberOfWrappedLines) { // the cursor is at one line below the actual subLine. If we delete, we would delete the last character of the last subline
            //     cursorMover.moveLeft();
            //     document.wrapped_lines[line][subLine].pop_back();
            // }
            // else if (index == 0) { // the cursor is at the start of the subline. This indicates that if we delete char we would delete the newline character.
            //     if (document.wrapped_lines[line][subLine].size() == 0) {
            //         document.wrapped_lines[line].erase(document.wrapped_lines[line].begin() + subLine);
            //     }
            //     else {
            //         document.wrapped_lines[line][subLine].pop_back();
            //     }
            //     cursorMover.moveLeft();
            // }
            // else { // we just delete at the appropriate index
            //     document.wrapped_lines[line][subLine].erase(index - 1, 1);
            //     cursorMover.moveLeft();
            // }
        }














}
