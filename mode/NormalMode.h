#ifndef NORMALMODE_H
#define NORMALMODE_H


#include <fstream>

#include "Mode.h"
#include "../model/Document.h"
#include "../view/Window.h"
#include "../controller/CursorMover.h"
#include "../structs/ReturnMessage.h"
#include "../structs/Keys.h"
#include "../structs/ActionTypes.h"
#include "../action/ActionFactory.h"


using namespace std;


namespace mode {

    
    class NormalMode : public Mode {

        model::Document &document;
        controller::CursorMover cursorMover;

        bool isDigit(int ch);
        int extractDigit(int ch);

        int extractMultiplier(vector<int> &input);

    public:
        NormalMode(model::Document &document, controller::CursorMover cm): document{document}, cursorMover{cm} {}
         ~NormalMode() = default;



        ReturnMessage processInput(vector<int> input) override;




        









    };
}
#endif