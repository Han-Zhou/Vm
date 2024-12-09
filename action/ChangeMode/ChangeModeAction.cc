#include "ChangeModeAction.h"

namespace action {

    ReturnMessage ChangeModeAction::execute() {
        switch (actionType) {
            case ActionTypes::CHANGE_TO_INSERT_I:
                return changeToInsertI();
                break;
            case ActionTypes::CHANGE_TO_INSERT_A:
                return changeToInsertA();
                break;
            case ActionTypes::CHANGE_TO_INSERT_O:
                return changeToInsertO();
                break;
            case ActionTypes::CHANGE_TO_INSERT_BIG_I:
                return changeToInsertBigI();
                break;
            case ActionTypes::CHANGE_TO_INSERT_BIG_A:
                return changeToInsertBigA();
                break;
            case ActionTypes::CHANGE_TO_INSERT_BIG_O:
                return changeToInsertBigO();
                break;
        }
    }

    
    ReturnMessage ChangeModeAction::undo() {
        // do nothing
        return ReturnMessage::SUCCESS;
    }






    ReturnMessage ChangeModeAction::changeToInsertI() {
        // we dont have to do any additional work
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeModeAction::changeToInsertA() {
        cursorMover.moveCursorRightInsertMode();
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeModeAction::changeToInsertO() {
        // we need to add a line below the current line
        // and move out cursor there
        document.addLineBelow();
        cursorMover.moveDown();
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeModeAction::changeToInsertBigI() {
        // we need to move to the first character of the current line
        document.moveToFirstCharOfLine();
        cursorMover.updateCursorTriple(document.getTriple());
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeModeAction::changeToInsertBigA() {
        // we need to move to the last character of the current line and then move right (so that the cursor hovers)
        document.moveToEndOfLine();
        cursorMover.updateCursorTriple(document.getTriple());
        cursorMover.moveCursorRightInsertMode();
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeModeAction::changeToInsertBigO() {
        // we need to add a line above the current line
        // and move our cursor there
        document.addLineAbove();
        cursorMover.updateCursorTriple(document.getTriple());
        cursorMover.moveUp();
        return ReturnMessage::INSERT;
    }









}