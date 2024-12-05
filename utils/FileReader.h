# ifndef FILE_READER_H
# define FILE_READER_H

#include<fstream>
#include<string>
#include<vector>

using namespace std;

namespace utils {

    class FileReader {
    public:
        vector<string> read_file(const string &filename);
    };
}

# endif