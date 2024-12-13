#include "DeleteAction.h"

namespace action {

    string DeleteAction::deleteRange(const Triple &start, const Triple &end) {
        return document.deleteRange(start, end);
    }

    ReturnMessage DeleteAction::execute(){
        switch(actionType) {
            case ActionTypes::DELETE_DJ: {
                return dj(multiplier);
            }

            case ActionTypes::DELETE_DK: {
               return dk(multiplier); 
            }

            case ActionTypes::DELETE_DH: {
                return dh(multiplier);
            }

            case ActionTypes::DELETE_DL: {
                return dl(multiplier);
            }

            case ActionTypes::DELETE_DW : {
                return dw(multiplier);
            }

            case ActionTypes::DELETE_DBIGW: {
                return dW(multiplier);
            }

            case ActionTypes::DELETE_DB: {
                return db(multiplier);
            }

            case ActionTypes::DELETE_DBIGB: {
                return dB(multiplier);
            }

            case ActionTypes::DELETE_D$: {
                return d$(multiplier);
            }

            case ActionTypes::DELETE_DCARET: {
                return dCaret(multiplier);
            }

            case ActionTypes::DELETE_D0: {
                return d0(multiplier);
            }

            case ActionTypes::DELETE_DD: {
                return dd(multiplier);
            }
        }
        return ReturnMessage::SUCCESS;
    }



    ReturnMessage DeleteAction::undo() {
        //  >>>>>>
        return ReturnMessage::SUCCESS;
    }



    ReturnMessage DeleteAction::dd(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            s += document.deleteCurrentLine();
            cursorMover.updateCursor();
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }



    ReturnMessage DeleteAction::dw(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += dd_wy(1);
                continue;
            }
            cursorMover.moveToNextWord(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += d$_wy(1);
                continue;
            }
            s += deleteRange(start, end);
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage DeleteAction::dW(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += dd_wy(1);
                continue;
            }
            cursorMover.moveToNextNonWhitespace(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += d$_wy(1);
                continue;
            }
            s += deleteRange(start, end);
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage DeleteAction::db(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += dd_wy(1);
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevWord(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += dd_wy(1);
                continue;
            }
            s += deleteRange(end, start);
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage DeleteAction::dB(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += dd_wy(1);
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevNonWhitespace(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += dd_wy(1);
                continue;
            } 
            s += deleteRange(end, start);
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }






    ReturnMessage DeleteAction::d$(int m) { // it doesn't care about multipliers
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            // we don't want to update the yank register if the line contains nothing
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        cursorMover.moveToEndOfLine();
        Triple end = document.getTriple();
        s += deleteRange(start, end);
        document.updateTriple(start);
        cursorMover.updateCursor();
        s = dl_wy(1) + s;
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage DeleteAction::d0(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        cursorMover.moveToFrontOfLine();
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage DeleteAction::dCaret(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        cursorMover.moveToFirstCharOfLine();
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }



    // delete the character to the left of the cursor
    ReturnMessage DeleteAction::dh(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return ReturnMessage::SUCCESS;
        }
        if (start.index == 0) {
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        cursorMover.moveLeft(m);
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }



    // detelete the CURRENT character, not the one to the right
    ReturnMessage DeleteAction::dl(int m) {
        string s = "";
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return ReturnMessage::SUCCESS;
        }
        for (int i = 0; i < m; i++) {
            cursorMover.moveRight(1);
            Triple end = document.getTriple();
            if (start == end) { // the cursor is at the end of the line; we need to delete this and moveleft
                s += document.fetchWrappedLines()[start.line][start.subLine].substr(start.index, 1);
                document.deleteChar(start); 
            }
            else {
                s += deleteRange(start, end);
            }
            cursorMover.moveLeft(1);
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }


    // deletes the current line and the line above
    ReturnMessage DeleteAction::dk(int m) {
        int curLine = document.getTriple().line;
        if (curLine == 0) {
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        s += dd_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == 0) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                yankRegister.yank(s);
                return ReturnMessage::SUCCESS;
            }
            cursorMover.moveUp(1);
            curLine--;
            s = dd_wy(1) + s;
        }
        document.updateTriple({curLine, 0, 0});
        cursorMover.updateCursor();
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }


    // deletes the current line and the line below
    ReturnMessage DeleteAction::dj(int m) {
        int originalLine = document.getTriple().line;
        int curLine = document.getTriple().line;
        if (curLine == document.getLinesSize() - 1) {
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        s += dd_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == document.getLinesSize() - 1) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                yankRegister.yank(s);
                return ReturnMessage::SUCCESS;
            }

            curLine++;
            s = s + dd_wy(1);
        }
        document.updateTriple({originalLine, 0, 0});
        cursorMover.updateCursor();
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }



























