#include "Window.h"




namespace view {

    // Initialize the singleton instance to nullptr
    unique_ptr<Window> Window::instance = nullptr;
        


    Window::~Window() {
        attroff(COLOR_PAIR(1));
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

        attron(COLOR_PAIR(1));
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
        int end = std::min(scrollOffset + LINES, document.getWrappedLinesSize());
        
        int currentLine = scrollOffset;

        for (int i = scrollOffset; i < end; ++i) {
            mvprintw(i - scrollOffset, 0, flatLines[i].c_str());
        }

        


        // for (int i = scrollOffset; i < end;) {
        //     for (int j = 0; (j < wrappedLines[currentLine].size()) && (i < end); ++j, ++i) {
        //         mvprintw(i - scrollOffset, 0, wrappedLines[currentLine][j].c_str());
        //         // log << "i: " << i << "j: " << j << "|" << wrappedLines[currentLine][j] << endl;
        //     }
        //     currentLine++;
        //     // mvprintw(i - scrollOffset, 0, wrappedLines[i].c_str());
        // }
    }



    void Window::display_cursor() {

        ofstream log("log", ios_base::app);
        log << "New y: " << cursor.getPosn().y << "; New x: " << cursor.getPosn().x << endl;
        log << "COLS: " << COLS << "; LINES: " << LINES << endl;

        const Triple &currentChar = cursor.getCurrentChar();
        log << "currentChar.line: " << currentChar.line << endl;
        log << "currentChar.subLine: " << currentChar.subLine << endl;
        log << "currentChar.index: " << currentChar.index << endl;
        log << "actualX: " << cursor.getActualX() << endl;
        log << "linesSize: " << document.getLinesSize() << endl;
        log << "scrollOffset: " << cursor.getScrollOffset() << endl;

        // mvprintw(22, 25, "New y: %d; New x: %d", cursor.getPosn().y, cursor.getPosn().x);
        // mvprintw(23, 25, "COLS: %d; LINES: %d", COLS, LINES);

        // const Triple &currentChar = cursor.getCurrentChar();
        // mvprintw(24, 25, "currentChar.line: %d", currentChar.line);
        // mvprintw(25, 25, "currentChar.subLine: %d", currentChar.subLine);
        // mvprintw(26, 25, "currentChar.index: %d", currentChar.index);
        // mvprintw(27, 25, "actualX: %d", cursor.getActualX());
        // mvprintw(28, 25, "linesSize: %d", document.getLinesSize());
        // mvprintw(29, 25, "scrollOffset: %d", cursor.getScrollOffset());    
        
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
        clear();
        resized = true;
        run();
    }










}

