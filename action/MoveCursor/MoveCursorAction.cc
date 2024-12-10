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
            
            case ActionTypes::MOVE_WORD_W:
                cursorMover.moveToNextWord(multiplier);
                break;
            case ActionTypes::MOVE_WORD_BIG_W:
                cursorMover.moveToNextNonWhitespace(multiplier);
                break;
            case ActionTypes::MOVE_WORD_B:
                cursorMover.moveToPrevWord(multiplier);
                break;
            case ActionTypes::MOVE_WORD_BIG_B:
                cursorMover.moveToPrevNonWhitespace(multiplier);
                break;
        }
        return ReturnMessage::SUCCESS;
    }



}