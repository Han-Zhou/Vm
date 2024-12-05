#include "TextWrapper.h"

namespace utils {

    vector<vector<string>> TextWrapper::wrapText(const vector<string> text, size_t maxWidth) {

        ofstream log("log");
        vector<string> wrappedLines;

        for (const string &line : text) {
            // log << "Line: " << line << endl;
            istringstream stream(line);
            stream >> std::noskipws;
            // log << "stream: " << stream.str() << endl;
            // string word;
            string currentLine;


            // while (stream >> word) {
            //     log << "Word: " << word << endl;
            //     // If adding the next word exceeds the line width
            //     if (currentLine.length() + word.length() + 1 > maxWidth) {
            //         wrappedLines.push_back(currentLine); // Save the current line
            //         log << "Wrapped Line: " << currentLine << endl;
            //         currentLine = word; // Start a new line
            //     } else {
            //         // Add a space if the line isn't empty
            //         // if (!currentLine.empty()) {
            //         //     currentLine += " ";
            //         // }
            //         currentLine += word;
            //     }
            // }

            char ch;
            while (stream >> ch) {
                if (ch == '\n') {
                    if (currentLine.length() == 0) {
                        wrappedLines.push_back("");
                        continue;
                    }
                    wrappedLines.push_back(currentLine);
                    // log << "Wrapped Line: " << currentLine << endl;
                    currentLine = "";
                } else if (currentLine.length() + 2 > maxWidth) {
                    wrappedLines.push_back(currentLine);
                    // log << "Wrapped Line: " << currentLine << endl;
                    currentLine = ch;
                } else {
                    currentLine += ch;
                }
            }

            // Add the last line if there's any remaining text
            if (currentLine.length() != 0) {
                // log << "Wrapped Line: " << currentLine << endl; 
                wrappedLines.push_back(currentLine);
            }
        }

        log << "Wrapped Lines: " << endl;
        for (string &s : wrappedLines) {
            log << s << endl;
        }


        return wrappedLines;
    }

    
}

