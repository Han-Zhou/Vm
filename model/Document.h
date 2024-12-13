#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>

#include "../utils/TextWrapper.h"
#include "../structs/Triple.h"
#include "../structs/Keys.h"

using namespace std;

namespace mode {
    class InsertMode;
}


namespace model {

    class Document {
        vector<string> lines;
        vector<vector<string>> wrapped_lines;

        // indicates line, subline, and index
        // exactly the same as the triple in Cursor
        Triple currentCursorChar = {0, 0, 0};


        // determines the total number of wrapped lines in the document
        size_t howManyWrappedLines = 0;

        void read_file(const string &filename);

        size_t curWidth = 1;

        // set of functions that allows us to tell what kind of character the cursor is pointing to
        bool isWhitespace(int ch);
        bool isPunctuation(int ch);
        bool isAlphabet(int ch);
        
        bool atEndOfDocument(int &currentLine, int &currentCharIndex);
        void moveForwardOneChar(int &currentLine, int &currentCharIndex);
        bool atBeginOfDocument(int &currentLine, int &currentCharIndex);
        void moveBackOneChar(int &currentLine, int &currentCharIndex);


        


    public:

    friend class mode::InsertMode;


        Document(const string &filename);
        Document(Document &&d) = delete;
        Document &operator=(const Document &d) = delete;
        Document &operator=(Document &&d) = delete;


        const vector<string> &getLines() const;

        void wrap(size_t width);
        vector<vector<string>> &createWrappedLines(size_t width);
        const vector<vector<string>> &fetchWrappedLines() const;
        size_t getLinesSize() const;
        size_t getWrappedLinesSize() const;


        void updateTriple(const Triple &t);
        const Triple &getTriple() const;


        void insertChar(int ch);
        // void deleteChar();
        void deleteChar(const Triple &t);


        // changes wrapped lines according to lines
        void updateWrappedLines();

        // // moving up, down, left, right, right in insert
        // void moveUp(size_t windowCOLS);
        // void moveDown(size_t windowLINES, size_t windowCOLS);
        // void moveLeft(size_t windowCOLS);
        // void moveRight(size_t windowCOLS);
        // void moveRightInsertMode(size_t windowCOLS);

        // add a line below the current line
        void addLineBelow();
        void addLineAbove();

        void moveToFrontOfLine();
        void moveToFirstCharOfLine();
        void moveToEndOfLine();

        void moveToNextWord(); 
        void moveToNextNonWhitespace();
        void moveToPrevWord();
        void moveToPrevNonWhitespace();


        // these functions return the deleted text for yanking and pasting
        string deleteCurrentLine();
        // deletes every character in [start, finish)
        string deleteRange(const Triple &start, const Triple &end);

        string getTextInRange(const Triple &start, const Triple &end);
        string getLineText(int line);

        // insert text after the current cursor position
        void insertTextAfter(vector<string> &text);
        // insert text before the current cursor position
        void insertTextBefore(vector<string> &text);







    };
}


# endif