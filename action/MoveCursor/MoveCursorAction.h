#ifndef MOVECURSORACTION_H
#define MOVECURSORACTION_H

#include "../Action.h"
#include "../../model/Document.h"
#include "../../controller/CursorMover.h"
#include "../../structs/ActionTypes.h"



namespace action {

    class MoveCursorAction : public Action {
        model::Document &document;
        controller::CursorMover &cursorMover;
        int multiplier;
        ActionTypes actionType;

    public:
        MoveCursorAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType): document{document}, cursorMover{cursorMover}, multiplier{multiplier}, actionType{actionType} {}

        ReturnMessage execute() override;



        ReturnMessage undo() override {
            return ReturnMessage::SUCCESS;
        };










    };




}













#endif