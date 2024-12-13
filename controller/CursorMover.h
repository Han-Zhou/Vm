#ifndef CURSORMOVER_H
#define CURSORMOVER_H

#include "../model/Document.h"
#include "../view/Cursor.h"
#include "../view/Window.h"
#include "../structs/Keys.h"
#include "../structs/Triple.h"



namespace controller {

    // moves the cursor on the window
    class CursorMover {
        model::Document &document;
        view::Cursor &cursor;
        view::Window &window;

        
    public:


        CursorMover(model::Document &document, view::Cursor &cursor, view::Window &window): document{document}, cursor{cursor}, window{window} {}

        void moveUp(int multiplier = 1);
        void moveDown(int multiplier = 1);
        void moveLeft(int multiplier = 1);
        void moveRight(int multiplier = 1);

        // moves the cursor to the right by one character
        // This is special as it allows the cursor to not necessarily point to a character
        // only allowed in insertmode and when normal mode turns to insert mode
        void moveCursorRightInsertMode(int multiplier = 1);

        void moveToFrontOfLine();
        void moveToFirstCharOfLine();
        void moveToEndOfLine();


        void moveToNextWord(int multiplier = 1);
        void moveToNextNonWhitespace(int multiplier = 1);
        void moveToPrevWord(int multiplier = 1);
        void moveToPrevNonWhitespace(int multiplier = 1);





        void updateCursorTriple(const Triple &t);

        // once a change to the document triple has been made, we need to update the cursor
        void updateCursor();

    };
}












#endif