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
        vector<string> wrapped_lines;
    public:

        Document(const string &filename);

        
        Document(Document &&d) = delete;
        Document &operator=(const Document &d) = delete;
        Document &operator=(Document &&d) = delete;


        void wrap(size_t width);
        vector<string> getWrappedLines(size_t width);
        vector<string> fetchWrappedLines() const;
        size_t getLinesSize() const;
        size_t getWrappedLinesSize() const;






    };
}


# endif