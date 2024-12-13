#ifndef FileSaver_H
#define FileSaver_H


#include <vector>
#include <fstream>
#include <string>

using namespace std;

namespace utils {
    class FileSaver {
    public:
        bool saveFile(const string &filename, const vector<string> &lines, const vector<string> &originalLines);
    };
}















#endif