# ifndef INSERTMODE_H
# define INSERTMODE_H

#include <fstream>
#include <algorithm>


#include "Mode.h"
#include "../model/Document.h"
#include "../controller/CursorMover.h"

using namespace std;

namespace mode {


    class InsertMode : public Mode {

        model::Document &document;
        controller::CursorMover cursorMover;


    public:
        InsertMode(model::Document &document, controller::CursorMover cm): document{document}, cursorMover{cm} {}

        ReturnMessage processInput(vector<int> input) override;
        ~InsertMode() = default;

        void insertChar(int ch);
        void deleteChar();






    };




}
#endif