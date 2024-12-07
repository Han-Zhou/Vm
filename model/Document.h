#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <memory>

#include "../utils/FileReader.h"
#include "../utils/TextWrapper.h"

using namespace std;

namespace model {

    class Document {
        vector<string> lines;
        vector<vector<string>> wrapped_lines;

        // determines the total number of wrapped lines in the document
        size_t howManyWrappedLines = 0;

    public:

        Document(const string &filename);

        
        Document(Document &&d) = delete;
        Document &operator=(const Document &d) = delete;
        Document &operator=(Document &&d) = delete;


        void wrap(size_t width);
        vector<vector<string>> &createWrappedLines(size_t width);
        const vector<vector<string>> &fetchWrappedLines() const;
        size_t getLinesSize() const;
        size_t getWrappedLinesSize() const;






    };
}


# endif