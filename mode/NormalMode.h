#ifndef NORMALMODE_H
#define NORMALMODE_H



#include "Mode.h"
#include "../model/Document.h"
#include "../controller/CursorMover.h"


using namespace std;


namespace mode {

    
    class NormalMode : public Mode {

        model::Document &document;
        controller::CursorMover cursorMover;

    public:
        NormalMode(model::Document &document, controller::CursorMover cm): document{document}, cursorMover{cm} {}

        ReturnMessage processInput(vector<int> input) override;
        ~NormalMode() = default;

        









    };
}
#endif