// ======================== WITHOUT YANKING ========================






    string DeleteAction::dd_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            s += document.deleteCurrentLine();
            cursorMover.updateCursor();
        }
        return s;
    }

    string DeleteAction::dw_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += dd_wy(1);
                continue;
            }
            cursorMover.moveToNextWord(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += d$_wy(1);
                continue;
            }
            s +=deleteRange(start, end);
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        return s;
    }

    string DeleteAction::dW_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += dd_wy(1);
                continue;
            }
            cursorMover.moveToNextNonWhitespace(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += d$_wy(1);
                continue;
            }
            s += deleteRange(start, end);
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        return s;
    }

    string DeleteAction::db_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += dd_wy(1);
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevWord(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += dd_wy(1);
                continue;
            }
            s += deleteRange(end, start);
        }
        return s;
    }

    string DeleteAction::dB_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += dd_wy(1);
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevNonWhitespace(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += dd_wy(1);
                continue;
            } 
            s += deleteRange(end, start);
        }
        return s;
    }

    string DeleteAction::d$_wy(int m) { // it doesn't care about multipliers
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return "";
        }
        string s = "";
        cursorMover.moveToEndOfLine();
        Triple end = document.getTriple();
        s += deleteRange(start, end);
        document.updateTriple(start);
        cursorMover.updateCursor();
        s += dl_wy(1);
        return s;
    }

    string DeleteAction::d0_wy(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return "";
        }
        string s = "";
        cursorMover.moveToFrontOfLine();
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        return s;
    }

    string DeleteAction::dCaret_wy(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return "";
        }
        string s = "";
        cursorMover.moveToFirstCharOfLine();
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        return s;
    }

    string DeleteAction::dh_wy(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return "";
        }
        string s = "";
        cursorMover.moveLeft(m);
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        return s;
    }

    string DeleteAction::dl_wy(int m) {
        string s = "";
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return "";
        }
        for (int i = 0; i < m; i++) {
            cursorMover.moveRight(1);
            Triple end = document.getTriple();
            if (start == end) { // the cursor is at the end of the line; we need to delete this and moveleft
                s += document.fetchWrappedLines()[start.line][start.subLine].substr(start.index, 1);
                document.deleteChar(start); 
            }
            else {
                s += deleteRange(start, end);
            }
            cursorMover.moveLeft(1);
        }
        return s;
    }

    string DeleteAction::dk_wy(int m) {
        int curLine = document.getTriple().line;
        if (curLine == 0) {
            return "";
        }
        string s = "";
        s += dd_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == 0) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                return s;
            }
            cursorMover.moveUp(1);
            curLine--;
            s = dd_wy(1) + s;
        }
        document.updateTriple({curLine, 0, 0});
        cursorMover.updateCursor();
        return s;
    }

    string DeleteAction::dj_wy(int m) {
        int originalLine = document.getTriple().line;
        int curLine = document.getTriple().line;
        if (curLine == document.getLinesSize() - 1) {
            return "";
        }
        string s = "";
        s += dd_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == document.getLinesSize() - 1) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                return s;
            }

            curLine++;
            s += dd_wy(1);
        }
        document.updateTriple({originalLine, 0, 0});
        cursorMover.updateCursor();
        return s;
    }
}
