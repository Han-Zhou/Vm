#ifndef PASTE_ACTION_H
#define PASTE_ACTION_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "../Action.h"
#include "../../model/Document.h"
#include "../../model/YankRegister.h"
#include "../../controller/CursorMover.h"
#include "../../structs/ActionTypes.h"
#include "../../structs/Triple.h"
#include "../../structs/ReturnMessage.h"



namespace action {

    class PasteAction : public Action {
        model::Document &document;
        controller::CursorMover &cursorMover;
        int multiplier;
        ActionTypes actionType;
        model::YankRegister &yankRegister;


        ReturnMessage p();
        ReturnMessage bigP();

        
        public:
        PasteAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier,  ActionTypes actionType, model::YankRegister &yr): document{document}, cursorMover{cursorMover}, multiplier{multiplier}, actionType{actionType}, yankRegister{yr} { }

        ~PasteAction() = default;

        ReturnMessage execute() override;

        ReturnMessage undo() override;
    };


}














#endif