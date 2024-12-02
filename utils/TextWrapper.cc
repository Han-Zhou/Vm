#include "TextWrapper.h"

namespace utils {

    vector<string> TextWrapper::wrapText(const vector<string> text, size_t maxWidth) {
        vector<string> wrappedLines;
        for (const string &line : text) {
            istringstream stream(line);
            string word;
            string currentLine;

            while (stream >> word) {
                // If adding the next word exceeds the line width
                if (currentLine.length() + word.length() + 1 > maxWidth) {
                    wrappedLines.push_back(currentLine); // Save the current line
                    currentLine = word; // Start a new line
                } else {
                    // Add a space if the line isn't empty
                    if (!currentLine.empty()) {
                    currentLine += " ";
                    }
                    currentLine += word;
                }
            }

            // Add the last line if there's any remaining text
            if (!currentLine.empty()) {
            wrappedLines.push_back(currentLine);
            }
        }
        return wrappedLines;
    }

    
}

