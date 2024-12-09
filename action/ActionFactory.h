#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include <memory>

#include "Action.h"
#include "../structs/ActionTypes.h"
#include "./MoveCursor/MoveCursorAction.h"
#include "./ChangeMode/ChangeModeAction.h"





namespace action {

    class ActionFactory {
        public:

        static::unique_ptr<Action> createMoveCursorAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType);

        static::unique_ptr<Action> createChangeModeAction(model::Document &document, controller::CursorMover &cursorMover, ActionTypes actionType);





    };













}














#endif