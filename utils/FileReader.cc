#include "FileReader.h"
#include <iostream>

using namespace std;


namespace utils {

    vector<string> FileReader::read_file(const string &filename) {
        ifstream file(filename);
        vector<string> lines;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
            lines.push_back(line);
        }
        return lines;
    }
}




