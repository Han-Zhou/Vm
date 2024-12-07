#include "TextWrapper.h"

namespace utils {

    vector<vector<string>> TextWrapper::wrapText(const vector<string> text, size_t maxWidth) {

        ofstream log("log");
        vector<vector<string>> wrappedLines;

        for (const string &line : text) {

            // currentWrappedLine is line but wrapped
            vector<string> currentWrappedLine;

            istringstream stream(line);
            stream >> std::noskipws;
            string currentLine;

            char ch;
            while (stream >> ch) {
                if (ch == '\n') {
                    // line is only a newline character, nothing more
                    if (currentLine.length() == 0) {
                        currentWrappedLine.push_back("");
                        break;
                    }
                    // else the line is over
                    currentWrappedLine.push_back(currentLine);
                    currentLine = "";
                } else if (currentLine.length() + 2 > maxWidth) {
                    currentWrappedLine.push_back(currentLine);
                    currentLine = ch;
                } else {
                    currentLine += ch;
                }
            }

            // Add the last line if there's any remaining text
            if (currentLine.length() != 0) {
                currentWrappedLine.push_back(currentLine);
            }

            wrappedLines.push_back(currentWrappedLine);
        }

        // for (int i = 0; i < wrappedLines.size(); ++i) {
        //     for (int j = 0; j < wrappedLines[i].size(); ++j) {
        //         log << wrappedLines[i][j] << endl;
        //     }
        // }



        return wrappedLines;
    }

    
}

