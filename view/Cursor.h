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

        // keeps track of where the cursor is pointing to in the vector<vector<string>> wrappedLines. Here y and x don't represent coordinates 
        // i.e. it determines which part of the document the cursor is pointing to.
        // for example, if the current cursor position is pointing to the character wrappedLines[0][1][2], then currentChar = {0, 1, 2}
        Triple currentChar = {0, 0, 0};

        void updateNewTriple(size_t newLINES, size_t newCOLS);
 


    public:

        Cursor(int x, int y, model::Document &document, int COLS) : posn{x, y}, document{document}, oldCOLS{COLS} {
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

        void moveCursor(int x, int y);


        Posn getPosn() const;
        size_t getScrollOffset() const;

        const Triple &getCurrentChar() const  { return currentChar; }

        int getActualX() const { return actualX; }

        void updateCOLS(int newCOLS) { oldCOLS = newCOLS; }





    };




}


# endif