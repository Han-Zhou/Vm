#include "Document.h"

using namespace std;

namespace model {


        Document::Document(const string &filename) {
            // read the file
            utils::FileReader fr;
            lines = fr.read_file(filename);
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


}


