#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace utils {
    class TextWrapper {
    public:
        vector<string> wrapText(const vector<string> text, size_t maxWidth);
    };
}

