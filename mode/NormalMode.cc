


#include "NormalMode.h"

#include <cmath>

namespace mode {

    ReturnMessage NormalMode::processInput(vector<int> input) {

        
        if (input.size() == 0) {
            return ReturnMessage::RUNNING;
        }
        
        if (input.size() == 1) {
            if (input[0] == Keys::KEY_ESC) {
                return ReturnMessage::SUCCESS;
            }
            if (input[0] == '0') {
                // move to the beginning of the line
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, 1, ActionTypes::MOVE_LINE_0);
                return action->execute();
            }
        }


        int multiplier = extractMultiplier(input);
        if (input.size() == 0) {
            return ReturnMessage::RUNNING;
        }



        if (input.size() == 1) {
            switch (input[0]) {
            case ':': {
                return ReturnMessage::RUNNING;
            }
            case Keys::KEY_LEFT_ARROW: 
            case 'h': { // moves the cursor left
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_LEFT);
                return action->execute();
            }
            case Keys::KEY_DOWN_ARROW:
            case 'j': { // moves the cursor down
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_DOWN);
                return action->execute();
            }
            case Keys::KEY_UP_ARROW:
            case 'k': { // moves the cursor up
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_UP);
                return action->execute();
            }
            case Keys::KEY_RIGHT_ARROW:
            case 'l': { // moves the cursor to the right
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_RIGHT);
                return action->execute();
            }
            case 'i': { // switch to insert mode
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_I);
                return action->execute();
            }
            case 'a': {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_A);
                return action->execute();
            }
            case 'o': {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_O);
                return action->execute();
            }
            case 'I': {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_BIG_I);
                return action->execute();
            }
            case 'A': {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_BIG_A);
                return action->execute();
            }
            case 'O': {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_BIG_O);
                return action->execute();
            }
            case '$': {
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_LINE_$);
                return action->execute();
            }
            case '^': {
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_LINE_caret);
                return action->execute();
            }


            case 'w': {
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_WORD_W);
                return action->execute();
            }
            case 'b': {
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_WORD_B);
                return action->execute();
            }
            case 'W': {
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_WORD_BIG_W);
                return action->execute();
            }
            case 'B': {
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_WORD_BIG_B);
                return action->execute();
            }


            case 'd': {
                return ReturnMessage::RUNNING;
            }
            case 'c': {
                return ReturnMessage::RUNNING;
            }
            case 'y': {
                return ReturnMessage::RUNNING;
            }


            case 'p': {
                auto action = action::ActionFactory::createPasteAction(document, cursorMover, multiplier, ActionTypes::PASTE_P, yankRegister);
                return action->execute();
            }
            case 'P': {
                auto action = action::ActionFactory::createPasteAction(document, cursorMover, multiplier, ActionTypes::PASTE_BIGP, yankRegister);
                return action->execute();
            }


            default:
                break;
            }
            return ReturnMessage::SUCCESS;
        }




        // inputsize = 2
        if (input.size() == 2) {

            switch (input[0]) {
            case 'd': {
                switch(input[1]) {
                    case 'h': 
                    case Keys::KEY_LEFT_ARROW: {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DH, yankRegister);
                        return action->execute();
                    }
                    case 'j': 
                    case Keys::KEY_DOWN_ARROW: {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DJ, yankRegister);
                        return action->execute();
                    }
                    case 'k': 
                    case Keys::KEY_UP_ARROW: {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DK, yankRegister);
                        return action->execute();
                    }
                    case 'l': 
                    case Keys::KEY_RIGHT_ARROW: {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DL, yankRegister);
                        return action->execute();
                    }
                    case 'd': {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DD, yankRegister);
                        return action->execute();
                    }
                    case 'w': {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DW, yankRegister);
                        return action->execute();
                    }
                    case 'W': {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DBIGW, yankRegister);
                        return action->execute();
                    }
                    case 'b': {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DB, yankRegister);
                        return action->execute();
                    }
                    case 'B': {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DBIGB, yankRegister);
                        return action->execute();
                    }
                    case '$': {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_D$, yankRegister);
                        return action->execute();
                    }
                    case '^': {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_DCARET, yankRegister);
                        return action->execute();
                    }
                    case '0': {
                        auto action = action::ActionFactory::createDeleteAction(document, cursorMover, multiplier, ActionTypes::DELETE_D0, yankRegister);
                        return action->execute();
                    }
                }
            }

            

           case 'c': {
                switch(input[1]) {
                    case 'h': 
                    case Keys::KEY_LEFT_ARROW: {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CH, yankRegister);
                        return action->execute();
                    }
                    case 'j': 
                    case Keys::KEY_DOWN_ARROW: {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CJ, yankRegister);
                        return action->execute();
                    }
                    case 'k': 
                    case Keys::KEY_UP_ARROW: {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CK, yankRegister);
                        return action->execute();
                    }
                    case 'l': 
                    case Keys::KEY_RIGHT_ARROW: {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CL, yankRegister);
                        return action->execute();
                    }
                    case 'c': {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CC, yankRegister);
                        return action->execute();
                    }
                    case 'w': {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CW, yankRegister);
                        return action->execute();
                    }
                    case 'W': {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CBIGW, yankRegister);
                        return action->execute();
                    }
                    case 'b': {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CB, yankRegister);
                        return action->execute();
                    }
                    case 'B': {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CBIGB, yankRegister);
                        return action->execute();
                    }
                    case '$': {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_C$, yankRegister);
                        return action->execute();
                    }
                    case '^': {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_CCARET, yankRegister);
                        return action->execute();
                    }
                    case '0': {
                        auto action = action::ActionFactory::createChangeAction(document, cursorMover, multiplier, ActionTypes::CHANGE_C0, yankRegister);
                        return action->execute();
                    }
                }
            } 

            case 'y': {
                switch(input[1]) {
                    case 'h': 
                    case Keys::KEY_LEFT_ARROW: {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YH, yankRegister);
                        return action->execute();
                    }
                    case 'j': 
                    case Keys::KEY_DOWN_ARROW: {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YJ, yankRegister);
                        return action->execute();
                    }
                    case 'k': 
                    case Keys::KEY_UP_ARROW: {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YK, yankRegister);
                        return action->execute();
                    }
                    case 'l': 
                    case Keys::KEY_RIGHT_ARROW: {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YL, yankRegister);
                        return action->execute();
                    }
                    case 'y': {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YY, yankRegister);
                        return action->execute();
                    }
                    case 'w': {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YW, yankRegister);
                        return action->execute();
                    }
                    case 'W': {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YBIGW, yankRegister);
                        return action->execute();
                    }
                    case 'b': {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YB, yankRegister);
                        return action->execute();
                    }
                    case 'B': {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YBIGB, yankRegister);
                        return action->execute();
                    }
                    case '$': {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_Y$, yankRegister);
                        return action->execute();
                    }
                    case '^': {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_YCARET, yankRegister);
                        return action->execute();
                    }
                    case '0': {
                        auto action = action::ActionFactory::createYankAction(document, cursorMover, multiplier, ActionTypes::YANK_Y0, yankRegister);
                        return action->execute();
                    }
                }  

            return ReturnMessage::SUCCESS;
            }

            case ':': {
                return ReturnMessage::RUNNING;
            }
            }
        }



        if (input[0] == ':') {
            if (input.size() == 3) {
                if (input[input.size() - 1] == Keys::KEY_ENTER_override) {
                    switch(input[1]) {
                        case 'q': {
                            auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_Q);
                            return action->execute();
                        }
                        case 'w': {
                            auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_W);
                            return action->execute();
                        }
                        case '0': {
                            auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_0);
                            return action->execute();
                        }
                        case '$': {
                            auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_$);
                            return action->execute();
                        }
                        case '1': 
                        case '2': 
                        case '3': 
                        case '4': 
                        case '5': 
                        case '6': 
                        case '7': 
                        case '8': 
                        case '9': {
                            auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_LINE, input[1] - '0');
                            return action->execute();
                        }
                        return ReturnMessage::SUCCESS;
                    }
                }
                else{ // enter hasn't been pressed
                    switch (input[1]) {
                        case 'q': {
                            return ReturnMessage::RUNNING;
                        }
                        case 'w': {
                            return ReturnMessage::RUNNING;
                        }
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9': {
                            return ReturnMessage::RUNNING;
                        }
                    }
                    return ReturnMessage::SUCCESS;
                }
            }
        
        
            if (input.size() == 4) {
                if (input[input.size() - 1] == Keys::KEY_ENTER_override) {
                    if (input[1] == 'q') {
                        if (input[2] == '!') {
                            auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_Q_EXCLAMATION);
                            return action->execute();
                        }
                        return ReturnMessage::SUCCESS;
                    }
                    if (input[1] == 'w') {
                        if (input[2] == 'q') {
                            auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_WQ);
                            return action->execute();
                        }
                        return ReturnMessage::SUCCESS;
                    }
                    // determine if it is a change line command
                    vector<int> newInput(input.begin() + 1, input.end() - 1);
                    int size = newInput.size();
                    int multiplier = extractMultiplier(newInput);
                    if ((size_t)multiplier < static_cast<size_t>(pow(10, size - 1))) {
                        return ReturnMessage::SUCCESS;
                    }
                    auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_LINE, multiplier);
                    return action->execute();
                }
            }
            else { // > 4 of size for input
                if (input[input.size() - 1] == Keys::KEY_ENTER_override) {
                    vector<int> newInput(input.begin() + 1, input.end() - 1);
                    int size = newInput.size();
                    int lineNumber = extractMultiplier(newInput);
                    if ((size_t)lineNumber <  10^(size - 1)) {
                        return ReturnMessage::SUCCESS;
                    }
                    auto action = action::ActionFactory::createColonAction(document, cursorMover, ActionTypes::COLON_LINE, lineNumber);
                    return action->execute();
                }
            }
        }
    


        





        return ReturnMessage::SUCCESS;
    }








    int NormalMode::extractMultiplier(vector<int> &input) {
        int multiplier = 0;
        int inputSize = input.size();
        for (int i = 0; i < inputSize; i++) {
            if (isDigit(input[0])) {
                multiplier = multiplier * 10 + extractDigit(input[0]);
                input.erase(input.begin());
            }
            else {
                break;
            }
        }
        multiplier = max(1, multiplier);
        // ofstream log("multiplier.log", ios::app);
        // log << "multiplier: " << multiplier << endl;
        return multiplier;
    }







    bool NormalMode::isDigit(int ch) {
        return ((ch >= 48) && (ch <= 57));
    }


    int NormalMode::extractDigit(int ch) {
        return (ch - 48);
    } 
















    
}
