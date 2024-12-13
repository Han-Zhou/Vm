#include "FileSaver.h"


namespace utils {
    bool FileSaver::saveFile(const string &filename, const vector<string> &lines, const vector<string> &originalLines) {

        if (lines == originalLines) {
            return false;
        }

        ofstream file(filename);
        file << noskipws;
        for (const string &line : lines) {
            file << line;
        }
        return true;
    }
    
}