#include "Window.h"
#include <cstring>




namespace view {

    // Initialize the singleton instance to nullptr
    unique_ptr<Window> Window::instance = nullptr;
        


    Window::~Window() {
        // attroff(COLOR_PAIR(1));
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

        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);

        // disables character buffering
        cbreak();

        // disables echoing of characters
        noecho();

        keypad(stdscr, TRUE); // Enable special keys

        win = newwin(LINES, COLS, 0, 0);
        cursor.updateCOLS(COLS);
        
        signal(SIGWINCH, handle_resize);

        // attron(COLOR_PAIR(1));
    }




    void Window::run() {
        // COLS = 8;

        const vector<vector<string>> &wrappedContent = document.createWrappedLines(COLS);

        if (resized) {
            resized = false;
            cursor.adjustCursor(LINES, COLS);
        }
        clear();
        display_file(wrappedContent);
        display_cursor();

        // mvprintw(20, 10, "COLS: %d; LINES: %d", COLS, LINES);
        // mvprintw(21, 10, "MaxWrappedSublineSize: %d", document.fetchWrappedLines()[0][0].size());

        refresh(); 
    }




    // assumes that wrappedLines has been read from a file and has lines of appropriate length
    // i.e. has been formatted correctly to wrap around the window
    void Window::display_file(const vector<vector<string>> &wrappedLines) {
        // Clear the window
        clear();
        // int row = 0;
        scrollOffset = cursor.getScrollOffset();

        // Flatten the wrapped lines so we can easily print from scrollOffset
        vector<string> flatLines;
        flatLines.reserve(document.getWrappedLinesSize());

        for (size_t i = 0; i < wrappedLines.size(); i++) {
            for (size_t j = 0; j < wrappedLines[i].size(); j++) {
                flatLines.push_back(wrappedLines[i][j]);
            }
        }

        ofstream log("log2", ios_base::app);
        // log << "displaying file" << endl;
        int end = std::min(scrollOffset + LINES - 1, document.getWrappedLinesSize());
        
        int currentLine = scrollOffset;

        for (int i = scrollOffset; i < end; ++i) {
            mvprintw(i - scrollOffset, 0, flatLines[i].c_str());
        }
        display_status_bar();
    }



    void Window::display_cursor() {

        ofstream log("log", ios_base::app);

        const Triple &currentChar = cursor.getCurrentChar();
        
        move(cursor.getPosn().y, cursor.getPosn().x);
    }





    void Window::display_status_bar() {
        int height = LINES;
        int width = COLS;

        // Prepare status messages
        std::string leftStatus;
        if (mode == "insert") {
            leftStatus = "-- INSERT --";
        } 

        // Get cursor position (1-based for nicer display)
        int row = cursor.getPosn().y + 1;
        int col = cursor.getPosn().x + 1;
        char rightStatus[20];
        snprintf(rightStatus, sizeof(rightStatus), "Ln %d, Col %d", row, col);

        attron(COLOR_PAIR(1) | A_BOLD);

        // the status bar will be at height - 1
        move(height - 1, 0);

        // Clear the line
        clrtoeol();

        // Print the left status
        mvprintw(height - 1, 0, "%s", leftStatus.c_str());

        // Print the right status aligned to the right
        // First determine where to start printing the right status
        int rightStart = width - (int)strlen(rightStatus);

        if (rightStart < (int)leftStatus.size() + 1) {
            rightStart = (int)leftStatus.size() + 1;
        }
        
        mvprintw(height - 1, rightStart, "%s", rightStatus);

        attroff(COLOR_PAIR(1) | A_BOLD);
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
        clear();
        resized = true;
        run();
    }


    void Window::changeMode(string newMode) {
        mode = newMode;
    }










}

