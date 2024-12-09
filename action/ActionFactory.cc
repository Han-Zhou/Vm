#include "ActionFactory.h"


namespace action {

    unique_ptr<Action> ActionFactory::createMoveCursorAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType) {
        return make_unique<MoveCursorAction>(document, cursorMover, multiplier, actionType);
    }

    unique_ptr<Action> ActionFactory::createChangeModeAction(model::Document &document, controller::CursorMover &cursorMover, ActionTypes actionType) {
        return make_unique<ChangeModeAction>(document, cursorMover, actionType);
    }

}