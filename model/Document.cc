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



        bool Document::isWhitespace(int ch) {
            return (ch == ' ');
        }

        bool Document::isPunctuation(int ch) {
            return (ch >= 33 && ch <= 47) || (ch >= 58 && ch <= 64) || (ch >= 91 && ch < 95) || (ch == 96) || (ch >= 123 && ch <= 126);
        }

        bool Document::isAlphabet(int ch) {
            return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch == 95) || (ch >= 48 && ch <= 57);
        }

        bool Document::atEndOfDocument(int &currentLine, int &currentCharIndex) {
            if ((currentLine == (int)lines.size() - 1) && (currentCharIndex == (int)lines.back().size() - 1)) {
                return true;
            }
            if (currentLine == (int)lines.size()) {
                currentLine--;
                currentCharIndex = lines[currentLine].size() - 1;
                return true;
            }
            return false;
        }




        // for traversing moveToNextWord and moveToNextNonWhitespace
        // NOTE may make this into a new version of moveRight for cursor
        void Document::moveForwardOneChar(int &currentLine, int &currentCharIndex) {
            // Attempt to move one character forward in the document.
            // If at the end of a line, move to the start of the next line, if available.
            if (currentLine < lines.size()) {
                // need to skip the newLinecharacter in the end
                if (currentCharIndex < (int)lines[currentLine].size() - 2) {
                    currentCharIndex++;
                } 
                else {
                    // move to the next line start 
                    if (currentLine < (int)lines.size() - 1) {
                        currentLine++;
                        currentCharIndex = 0;
                    }
                }
            }
            if (currentLine == lines.size()) {
                currentLine--;
                currentCharIndex = max((int)lines[currentLine].size() - 1, 0);
            }
        }



        // =================================================================================================



        void Document::moveToNextWord() {

            if (atEndOfDocument(currentCursorChar.line, currentCursorChar.index)) { // we are at the end of file. Don't do anything
                return;
            }

            int currentLine = currentCursorChar.line;
            int currentSubLine = currentCursorChar.subLine;
            int currentIndex = currentCursorChar.index;

            int currentCharIndex = currentSubLine * curWidth + currentIndex;

            // define a lambda to access characters more easily
            auto getChar = [&](int line, int chIndx) -> char {
                    return lines[line][chIndx];
            };

            char curCh = getChar(currentLine, currentCharIndex);

            // case 1: we are at a whitespace character or newline character
            if ((isWhitespace(curCh)) || (curCh == '\n')) {
                if (curCh == '\n') {
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }
                // we first skip all the whitespace characters
                while (isWhitespace(curCh) && (!atEndOfDocument(currentLine, currentCharIndex))) {
                    int prevLine = currentLine;
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we are either: 
                // 1) at the end of the document
                // 2) at a non-whitespace character
                // either of those cases, we are done
            }
            
            // case 2: we are on a punctuation character
            else if (isPunctuation(curCh)) {
                // first we skip all the punctuation characters (if there are any)
                while (isPunctuation(curCh) && (!atEndOfDocument(currentLine, currentCharIndex))) {
                    int prevLine = currentLine;
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if (prevLine != currentLine) {
                        break;
                    }
                }

                // mext we skip all the whitespace characters (if there are any)
                while (isWhitespace(curCh) && (!atEndOfDocument(currentLine, currentCharIndex))) {
                    int prevLine = currentLine;
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if ((prevLine != currentLine) && (curCh == '\n')) {
                        break;
                    }
                }

                // we are either:
                // 1) at the end of the document
                // 2) at a non-whitespace character
                // either of those cases, we are done
            }

            else {
                // case 3: we are on an alphabet character
                // we first skip all the alphabet characters
                while (isAlphabet(curCh) && (!atEndOfDocument(currentLine, currentCharIndex))) {
                    int prevLine = currentLine;
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if (prevLine != currentLine) {
                        break;
                    }
                }

                // next, we skip all the whitespace characters
                while (isWhitespace(curCh) && (!atEndOfDocument(currentLine, currentCharIndex))) {
                    int prevLine = currentLine;
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if ((prevLine != currentLine) && (curCh == '\n')) {
                        break;
                    }
                }

                // we are either:
                // 1) at the end of the document
                // 2) at a non-whitespace character
                // either of those cases, we are done
            }

            currentCursorChar.line = currentLine;
            currentCursorChar.subLine = currentCharIndex / curWidth;
            currentCursorChar.index = currentCharIndex % curWidth;
            return;
        }




        void Document::moveToNextNonWhitespace() {
            if (atEndOfDocument(currentCursorChar.line, currentCursorChar.index)) { // we are at the end of file. Don't do anything
                return;
            }

            int currentLine = currentCursorChar.line;
            int currentSubLine = currentCursorChar.subLine;
            int currentIndex = currentCursorChar.index;

            int currentCharIndex = currentSubLine * curWidth + currentIndex;

            // define a lambda to access characters more easily
            auto getChar = [&](int line, int chIndx) -> char {
                    return lines[line][chIndx];
            };

            char curCh = getChar(currentLine, currentCharIndex);

            // case 1: we are at a whitespace character or newline character
            if ((isWhitespace(curCh)) || (curCh == '\n')) {
                if (curCh == '\n') {
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }
                // we first skip all the whitespace characters
                while (isWhitespace(curCh) && (!atEndOfDocument(currentLine, currentCharIndex))) {
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we are either: 
                // 1) at the end of the document
                // 2) at a non-whitespace character
                // either of those cases, we are done
            }

            else {
                // case 2: we are on a non-whitespace character
                // we first skip all the non-whitespace characters
                while (!isWhitespace(curCh) && (!atEndOfDocument(currentLine, currentCharIndex))) {
                    int prevLine = currentLine;
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if (prevLine != currentLine) {
                        break;
                    }
                }

                // next, we skip all the whitespace characters
                while (isWhitespace(curCh) && (!atEndOfDocument(currentLine, currentCharIndex))) {
                    int prevLine = currentLine;
                    moveForwardOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if ((prevLine != currentLine) && (curCh == '\n')) {
                        break;
                    }
                }

                // we are either:
                // 1) at the end of the document
                // 2) at a non-whitespace character
                // either of those cases, we are done
            }

            currentCursorChar.line = currentLine;
            currentCursorChar.subLine = currentCharIndex / curWidth;
            currentCursorChar.index = currentCharIndex % curWidth;
            return;
        }















        bool Document::atBeginOfDocument(int &currentLine, int &currentCharIndex) {
            return (currentLine == 0) && (currentCharIndex == 0);
        }




        // for traversing moveToPrevWord and moveToPrevNonWhitespace
        // NOTE may make this into a new version of moveLeft for cursor
        void Document::moveBackOneChar(int &currentLine, int &currentCharIndex) {
            // Attempt to move one character backwards in the document.
            if (currentCharIndex > 0) {
                currentCharIndex--;
            } 
            else {
                if (currentLine == 0) {
                    return;
                }
                // need to skip the newLine character in the end
                // move to the prev line end 
                currentLine--;
                currentCharIndex = max((int)lines[currentLine].size() - 2, 0);
            }

        }




        void Document::moveToPrevWord() {
            if (atBeginOfDocument(currentCursorChar.line, currentCursorChar.index)) { // we are at the beginning of file. Don't do anything
                return;
            }

            int currentLine = currentCursorChar.line;
            int currentSubLine = currentCursorChar.subLine;
            int currentIndex = currentCursorChar.index;

            int currentCharIndex = currentSubLine * curWidth + currentIndex;

            // define a lambda to access characters more easily
            auto getChar = [&](int line, int chIndx) -> char {
                    return lines[line][chIndx];
            };

            auto save = [&] () {
                currentCursorChar.line = currentLine;
                currentCursorChar.subLine = currentCharIndex / curWidth;
                currentCursorChar.index = currentCharIndex % curWidth;
            };

            char curCh = getChar(currentLine, currentCharIndex);

            // case 1: we are at a whitespace character or newline character
            if ((isWhitespace(curCh)) || (curCh == '\n')) {

                if (curCh == '\n') {
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we first skip all the whitespace characters
                while (isWhitespace(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we are either: 
                // 1) at the beginning of the document
                if (atBeginOfDocument(currentLine, currentCharIndex)) {
                    save();
                    return;
                }

                // 2) at a non-whitespace character
                if (isAlphabet(curCh)) {
                    // we move to the first alphabet character
                    while (isAlphabet(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                        if (currentCharIndex == 0) {
                            break;
                        }
                        moveBackOneChar(currentLine, currentCharIndex);
                        curCh = getChar(currentLine, currentCharIndex);
                    }
                    if (!isAlphabet(curCh)) {
                        moveForwardOneChar(currentLine, currentCharIndex);
                    }
                }
                else if (curCh != '\n') {
                    // we move to the first punctuation character
                    while (isPunctuation(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                        if (currentCharIndex == 0) {
                            break;
                        }
                        moveBackOneChar(currentLine, currentCharIndex);
                        curCh = getChar(currentLine, currentCharIndex);
                    }
                    if (!isPunctuation(curCh)) {
                        moveForwardOneChar(currentLine, currentCharIndex);
                    }
                }
            }

            // case 2: we are on a punctuation character
            else if (isPunctuation(curCh)) {
                // first we skip all the punctuation characters (if there are any)

                int PuntuationCount = 0;
                while (isPunctuation(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    PuntuationCount++;
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if (isPunctuation(curCh) && currentCharIndex == 0) {
                        break;
                    }
                }

                if ((!isPunctuation(curCh)) && (PuntuationCount > 1)) {
                    // this means we are previously in the middle of a punctuation string
                    // we move to the beginning of the punctuation characters
                    // and we're done
                    moveForwardOneChar(currentLine, currentCharIndex);
                    save();
                    return;
                }

                // mext we skip all the whitespace characters (if there are any)
                while (isWhitespace(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we are either:
                // 1) at the beginning of the document
                if (atBeginOfDocument(currentLine, currentCharIndex)) {
                    save();
                    return;
                }
                // 2) at a non-whitespace character
                if (isAlphabet(curCh)) {
                    // we move to the first alphabet character
                    while (isAlphabet(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                        if (currentCharIndex == 0) {
                            break;
                        }
                        moveBackOneChar(currentLine, currentCharIndex);
                        curCh = getChar(currentLine, currentCharIndex);
                    }
                    if (!isAlphabet(curCh)) {
                        moveForwardOneChar(currentLine, currentCharIndex);
                    }
                }
                else if (curCh != '\n') {
                    // we move to the first punctuation character
                    while (isPunctuation(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                        if (currentCharIndex == 0) {
                            break;
                        }
                        moveBackOneChar(currentLine, currentCharIndex);
                        curCh = getChar(currentLine, currentCharIndex);
                    }
                    if (!isPunctuation(curCh)) {
                        moveForwardOneChar(currentLine, currentCharIndex);
                    }
                }
                
            }

            else {
                // case 3: we are on an alphabet character
                // we first skip all the alphabet characters
                int AlphabetCount = 0;
                while (isAlphabet(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    AlphabetCount++;
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if (isAlphabet(curCh) && currentCharIndex == 0) {
                        break;
                    }
                }

                if ((!isAlphabet(curCh)) && (AlphabetCount > 1)) {
                    // this means we are previously in the middle of an alphabet string
                    // we move to the beginning of the alphabet characters
                    // and we're done
                    moveForwardOneChar(currentLine, currentCharIndex);
                    save();
                    return;
                }

                // next, we skip all the whitespace characters
                while (isWhitespace(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we are either:
                // 1) at the beginning of the document
                if (atBeginOfDocument(currentLine, currentCharIndex)) {
                    save();
                    return;
                }
                // 2) at a non-whitespace character
                // either of those cases, we are done
                if (isAlphabet(curCh)) {
                    // we move to the first alphabet character
                    while (isAlphabet(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                        if (currentCharIndex == 0) {
                            break;
                        }
                        moveBackOneChar(currentLine, currentCharIndex);
                        curCh = getChar(currentLine, currentCharIndex);
                    }
                    if (!isAlphabet(curCh)) {
                        moveForwardOneChar(currentLine, currentCharIndex);
                    }
                }
                else if (curCh != '\n') {
                    // we move to the first punctuation character
                    while (isPunctuation(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                        if (currentCharIndex == 0) {
                            break;
                        }
                        moveBackOneChar(currentLine, currentCharIndex);
                        curCh = getChar(currentLine, currentCharIndex);
                    }
                    if (!isPunctuation(curCh)) {
                        moveForwardOneChar(currentLine, currentCharIndex);
                    }
                }
                
            }

            save();
            return;
        }





        void Document::moveToPrevNonWhitespace() {
            if (atBeginOfDocument(currentCursorChar.line, currentCursorChar.index)) { // we are at the beginning of file. Don't do anything
                return;
            }

            int currentLine = currentCursorChar.line;
            int currentSubLine = currentCursorChar.subLine;
            int currentIndex = currentCursorChar.index;

            int currentCharIndex = currentSubLine * curWidth + currentIndex;

            // define a lambda to access characters more easily
            auto getChar = [&](int line, int chIndx) -> char {
                    return lines[line][chIndx];
            };

            auto save = [&] () {
                currentCursorChar.line = currentLine;
                currentCursorChar.subLine = currentCharIndex / curWidth;
                currentCursorChar.index = currentCharIndex % curWidth;
            };

            char curCh = getChar(currentLine, currentCharIndex);

            // case 1: we are at a whitespace character or newline character
            if ((isWhitespace(curCh)) || (curCh == '\n')) {

                if (curCh == '\n') {
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we first skip all the whitespace characters
                while (isWhitespace(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we are either: 
                // 1) at the beginning of the document
                if (atBeginOfDocument(currentLine, currentCharIndex)) {
                    save();
                    return;
                }

                // 2) at a non-whitespace character
                if ((!isWhitespace(curCh)) && (curCh != '\n')) {
                    // we move to the first non-whitespace character
                    while (!isWhitespace(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                        if (currentCharIndex == 0) {
                            break;
                        }
                        moveBackOneChar(currentLine, currentCharIndex);
                        curCh = getChar(currentLine, currentCharIndex);
                    }
                    if (isWhitespace(curCh)) {
                        moveForwardOneChar(currentLine, currentCharIndex);
                    }
                }
            }

            // case 2: we are on a non-whitespace character
            else{
                // we first skip all the non-whitespace characters
                int count = 0;
                while ((!isWhitespace(curCh)) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    count++;
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                    if (!isWhitespace(curCh) && currentCharIndex == 0) {
                        break;
                    }
                }

                if ((isWhitespace(curCh)) && (count > 1)) {
                    // this means we are previously in the middle of a non-whitespace string
                    // we move to the beginning of the non-whitespace characters
                    // and we're done
                    moveForwardOneChar(currentLine, currentCharIndex);
                    save();
                    return;
                }

                // next, we skip all the whitespace characters
                while (isWhitespace(curCh) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }

                // we are either:
                // 1) at the beginning of the document
                if (atBeginOfDocument(currentLine, currentCharIndex)) {
                    save();
                    return;
                }
                // 2) at a non-whitespace character
                while ((!isWhitespace(curCh)) && (!atBeginOfDocument(currentLine, currentCharIndex))) {
                    if (currentCharIndex == 0) {
                        break;
                    }
                    moveBackOneChar(currentLine, currentCharIndex);
                    curCh = getChar(currentLine, currentCharIndex);
                }
                if (isWhitespace(curCh)) {
                    moveForwardOneChar(currentLine, currentCharIndex);
                }
            }

            save();
            return;
        }












}


