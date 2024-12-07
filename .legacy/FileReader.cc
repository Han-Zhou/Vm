#include "FileReader.h"
#include <iostream>

using namespace std;


namespace utils {

    vector<string> FileReader::read_file(const string &filename) {
        cout << "Reading file: " << filename << endl;
        ifstream file(filename);
        file >> noskipws;
        vector<string> lines;
        string line;
        char ch;
        while (file.get(ch)) {
            // cout << line << endl;
            if (ch == '\n') {
                line += ch;
                lines.push_back(line);
                cout << "Line: " << line << endl;
                line = "";
            }
            else {
                line += ch;
            }
        }
        cout << "Done reading file" << endl;
        return lines;
    }
}




