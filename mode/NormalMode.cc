


#include "NormalMode.h"

namespace mode {

    ReturnMessage NormalMode::processInput(vector<int> input) {

        // ofstream log("normal.log", ios::app);
        // log << "input: ";
        // for (int i = 0; i < input.size(); i++) {
        //     log << input[i] << " ";
        // }
        
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

            if (input[0] == 'h') { // moves the cursor left
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_LEFT);
                return action->execute();
            }
            else if (input[0] == 'j') { // moves the cursor down
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_DOWN);
                return action->execute();
            }
            else if (input[0] == 'k') { // moves the cursor up
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_UP);
                return action->execute();
            }
            else if (input[0] == 'l') { // moves the cursor to the right
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_RIGHT);
                return action->execute();
            }

            if (input[0] == 'i') { // switch to insert mode
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_I);
                return action->execute();
            }
            else if (input[0] == 'a') {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_A);
                return action->execute();
            }
            else if (input[0] == 'o') {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_O);
                return action->execute();
            }
            else if (input[0] == 'I') {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_BIG_I);
                return action->execute();
            }
            else if (input[0] == 'A') {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_BIG_A);
                return action->execute();
            }
            else if (input[0] == 'O') {
                auto action = action::ActionFactory::createChangeModeAction(document, cursorMover, ActionTypes::CHANGE_TO_INSERT_BIG_O);
                return action->execute();
            }
            else if (input[0] == '$') {
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_LINE_$);
                return action->execute();
            }
            else if (input[0] == '^') {
                auto action = action::ActionFactory::createMoveCursorAction(document, cursorMover, multiplier, ActionTypes::MOVE_LINE_caret);
                return action->execute();
            }




            return ReturnMessage::SUCCESS;
        }






        





        return ReturnMessage::RUNNING;
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
