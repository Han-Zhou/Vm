#include <ncurses.h>
#include <fstream>
#include <string>
#include <sstream>
#include <csignal>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;


WINDOW * windowForResize;

class Window;

// void handle_resize(int sig) {
//     clear();
//     int nh, nw;
//     getmaxyx(window, nh, nw);
//     resize(nw, nh);
//     refresh();
// }



namespace view {

class Window {

    // size_t height;
    // size_t width;

    WINDOW * win;   

    // Singleton instance
    static unique_ptr<Window> instance;

    size_t scrollOffset = 0;
    

public:


    Window() {
        // initializes ncurses
        initscr();

        // disables character buffering
        cbreak();

        // disables echoing of characters
        noecho();

        keypad(stdscr, TRUE); // Enable special keys

        // signal(SIGWINCH, handle_resize);

        win = newwin(LINES, COLS, 0, 0);

        signal(SIGWINCH, handle_resize);
    }


    // Static signal handler for window resizing
    static void handle_resize(int sig) {
        if (instance) {
            int newCOLS, newLINES;
            getmaxyx(instance->win, newLINES, newCOLS);
            instance->resize(newCOLS, newLINES); // Trigger the resize logic in the singleton instance
        }
    }

    
    ~Window() {
        delwin(win);
        endwin();
    }



    // Static method to access the singleton instance
    static Window& getInstance() {
        if (!instance) {
            instance = make_unique<Window>();
        }
        return *instance;
    }




    void run(const vector<string> &wrappedContent) {

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
        clear();
        wresize(win, newLINES, newCOLS);
        refresh();
    }

    void refresh() {
        wrefresh(win);
    }






};


// Initialize the singleton instance to nullptr
unique_ptr<Window> Window::instance = nullptr;



}

