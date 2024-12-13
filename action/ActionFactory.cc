#include "ActionFactory.h"


namespace action {

    unique_ptr<Action> ActionFactory::createMoveCursorAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType) {
        return make_unique<MoveCursorAction>(document, cursorMover, multiplier, actionType);
    }

    unique_ptr<Action> ActionFactory::createChangeModeAction(model::Document &document, controller::CursorMover &cursorMover, ActionTypes actionType) {
        return make_unique<ChangeModeAction>(document, cursorMover, actionType);
    }

    unique_ptr<Action> ActionFactory::createDeleteAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType, model::YankRegister &yankRegister) {
        return make_unique<DeleteAction>(document, cursorMover, multiplier, actionType, yankRegister);
    }

    unique_ptr<Action> ActionFactory::createPasteAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType, model::YankRegister &yankRegister) {
        return make_unique<PasteAction>(document, cursorMover, multiplier, actionType, yankRegister);
    }

    unique_ptr<Action> ActionFactory::createYankAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType, model::YankRegister &yankRegister) {
        return make_unique<YankAction>(document, cursorMover, multiplier, actionType, yankRegister);
    }

    unique_ptr<Action> ActionFactory::createChangeAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier, ActionTypes actionType, model::YankRegister &yankRegister) {
        return make_unique<ChangeAction>(document, cursorMover, multiplier, actionType, yankRegister);
    }

    unique_ptr<Action> ActionFactory::createColonAction(model::Document &document, controller::CursorMover &cursorMover, ActionTypes actionType, int lineNumber) {
        return make_unique<ColonAction>(document, cursorMover, actionType, lineNumber);
    }






    

}