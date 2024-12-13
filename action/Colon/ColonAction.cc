#include "ColonAction.h"


namespace action {

    ReturnMessage ColonAction::execute() {
        switch(actionType) {
            case ActionTypes::COLON_Q_EXCLAMATION: {
                return colonqexclamation();
            }
            case ActionTypes::COLON_Q: {
                return colonq();
            }
            case ActionTypes::COLON_W: {
                return colonw();
            }
            case ActionTypes::COLON_WQ: {
                return colonwq();
            }
            case ActionTypes::COLON_0: {
                return colon0();
            }
            case ActionTypes::COLON_$: {
                return colon$();
            }
            case ActionTypes::COLON_LINE: {
                return colonline();
            }
        }
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage ColonAction::undo() {
        return ReturnMessage::SUCCESS;
    }






    ReturnMessage ColonAction::colonqexclamation() {
        return ReturnMessage::QUIT;
    }


    ReturnMessage ColonAction::colonq() {
        utils::FileSaver fileSaver;
        if (fileSaver.saveFile(document.getFileName(), document.getLines(), document.getOriginalLines())) {
            return ReturnMessage::QUIT;
        }
        return ReturnMessage::SUCCESS;
    }


    ReturnMessage ColonAction::colonw() {
        utils::FileSaver fileSaver;
        fileSaver.saveFile(document.getFileName(), document.getLines(), document.getOriginalLines());
        return ReturnMessage::SUCCESS;
    }


    ReturnMessage ColonAction::colonwq() {
        utils::FileSaver fileSaver;
        fileSaver.saveFile(document.getFileName(), document.getLines(), document.getOriginalLines());
        return ReturnMessage::QUIT;
    }


    ReturnMessage ColonAction::colon0() {
        cursorMover.moveToStartOfFile();
        return ReturnMessage::SUCCESS;
    }


    ReturnMessage ColonAction::colon$() {
        cursorMover.moveToEndOfFile();
        return ReturnMessage::SUCCESS;
    }


    ReturnMessage ColonAction::colonline() {
        cursorMover.moveToLine(lineNumber);
        return ReturnMessage::SUCCESS;
    }











}



