#include "UndoRedoStack.h"


namespace model {

    void UndoRedoStack::pushToUndoStack(unique_ptr<action::Action> action) {
        undoStack.push(move(action));
    }

    void UndoRedoStack::pushToRedoStack(unique_ptr<action::Action> action) {
        redoStack.push(move(action));
    }

    unique_ptr<action::Action> UndoRedoStack::popFromUndoStack() {
        // if (undoStack.empty()) {
        //     return nullptr;
        // }
        unique_ptr<action::Action> action = move(undoStack.top());
        undoStack.pop();
        return action;
    }

    unique_ptr<action::Action> UndoRedoStack::popFromRedoStack() {
        unique_ptr<action::Action> action = move(redoStack.top());
        redoStack.pop();
        return action;
    }




    void UndoRedoStack::add(unique_ptr<action::Action> action) {
        pushToUndoStack(move(action));
    }




    ReturnMessage UndoRedoStack::undo() {
        if (!undoStack.empty()) {
            unique_ptr<action::Action> action = popFromUndoStack();
            ReturnMessage rm = action->undo();
            pushToRedoStack(move(action));
            return rm;
        }
        return ReturnMessage::SUCCESS;
    }


    ReturnMessage UndoRedoStack::redo() {
        if (!redoStack.empty()) {
            unique_ptr<action::Action> action = popFromRedoStack();
            ReturnMessage rm = action->execute();
            pushToUndoStack(move(action));
            return rm;
        }
        return ReturnMessage::SUCCESS;
    }





}
