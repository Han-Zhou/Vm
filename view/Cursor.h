# ifndef CURSOR_H
# define CURSOR_H


#include <ncurses.h>
#include <iostream>

#include "../structs/Posn.h"
// #include "../view/Window.h"
#include "../model/Document.h"



namespace view {

    class Cursor {
        Posn posn;
        // Window &window;
        model::Document &document;
        size_t scrollOffset = 0;

        // keeps track of which column should the cursor point to after moving up or down
        int actualX = 0; 

    public:

        Cursor(int x, int y, model::Document &document) : posn{x, y}, document{document} {
            cout << "Cursor created" << endl;
        }

        Cursor(const Cursor &c) = delete;
        Cursor(Cursor &&c) = delete;
        Cursor &operator=(const Cursor &c) = delete;
        Cursor &operator=(Cursor &&c) = delete;

        void moveUp();
        void moveDown(size_t windowLINES);
        void moveLeft();
        void moveRight(size_t windowCOLS);

        void moveCursor(int x, int y);


        Posn getPosn() const;
        size_t getScrollOffset() const;






    };




}


# endif