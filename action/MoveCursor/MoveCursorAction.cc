#include "MoveCursorAction.h"



namespace action {

    ReturnMessage MoveCursorAction::execute() {
        switch (actionType) {
            case ActionTypes::MOVE_UP:
                cursorMover.moveUp(multiplier);
                break;
            case ActionTypes::MOVE_DOWN:
                cursorMover.moveDown(multiplier);
                break;
            case ActionTypes::MOVE_LEFT:
                cursorMover.moveLeft(multiplier);
                break;
            case ActionTypes::MOVE_RIGHT:
                cursorMover.moveRight(multiplier);
                break;
            case ActionTypes::MOVE_LINE_0:
                cursorMover.moveToFrontOfLine();
                break;
            case ActionTypes::MOVE_LINE_$:
                cursorMover.moveToEndCharOfLine();
                break;
            case ActionTypes::MOVE_LINE_caret:
                cursorMover.moveToFirstCharOfLine();
                break;
        }
        return ReturnMessage::SUCCESS;
    }



}