#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include <memory>

#include "Action.h"
#include "../structs/ActionTypes.h"
#include "./MoveCursor/MoveCursorAction.h"
#include "./ChangeMode/ChangeModeAction.h"
#include "./Delete/DeleteAction.h"
#include "../model/YankRegister.h"
#include "./YankAndPaste/PasteAction.h"
#include "./YankAndPaste/YankAction.h"
#include "./Change/ChangeAction.h"




namespace action {

    class ActionFactory {
        public:

        static unique_ptr<Action> createMoveCursorAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType);

        static unique_ptr<Action> createChangeModeAction(model::Document &document, controller::CursorMover &cursorMover, ActionTypes actionType);

        static unique_ptr<Action> createDeleteAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType, model::YankRegister &yankRegister);

        static unique_ptr<Action> createPasteAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType, model::YankRegister &yankRegister);

        static unique_ptr<Action> createYankAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType, model::YankRegister &yankRegister);

        static unique_ptr<Action> createChangeAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType, model::YankRegister &yankRegister);







    };













}














#endif