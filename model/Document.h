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

        // exactly the same as the triple in Cursor
        Triple currentCursorChar = {0, 0, 0};


        // determines the total number of wrapped lines in the document
        size_t howManyWrappedLines = 0;

        void read_file(const string &filename);

        size_t curWidth = 1;


    public:

    friend class mode::InsertMode;

        Document(const string &filename);

        
        Document(Document &&d) = delete;
        Document &operator=(const Document &d) = delete;
        Document &operator=(Document &&d) = delete;


        void wrap(size_t width);
        vector<vector<string>> &createWrappedLines(size_t width);
        const vector<vector<string>> &fetchWrappedLines() const;
        size_t getLinesSize() const;
        size_t getWrappedLinesSize() const;


        void updateTriple(const Triple &t);
        const Triple &getTriple() const;


        void insertChar(int ch);
        void deleteChar();


        // changes lines according to wrapped lines
        void updateWrappedLines();


        // add a line below the current line
        void addLineBelow();
        void addLineAbove();

        void moveToFrontOfLine();
        void moveToFirstCharOfLine();
        void moveToEndOfLine();







    };
}


# endif