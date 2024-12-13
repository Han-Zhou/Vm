#include "YankAction.h"





namespace action {

    // Helper function to get text from a given range without deletion
    string YankAction::getRangeText(const Triple &start, const Triple &end) {
        return document.getTextInRange(start, end);
    }

    ReturnMessage YankAction::execute(){
        switch(actionType) {
            case ActionTypes::YANK_YY:
                return yy(multiplier);

            case ActionTypes::YANK_YH:
                return yh(multiplier);

            case ActionTypes::YANK_YL:
                return yl(multiplier);

            case ActionTypes::YANK_YK:
                return yk(multiplier);

            case ActionTypes::YANK_YJ:
                return yj(multiplier);

            case ActionTypes::YANK_YW:
                return yw(multiplier);

            case ActionTypes::YANK_YBIGW:
                return yW(multiplier);

            case ActionTypes::YANK_YB:
                return yb(multiplier);

            case ActionTypes::YANK_YBIGB:
                return yB(multiplier);

            case ActionTypes::YANK_Y$:
                return y$(multiplier);

            case ActionTypes::YANK_YCARET:
                return yCaret(multiplier);

            case ActionTypes::YANK_Y0:
                return y0(multiplier);
        }
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::undo() {
        // undo does nothing
        return ReturnMessage::SUCCESS;
    }




    // ======= LINE YANKS =======

    ReturnMessage YankAction::yy(int m) {
        // Yank the entire current line(s)
        // Similar to dd but no deletion
        Triple start = document.getTriple();
        string s = "";
        int curLine = start.line;
        for (int i = 0; i < m; i++) {
            // get entire line text
            s += document.getLineText(curLine);
            // Move down if we are yanking multiple lines (like yy with a count)
            if (curLine == (int)document.getLinesSize() - 1) {
                return ReturnMessage::SUCCESS;
            }
            curLine++;
            cursorMover.moveDown(1);
        }
        // move the cursor back to the original line
        document.updateTriple(start);
        cursorMover.updateCursor();
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    // ======= MOTION-BASED YANKS =======
    // The logic is similar to the delete motions, except we only fetch text without deleting.

    ReturnMessage YankAction::yw(int m) {
        std::string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                // empty line, just yank nothing or maybe a newline
                s += "\n";
                continue;
            }
            cursorMover.moveToNextWord(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                // word extends to the next line
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += y$_wy(1); // yank until end of line (helper)
                continue;
            }
            string text = getRangeText(start, end);
            // remove trailing spaces
            text.erase(text.find_last_not_of(" \n\r\t") + 1);
            s += text;
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }


    ReturnMessage YankAction::yW(int m) {
        std::string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += "\n";
                continue;
            }
            cursorMover.moveToNextNonWhitespace(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += y$_wy(1);
                continue;
            }
            string text = getRangeText(start, end);
            // remove trailing spaces
            text.erase(text.find_last_not_of(" \n\r\t") + 1);
            s += text; 
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }


