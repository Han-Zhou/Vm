#include "ChangeAction.h"

namespace action {

    string ChangeAction::deleteRange(const Triple &start, const Triple &end) {
        return document.deleteRange(start, end);
    }

    ReturnMessage ChangeAction::execute(){
        switch(actionType) {
            case ActionTypes::CHANGE_CJ: {
                return cj(multiplier);
            }

            case ActionTypes::CHANGE_CK: {
               return ck(multiplier); 
            }

            case ActionTypes::CHANGE_CH: {
                return ch(multiplier);
            }

            case ActionTypes::CHANGE_CL: {
                return cl(multiplier);
            }

            case ActionTypes::CHANGE_CW : {
                return cw(multiplier);
            }

            case ActionTypes::CHANGE_CBIGW: {
                return cW(multiplier);
            }

            case ActionTypes::CHANGE_CB: {
                return cb(multiplier);
            }

            case ActionTypes::CHANGE_CBIGB: {
                return cB(multiplier);
            }

            case ActionTypes::CHANGE_C$: {
                return c$(multiplier);
            }

            case ActionTypes::CHANGE_CCARET: {
                return cCaret(multiplier);
            }

            case ActionTypes::CHANGE_C0: {
                return c0(multiplier);
            }

            case ActionTypes::CHANGE_CC: {
                return cc(multiplier);
            }
        }
        return ReturnMessage::SUCCESS;
    }



    ReturnMessage ChangeAction::undo() {
        //  >>>>>>
        return ReturnMessage::SUCCESS;
    }



    ReturnMessage ChangeAction::cc(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            s += document.deleteCurrentLine();
            cursorMover.updateCursor();
        }
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeAction::cw(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += cc_wy(1);
                continue;
            }
            cursorMover.moveToNextWord(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += c$_wy(1);
                continue;
            }
            s += deleteRange(start, end);
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeAction::cW(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += cc_wy(1);
                continue;
            }
            cursorMover.moveToNextNonWhitespace(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += c$_wy(1);
                continue;
            }
            s += deleteRange(start, end);
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeAction::cb(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += cc_wy(1);
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevWord(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += cc_wy(1);
                continue;
            }
            s += deleteRange(end, start);
        }
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeAction::cB(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += cc_wy(1);
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevNonWhitespace(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += cc_wy(1);
                continue;
            } 
            s += deleteRange(end, start);
        }
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeAction::c$(int m) { // it doesn't care about multipliers
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            // we don't want to update the yank register if the line contains nothing
            return ReturnMessage::INSERT;
        }
        string s = "";
        cursorMover.moveToEndOfLine();
        Triple end = document.getTriple();
        s += deleteRange(start, end);
        document.updateTriple(start);
        cursorMover.updateCursor();
        s = cl_wy(1) + s;
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeAction::c0(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return ReturnMessage::INSERT;
        }
        string s = "";
        cursorMover.moveToFrontOfLine();
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    ReturnMessage ChangeAction::cCaret(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return ReturnMessage::INSERT;
        }
        string s = "";
        cursorMover.moveToFirstCharOfLine();
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    // delete the character to the left of the cursor
    ReturnMessage ChangeAction::ch(int m) {
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return ReturnMessage::INSERT;
        }
        if (start.index == 0) {
            return ReturnMessage::INSERT;
        }
        string s = "";
        cursorMover.moveLeft(m);
        Triple end = document.getTriple();
        s += deleteRange(end, start);
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    // delete the CURRENT character, not the one to the right
    ReturnMessage ChangeAction::cl(int m) {
        string s = "";
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return ReturnMessage::INSERT;
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
        return ReturnMessage::INSERT;
    }

    // deletes the current line and the line above
    ReturnMessage ChangeAction::ck(int m) {
        int curLine = document.getTriple().line;
        if (curLine == 0) {
            return ReturnMessage::INSERT;
        }
        string s = "";
        s += cc_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == 0) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                yankRegister.yank(s);
                return ReturnMessage::INSERT;
            }
            cursorMover.moveUp(1);
            curLine--;
            s = cc_wy(1) + s;
        }
        document.updateTriple({curLine, 0, 0});
        cursorMover.updateCursor();
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }

    // deletes the current line and the line below
    ReturnMessage ChangeAction::cj(int m) {
        int originalLine = document.getTriple().line;
        int curLine = document.getTriple().line;
        if (curLine == document.getLinesSize() - 1) {
            return ReturnMessage::INSERT;
        }
        string s = "";
        s += cc_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == document.getLinesSize() - 1) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                yankRegister.yank(s);
                return ReturnMessage::INSERT;
            }

            curLine++;
            s = s + cc_wy(1);
        }
        document.updateTriple({originalLine, 0, 0});
        cursorMover.updateCursor();
        yankRegister.yank(s);
        return ReturnMessage::INSERT;
    }























// ======================== WITHOUT YANKING ========================



    string ChangeAction::cc_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            s += document.deleteCurrentLine();
            cursorMover.updateCursor();
        }
        return s;
    }

    string ChangeAction::cw_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += cc_wy(1);
                continue;
            }
            cursorMover.moveToNextWord(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += c$_wy(1);
                continue;
            }
            s += deleteRange(start, end);
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        return s;
    }

    string ChangeAction::cW_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += cc_wy(1);
                continue;
            }
            cursorMover.moveToNextNonWhitespace(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += c$_wy(1);
                continue;
            }
            s += deleteRange(start, end);
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        return s;
    }

    string ChangeAction::cb_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += cc_wy(1);
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevWord(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += cc_wy(1);
                continue;
            }
            s += deleteRange(end, start);
        }
        return s;
    }

    string ChangeAction::cB_wy(int m) {
        string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += cc_wy(1);
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevNonWhitespace(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += cc_wy(1);
                continue;
            } 
            s += deleteRange(end, start);
        }
        return s;
    }

    string ChangeAction::c$_wy(int m) { // it doesn't care about multipliers
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
        s += cl_wy(1);
        return s;
    }

    string ChangeAction::c0_wy(int m) {
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

    string ChangeAction::cCaret_wy(int m) {
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

    string ChangeAction::ch_wy(int m) {
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

    string ChangeAction::cl_wy(int m) {
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

    string ChangeAction::ck_wy(int m) {
        int curLine = document.getTriple().line;
        if (curLine == 0) {
            return "";
        }
        string s = "";
        s += cc_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == 0) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                return s;
            }
            cursorMover.moveUp(1);
            curLine--;
            s = cc_wy(1) + s;
        }
        document.updateTriple({curLine, 0, 0});
        cursorMover.updateCursor();
        return s;
    }

    string ChangeAction::cj_wy(int m) {
        int originalLine = document.getTriple().line;
        int curLine = document.getTriple().line;
        if (curLine == document.getLinesSize() - 1) {
            return "";
        }
        string s = "";
        s += cc_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == document.getLinesSize() - 1) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                return s;
            }

            curLine++;
            s += cc_wy(1);
        }
        document.updateTriple({originalLine, 0, 0});
        cursorMover.updateCursor();
        return s;
    }


}