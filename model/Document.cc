#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "../utils/FileReader.h"
#include "../utils/TextWrapper.h"

using namespace std;


class Document {
    vector<string> lines;
    vector<string> wrapped_lines;
public:

    Document(const string &filename) {
        // read the file
        cout << "Reading file: " << filename << endl;
        utils::FileReader fr;
        lines = fr.read_file(filename);
    }

    Document(const Document &d) = delete;
    Document(Document &&d) = delete;
    Document &operator=(const Document &d) = delete;
    Document &operator=(Document &&d) = delete;


    void wrap(size_t width) {
        wrapped_lines.clear();
        
        utils::TextWrapper tw;
        wrapped_lines = tw.wrapText(lines, width);
    }


    vector<string> getWrappedLines(size_t width) {
        wrap(width);
        return wrapped_lines;
    }






};
