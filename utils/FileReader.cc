#include "FileReader.h"
#include <iostream>

using namespace std;


namespace utils {

    vector<string> FileReader::read_file(const string &filename) {
        cout << "Reading file: " << filename << endl;
        ifstream file(filename);
        vector<string> lines;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
            lines.push_back(line);
        }
        cout << "Done reading file" << endl;
        return lines;
    }
}




