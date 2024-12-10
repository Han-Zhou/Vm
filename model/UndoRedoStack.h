#ifndef UNDOREDOSTACK_H
#define UNDOREDOSTACK_H

#include <stack>
#include <memory>

#include "../action/Action.h"
#include "../structs/ReturnMessage.h"

using namespace std;

namespace action {
    class Action;
}


namespace model {

    class UndoRedoStack {
        stack<unique_ptr<action::Action>> undoStack;
        stack<unique_ptr<action::Action>> redoStack;

        void pushToUndoStack(unique_ptr<action::Action> action);
        void pushToRedoStack(unique_ptr<action::Action> action);
        unique_ptr<action::Action> popFromUndoStack();
        unique_ptr<action::Action> popFromRedoStack();


    public:
        UndoRedoStack() = default;
        ~UndoRedoStack() = default;

        void add(unique_ptr<action::Action> action);

        ReturnMessage undo();

        ReturnMessage redo();



    };



}















#endif