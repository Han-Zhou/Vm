#ifndef CURSOR_H
#define CURSOR_H


#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "../structs/Posn.h"
#include "../structs/Triple.h"
// #include "../view/Window.h"
#include "../model/Document.h"

using namespace std;


namespace controller {
    class CursorMover;
}


namespace view {

    class Cursor {
        // posn is the position of the cursor in the window/screen
        Posn posn;

        model::Document &document;
        size_t scrollOffset = 0;

        // keeps track of which column should the cursor point to after moving up or down
        int actualX = 0; 

        // the column size before resizing
        int oldCOLS;
        int curLINES;

        // keeps track of where the cursor is pointing to in the vector<vector<string>> wrappedLines. Here y and x don't represent coordinates 
        // i.e. it determines which part of the document the cursor is pointing to.
        // for example, if the current cursor position is pointing to the character wrappedLines[0][1][2], then currentChar = {0, 1, 2}
        Triple currentChar = {0, 0, 0};

        // while in insert mode, the cursor can sometimes even point to a block with no character. This bool determines if that is the case
        bool insertModeHover = false;

        void updateNewTriple(size_t newLINES, size_t newCOLS);
        void updateNewTriple(const Triple &t);
        void moveCursor(size_t LINES);
        void moveCursor();
 


    public:

        friend class controller::CursorMover;

        Cursor(int x, int y, model::Document &document, int COLS, int LINES) : posn{x, y}, document{document}, oldCOLS{COLS}, curLINES{LINES} {
            cout << "Cursor created" << endl;
        }

        Cursor(const Cursor &c) = delete;
        Cursor(Cursor &&c) = delete;
        Cursor &operator=(const Cursor &c) = delete;
        Cursor &operator=(Cursor &&c) = delete;

        // each time with a resize, we need to adjust the cursor position to ensure that the character the cursor is pointing to remains unvaried and on the screen
        void adjustCursor(size_t newLINES, size_t newCOLS);

        void moveUp(size_t windowCOLS);
        void moveDown(size_t windowLINES, size_t windowCOLS);
        void moveLeft(size_t windowCOLS);
        void moveRight(size_t windowCOLS);
        void moveRightInsertMode(size_t windowCOLS);



        Posn getPosn() const;
        size_t getScrollOffset() const;

        const Triple &getCurrentChar() const  { return currentChar; }

        int getActualX() const { return actualX; }

        void updateCOLS(int newCOLS) { oldCOLS = newCOLS; }
        void updateLINES(int newLINES) { curLINES = newLINES; }
        void updateDocumentTriple();

        bool isCursorHovering() const;





    };




}


# endif