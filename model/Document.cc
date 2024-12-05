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
        }


        vector<string> Document::getWrappedLines(size_t width) {
            wrap(width);
            return wrapped_lines;
        }

        vector<string> Document::fetchWrappedLines() const {
            return wrapped_lines;
        }


        size_t Document::getLinesSize() const {
            return lines.size();
        }

        size_t Document::getWrappedLinesSize() const {
            return wrapped_lines.size();
        }


}


