#include "PasteAction.h"

namespace action {

    ReturnMessage PasteAction::execute() {
        switch(actionType) {
            case ActionTypes::PASTE_P: {
                return p();
            }
            case ActionTypes::PASTE_BIGP: {
                return bigP();
            }
        }
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage PasteAction::undo() {
        return ReturnMessage::SUCCESS;
    }


    ReturnMessage PasteAction::p() {
        string text = yankRegister.getText();
        if (text == "") {
            return ReturnMessage::SUCCESS;
        }

        vector<string> pastedLines;
        string curLine = "";
        for (int i = 0; i < text.size(); i++) {
            curLine += text[i];
            if (text[i] == '\n') {
                pastedLines.push_back(curLine);
                curLine.clear();
            }
        }
        if (curLine != "") {
            pastedLines.push_back(curLine);
        }
        document.insertTextAfter(pastedLines);
        cursorMover.updateCursor();
        return ReturnMessage::SUCCESS;
    }



    ReturnMessage PasteAction::bigP() {
        string text = yankRegister.getText();
        if (text == "") {
            return ReturnMessage::SUCCESS;
        }

        vector<string> pastedLines;
        string curLine = "";
        for (int i = 0; i < text.size(); i++) {
            curLine += text[i];
            if (text[i] == '\n') {
                pastedLines.push_back(curLine);
                curLine.clear();
            }
        }
        if (curLine != "") {
            pastedLines.push_back(curLine);
        }
        document.insertTextBefore(pastedLines);
        cursorMover.updateCursor();
        return ReturnMessage::SUCCESS;
    }









}