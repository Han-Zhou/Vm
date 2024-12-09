#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <iostream>
#include <memory>

#include "../model/Document.h"
#include "../view/Window.h"
#include "../view/Cursor.h"

#include "CursorMover.h"

#include "../mode/Mode.h"
#include "../mode/InsertMode.h"
#include "../mode/NormalMode.h"

#include "../structs/ReturnMessage.h"


namespace controller {

    class MainController {
        model::Document &document;
        view::Window &window;
        view::Cursor &cursor;

        CursorMover cursorMover;

        mode::Mode *currentMode;

        unique_ptr<mode::InsertMode> insert_mode;
        unique_ptr<mode::NormalMode> normal_mode;

        vector<int> inputBuffer;

        bool justResized = false;



    public:
        MainController(model::Document &document, view::Window &window, view::Cursor &cursor): document{document}, window{window}, cursor{cursor}, cursorMover{document, cursor, window} {

            insert_mode = make_unique<mode::InsertMode>(document, cursorMover);
            normal_mode = make_unique<mode::NormalMode>(document, cursorMover);

            // currentMode = insert_mode.get();
            currentMode = normal_mode.get();
        }

        MainController(const MainController &m) = delete;
        MainController(MainController &&m) = delete;
        MainController &operator=(const MainController &m) = delete;
        MainController &operator=(MainController &&m) = delete;


        ReturnMessage processInput();

























    };
}










#endif

