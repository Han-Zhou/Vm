#ifndef CHANGE_MODE_ACTION_H
#define CHANGE_MODE_ACTION_H

#include "../Action.h"
#include "../../model/Document.h"
// #include "../../view/Window.h"
#include "../../controller/CursorMover.h"
#include "../../structs/ActionTypes.h"



namespace action {

    class ChangeModeAction : public Action {
        model::Document &document;
        controller::CursorMover &cursorMover;
        ActionTypes actionType;

        ReturnMessage changeToInsertI();
        ReturnMessage changeToInsertA();
        ReturnMessage changeToInsertO();
        ReturnMessage changeToInsertBigI();
        ReturnMessage changeToInsertBigA();
        ReturnMessage changeToInsertBigO();
    
    public:
        ChangeModeAction(model::Document &document, controller::CursorMover &cursorMover, ActionTypes actionType): document{document}, cursorMover{cursorMover}, actionType{actionType} { }

        ~ChangeModeAction() = default;

        ReturnMessage execute() override;

        ReturnMessage undo() override;
    };;


}














#endif