#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <iostream>

#include "../model/Document.h"
#include "../view/Window.h"
#include "../view/Cursor.h"



namespace controller {

    class MainController {
        model::Document &document;
        view::Window &window;
        view::Cursor &cursor;


    public:
        MainController(model::Document &document, view::Window &window, view::Cursor &cursor): document{document}, window{window}, cursor{cursor} {};

        MainController(const MainController &m) = delete;
        MainController(MainController &&m) = delete;
        MainController &operator=(const MainController &m) = delete;
        MainController &operator=(MainController &&m) = delete;


        string processInput();

























    };
}










#endif



