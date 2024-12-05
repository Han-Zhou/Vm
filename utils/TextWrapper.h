#ifndef TEXTWRAPPER_H
#define TEXTWRAPPER_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

namespace utils {
    class TextWrapper {
    public:
        vector<vector<string>> wrapText(const vector<string> text, size_t maxWidth);
    };
}

#endif
