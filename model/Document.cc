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

        const Triple &Document::getTriple() const {
            return currentCursorChar;
        }


        void Document::updateWrappedLines() {
            wrap(curWidth);
        }


        void Document::addLineBelow() {
            int currentLine = currentCursorChar.line;
            string newLine = "\n";
            lines.insert(lines.begin() + currentLine + 1, newLine);
            updateWrappedLines();
        }

        
        void Document::addLineAbove() {
            int currentLine = currentCursorChar.line;
            string newLine = "\n";
            lines.insert(lines.begin() + currentLine, newLine);
            currentCursorChar.line++;
            updateWrappedLines();
        }


        void Document::moveToFrontOfLine() {
            currentCursorChar.subLine = 0;
            currentCursorChar.index = 0;
        }


        void Document::moveToFirstCharOfLine() {
            int firstCharIndex = 0;
            for (int i = 0; i < lines[currentCursorChar.line].size(); ++i) {
                if (lines[currentCursorChar.line][i] != ' ') {
                    firstCharIndex = i;
                    break;
                }
                // if the line is only spaces, then we move to the end of the line
                if (i == lines[currentCursorChar.line].size() - 1) {
                    firstCharIndex = i;
                }
            }
            currentCursorChar.subLine = firstCharIndex / curWidth;
            currentCursorChar.index = firstCharIndex % curWidth;

        }


        void Document::moveToEndOfLine() {
            int endIndex = lines[currentCursorChar.line].size() - 1;
            currentCursorChar.subLine = endIndex / curWidth;
            currentCursorChar.index = std::max(0, static_cast<int>(endIndex % curWidth - 1));
        }












}


