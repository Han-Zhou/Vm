# ifndef WINDOW_H
# define WINDOW_H


#include <ncurses.h>
#include <fstream>
#include <string>
#include <sstream>
#include <csignal>
#include <iostream>
#include <memory>
#include <vector>
#include <signal.h>

#include "../model/Document.h"
#include "Cursor.h"

using namespace std;





namespace view {

class Window {

    WINDOW * win;   
    // Cursor * cursor;
    model::Document &document;
    Cursor &cursor;


    // Singleton instance
    static unique_ptr<Window> instance;

    size_t scrollOffset = 0;
    bool resized = false;
    

public:

    // friend class Cursor;

    friend class MainController;

    WINDOW * getWin() {
        return win;
    }


    Window(model::Document &document, Cursor &cursor): document{document}, cursor{cursor} { };
    ~Window();

    // Static signal handler for window resizing
    static void handle_resize(int sig);
    // Static method to access the singleton instance
    static Window& getInstance(model::Document &document, Cursor &cursor);


    void init();
    void run();
    void display_file(const vector<vector<string>> &wrappedLines);
    void display_cursor();




    int getChar();

    size_t getLINES() const;
    size_t getCOLS() const;
    void resize(size_t newCOLS, size_t newLINES);
    // void refresh();






};

}







# endif