#include "Window.h"




namespace view {

    // Initialize the singleton instance to nullptr
    unique_ptr<Window> Window::instance = nullptr;
        


    Window::~Window() {
        delwin(win);
        endwin();
        cout << "Window destroyed" << endl;
        // delete cursor;
    }

    // Static signal handler for window resizing
    void Window::handle_resize(int sig) {
        if (instance) {
            endwin();
            refresh();


            // ofstream log("log3", ios_base::app);
            // log << "Resizing window" << endl;
            int newCOLS, newLINES;
            getmaxyx(stdscr, newLINES, newCOLS);
            // log << "New standard window size: " << newLINES << " lines and " << newCOLS << " columns" << endl;
            // int a, b;
            // getmaxyx(instance->win, a, b);
            // log << "Winow size: " << a << " lines and " << b << " columns" << endl;

            instance->resize(newCOLS, newLINES); // Trigger the resize logic in the singleton instance
        }
    }


    // Static method to access the singleton instance
    Window& Window::getInstance(model::Document &document, Cursor &cursor) {
        if (!instance) {
            instance = make_unique<Window>(document, cursor);
        }
        return *instance;
    }


    void Window::init() {
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




    void Window::run() {
        const vector<string> &wrappedContent = document.getWrappedLines(COLS);

        // clear();
        display_file(wrappedContent);
        display_cursor();
        refresh(); 
    }




    // assumes that wrappedLines has been read from a file and has lines of appropriate length
    // i.e. has been formatted correctly to wrap around the window
    void Window::display_file(const vector<string> &wrappedLines) {
        // Clear the window
        clear();
        // int row = 0;
        scrollOffset = cursor.getScrollOffset();

        size_t end = std::min(scrollOffset + LINES, wrappedLines.size());
        for (size_t i = scrollOffset; i < end; ++i) {
            mvprintw(i - scrollOffset, 0, wrappedLines[i].c_str());
        }
    }



    void Window::display_cursor() {
        move(cursor.getPosn().y, cursor.getPosn().x);
    }






    int Window::getChar() {
        return getch();
    }


    size_t Window::getLINES() const {
        return LINES;
    }

    size_t Window::getCOLS() const {
        return COLS;
    }



    void Window::resize(size_t newCOLS, size_t newLINES) {
        win = newwin(newLINES, newCOLS, 0, 0);
        // ofstream log("log2", ios_base::app);
        clear();
        // wresize(win, newLINES, newCOLS);
        // log << "Resized window to " << newLINES << " lines and " << newCOLS << " columns" << endl;

        // int a, b;
        // getmaxyx(stdscr, a, b);
        // log << "standard screen size: " << a << " lines and " << b << " columns" << endl;



        run();
    }

    // void Window::refresh() {
    //     wrefresh(win);
    // }









}

