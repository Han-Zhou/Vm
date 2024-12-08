#include "Document.h"

using namespace std;

namespace model {

        void Document::read_file(const string &filename) {
            cout << "Reading file: " << filename << endl;
            ifstream file(filename);
            file >> noskipws;
            string line;
            char ch;
            while (file.get(ch)) {
                // cout << line << endl;
                if (ch == '\n') {
                    line += ch;
                    lines.push_back(line);
                    // cout << "Line: " << line << endl;
                    line = "";
                }
                else {
                    line += ch;
                }
            }
            // cout << "Done reading 31file" << endl;
        }


        Document::Document(const string &filename) {
            read_file(filename);
        }

      

        void Document::wrap(size_t width) {
            wrapped_lines.clear();
            
            utils::TextWrapper tw;
            wrapped_lines = tw.wrapText(lines, width);
            howManyWrappedLines = 0;

            for (int i = 0; i < wrapped_lines.size(); ++i) {
                howManyWrappedLines += wrapped_lines[i].size();
            }
        }


        vector<vector<string>> &Document::createWrappedLines(size_t width) {
            curWidth = width;
            wrap(width);
            return wrapped_lines;
        }

        const vector<vector<string>> &Document::fetchWrappedLines() const {
            return wrapped_lines;
        }


        size_t Document::getLinesSize() const {
            return lines.size();
        }

        size_t Document::getWrappedLinesSize() const {
            return howManyWrappedLines;
        }

        void Document::updateTriple(const Triple &t) {
            currentCursorChar.line = t.line;
            currentCursorChar.subLine = t.subLine;
            currentCursorChar.index = t.index;
        }


        void Document::updateWrappedLines() {
            wrap(curWidth);
        }












}