    ReturnMessage YankAction::yb(int m) {
        std::string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += "\n";
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevWord(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += yy_wy(1);
                continue;
            }
            s += getRangeText(end, start);
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::yB(int m) {
        std::string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += "\n";
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevNonWhitespace(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += yy_wy(1);
                continue;
            }
            s += getRangeText(end, start);
        }
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::y$(int m) {
        // yank until end of line
        // multiplier doesn't typically apply to y$, but if it does, you can loop.
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            // line is empty
            yankRegister.yank("");
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        cursorMover.moveToEndOfLine();
        Triple end = document.getTriple();
        s = getRangeText(start, end);
        document.updateTriple(start);
        cursorMover.updateCursor();
        s = yl_wy(1) + s;
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::y0(int m) {
        // yank from the start of line to current position
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            // line is empty
            yankRegister.yank("");
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        cursorMover.moveToFrontOfLine();
        Triple end = document.getTriple();
        s = getRangeText(end, start);
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::yCaret(int m) {
        // yank from the first non-whitespace char to current position
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            yankRegister.yank("");
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        cursorMover.moveToFirstCharOfLine();
        Triple end = document.getTriple();
        s += getRangeText(end, start);
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::yh(int m) {
        // yank m chars to the left
        string s = "";
        Triple start = document.getTriple();
        if (start.index == 0) {
            yankRegister.yank(s);
            return ReturnMessage::SUCCESS;
        }
        cursorMover.moveLeft(m);
        Triple end = document.getTriple();
        s += getRangeText(end, start);
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::yl(int m) {
        // yank m chars to the right
        string s = "";
        Triple start = document.getTriple();
        cursorMover.moveRight(m);
        Triple end = document.getTriple();
        s += getRangeText(start, end);
        document.updateTriple(start);
        cursorMover.updateCursor();
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::yk(int m) {
        int curLine = document.getTriple().line;
        if (curLine == 0) {
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        s += yy_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == 0) {
                // no more lines above
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                yankRegister.yank(s);
                return ReturnMessage::SUCCESS;
            }
            // move up to get the previous line text
            cursorMover.moveUp(1);
            curLine--;
            s = yy_wy(1) + s;
        }
        document.updateTriple({curLine, 0, 0});
        cursorMover.updateCursor();
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }

    ReturnMessage YankAction::yj(int m) {
        // yank the line(s) below
        int originalLine = document.getTriple().line;
        int curLine = document.getTriple().line;
        if (curLine == (int)document.getLinesSize() - 1) {
            return ReturnMessage::SUCCESS;
        }
        string s = "";
        s += yy_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == (int)document.getLinesSize() - 1) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                yankRegister.yank(s);
                return ReturnMessage::SUCCESS;
            }
            cursorMover.moveDown(1);
            curLine++;
            s += document.getLineText(curLine);
        }
        document.updateTriple({originalLine, 0, 0});
        cursorMover.updateCursor();
        yankRegister.yank(s);
        return ReturnMessage::SUCCESS;
    }















    


    // Versions without yanking


    string YankAction::yy_wy(int m) {
        // Yank the entire current line(s)
        // Similar to dd but no deletion
        Triple start = document.getTriple();
        string s = "";
        int curLine = start.line;
        for (int i = 0; i < m; i++) {
            // get entire line text
            s += document.getLineText(curLine);
            // Move down if we are yanking multiple lines (like yy with a count)
            if (curLine == (int)document.getLinesSize() - 1) {
                return s;
            }
            curLine++;
            cursorMover.moveDown(1);
        }
        // move the cursor back to the original line
        document.updateTriple(start);
        cursorMover.updateCursor();
        return s;
    }



    string YankAction::yw_wy(int m) {
        std::string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                // empty line, just yank nothing or maybe a newline
                s += "\n";
                continue;
            }
            cursorMover.moveToNextWord(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                // word extends to the next line
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += y$_wy(1); // yank until end of line (helper)
                continue;
            }
            string text = getRangeText(start, end);
            // remove trailing spaces
            text.erase(text.find_last_not_of(" \n\r\t") + 1);
            s += text; 
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        return s;
    }


    string YankAction::yW_wy(int m) {
        std::string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += "\n";
                continue;
            }
            cursorMover.moveToNextNonWhitespace(1);
            Triple end = document.getTriple();
            if (start.line != end.line) {
                document.updateTriple(start);
                cursorMover.updateCursor();
                s += y$_wy(1);
                continue;
            }
            string text = getRangeText(start, end);
            // remove trailing spaces
            text.erase(text.find_last_not_of(" \n\r\t") + 1);
            s += text; 
            document.updateTriple(start);
            cursorMover.updateCursor();
        }
        return s;
    }


    string YankAction::yb_wy(int m) {
        std::string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += "\n";
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevWord(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += yy_wy(1);
                continue;
            }
            s += getRangeText(end, start);
        }
        return s;
    }

    string YankAction::yB_wy(int m) {
        std::string s = "";
        for (int i = 0; i < m; i++) {
            Triple start = document.getTriple();
            if (document.getLines()[start.line].size() == 1) {
                s += "\n";
                cursorMover.moveUp(1);
                continue;
            }
            cursorMover.moveToPrevNonWhitespace(1);
            Triple end = document.getTriple();
            if ((start.line != end.line) && (end.subLine == 0) && (end.index == 0)) {
                s += yy_wy(1);
                continue;
            }
            s += getRangeText(end, start);
        }
        return s;
    }

    string YankAction::y$_wy(int m) {
        // yank until end of line
        // multiplier doesn't typically apply to y$, but if it does, you can loop.
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return "";
        }
        string s = "";
        cursorMover.moveToEndOfLine();
        Triple end = document.getTriple();
        s = getRangeText(start, end);
        document.updateTriple(start);
        cursorMover.updateCursor();
        s = yl_wy(1) + s;
        return s;
    }

    string YankAction::y0_wy(int m) {
        // yank from the start of line to current position
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return "";
        }
        string s = "";
        cursorMover.moveToFrontOfLine();
        Triple end = document.getTriple();
        s = getRangeText(end, start);
        return s;
    }

    string YankAction::yCaret_wy(int m) {
        // yank from the first non-whitespace char to current position
        Triple start = document.getTriple();
        if (document.getLines()[start.line].size() == 1) {
            return "";
        }
        string s = "";
        cursorMover.moveToFirstCharOfLine();
        Triple end = document.getTriple();
        s += getRangeText(end, start);
        return s;
    }

    string YankAction::yh_wy(int m) {
        // yank m chars to the left
        string s = "";
        Triple start = document.getTriple();
        if (start.index == 0) {
            return "";
        }
        cursorMover.moveLeft(m);
        Triple end = document.getTriple();
        s += getRangeText(end, start);
        return s;
    }

    string YankAction::yl_wy(int m) {
        // yank m chars to the right
        string s = "";
        Triple start = document.getTriple();
        cursorMover.moveRight(m);
        Triple end = document.getTriple();
        s += getRangeText(start, end);
        document.updateTriple(start);
        cursorMover.updateCursor();
        return s;
    }

    string YankAction::yk_wy(int m) {
        int curLine = document.getTriple().line;
        if (curLine == 0) {
            return "";
        }
        string s = "";
        s += yy_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == 0) {
                // no more lines above
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                return s;
            }
            // move up to get the previous line text
            cursorMover.moveUp(1);
            curLine--;
            s = yy_wy(1) + s;
        }
        document.updateTriple({curLine, 0, 0});
        cursorMover.updateCursor();
        return s;
    }

    string YankAction::yj_wy(int m) {
        // yank the line(s) below
        int originalLine = document.getTriple().line;
        int curLine = document.getTriple().line;
        if (curLine == (int)document.getLinesSize() - 1) {
            return "";
        }
        string s = "";
        s += yy_wy(1);
        for (int i = 0; i < m; i++) {
            if (curLine == (int)document.getLinesSize() - 1) {
                document.updateTriple({curLine, 0, 0});
                cursorMover.updateCursor();
                return s;
            }
            cursorMover.moveDown(1);
            curLine++;
            s += document.getLineText(curLine);
        }
        document.updateTriple({originalLine, 0, 0});
        cursorMover.updateCursor();
        return s;
    }












}