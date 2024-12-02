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
