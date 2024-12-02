#include <ncurses.h>
#include <fstream>
#include <string>
#include <sstream>
#include <csignal>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;




namespace view {

class Window {

    // size_t height;
    // size_t width;

    WINDOW * win;

    size_t scrollOffset = 0;


    

public:

    // static void handle_resize(int sig) {
    //     endwin();
    //     refresh();
    //     clear();
    //     int nh, nw;
    //     getmaxyx(win, nh, nw);
    //     win = newwin(nh, nw, 0, 0);
    // }

    Window() {
        // // initializes ncurses
        // initscr();

        // // disables character buffering
        // cbreak();

        // // disables echoing of characters
        // noecho();

        // keypad(stdscr, TRUE); // Enable special keys

        // // signal(SIGWINCH, handle_resize);

        // win = newwin(LINES, COLS, 0, 0);
    }


    
    ~Window() {
        delwin(win);
        endwin();
    }



    void run(const vector<string> &wrappedContent) {
        // initializes ncurses
        initscr();

        // disables character buffering
        cbreak();

        // disables echoing of characters
        noecho();

        keypad(stdscr, TRUE); // Enable special keys

        // signal(SIGWINCH, handle_resize);

        win = newwin(LINES, COLS, 0, 0);

        
        display_file(wrappedContent);

        int ch;
        while ((ch = getch()) != 'q') { // Press 'q' to quit
            switch (ch) {
                case KEY_UP:
                    if (scrollOffset > 0) scrollOffset--;
                    break;
                case KEY_DOWN:
                    if (scrollOffset + LINES < wrappedContent.size()) scrollOffset++;
                    break;
                default:
                    break;
            }
            display_file(wrappedContent);
        }
    }




    // assumes that wrappedLines has been read from a file and has lines of appropriate length
    // i.e. has been formatted correctly to wrap around the window
    void display_file(const vector<string> &wrappedLines) {
        // Clear the window
        wclear(win);
        // int row = 0;

            
        size_t end = std::min(scrollOffset + LINES, wrappedLines.size());
        for (size_t i = scrollOffset; i < end; ++i) {
            mvprintw(i - scrollOffset, 0, wrappedLines[i].c_str());
        }
        wrefresh(win);


      



        // for (const string &line : v) {
        //     mvwprintw(win, row++, 0, "%s", line.c_str());


            // If we reach the end of the window, pause and wait for user input
        //     if (row >= LINES) {
        //         mvwprintw(win, row, 0, "-- More -- Press any key to continue...");
        //         refresh();
        //     }
        // }


    }









    size_t getLINES() const {
        return LINES;
        cout << "LINES: " << LINES << endl;
    }

    size_t getCOLS() const {
        return COLS;
        cout << "COLS: " << COLS << endl;
    }



    void resize(size_t newCOLS, size_t newLINES) {
        wresize(win, newLINES, newCOLS);
    }

    void refresh() {
        wrefresh(win);
    }



    





};


}

