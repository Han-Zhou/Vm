#ifndef HOLYVMEDITOR_H
#define HOLYVMEDITOR_H


#include <memory>
#include <iostream>

#include "view/Window.h"
#include "model/Document.h"
#include "controller/MainController.h"
#include "view/Cursor.h"


using namespace std;




class HolyVmEditor {
    
    unique_ptr<model::Document> document;
    unique_ptr<view::Cursor> cursor;
    view::Window &window;
    unique_ptr<controller::MainController> controller;


public: 

    HolyVmEditor(const string &filename): 
        document{make_unique<model::Document>(filename)}, cursor{make_unique<view::Cursor>(0, 0, *document)},
        window{view::Window::getInstance(*document, *cursor)} {

        cout << "Creating HolyVmEditor" << endl;


        // view::Window windowInst = view::Window::getInstance(*document);
        controller = make_unique<controller::MainController>(*document, window, *cursor);
        cout << "HolyVmEditor created" << endl;
    }

    void run();

    ~HolyVmEditor() {
        // unique_ptr will automatically delete the window
        cout << "Destroying HolyVmEditor" << endl;
    }

    HolyVmEditor(const HolyVmEditor &h) = delete;
    HolyVmEditor(HolyVmEditor &&h) = delete;
    HolyVmEditor &operator=(const HolyVmEditor &h) = delete;
    HolyVmEditor &operator=(HolyVmEditor &&h) = delete;
};



#endif

