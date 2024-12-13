#ifndef COLON_ACTION_H
#define COLON_ACTION_H


#include "../Action.h"
#include "../../model/Document.h"
#include "../../model/YankRegister.h"
#include "../../controller/CursorMover.h"
#include "../../structs/ActionTypes.h"
#include "../../structs/ReturnMessage.h"
#include "../../utils/FileSaver.h"



namespace action {

    class ColonAction: public Action {

            model::Document &document;
            controller::CursorMover &cursorMover;
            ActionTypes actionType;
            int lineNumber;

            string deleteRange(const Triple &start, const Triple &end);

            

            ReturnMessage colonqexclamation();
            ReturnMessage colonq();
            ReturnMessage colonw();
            ReturnMessage colonwq();
            ReturnMessage colon0();
            ReturnMessage colon$();
            ReturnMessage colonline();
    


            
        public : 

            ColonAction(model::Document &document, controller::CursorMover &cursorMover, ActionTypes actionType, int lineNumber): document{document}, cursorMover{cursorMover}, actionType{actionType}, lineNumber{lineNumber} {}

            ReturnMessage execute() override;

            ReturnMessage undo() override;

    };


}








#endif