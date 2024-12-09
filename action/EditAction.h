#ifndef EDITACTION_H
#define EDITACTION_H

#include "Action.h"
#include "../model/Document.h"
#include "../controller/CursorMover.h"



namespace action {
    
        class EditAction : public Action {
            model::Document &document;
            controller::CursorMover &cursorMover;
    
        public:
            EditAction(model::Document &document, controller::CursorMover &cursorMover): document{document}, cursorMover{cursorMover} {}
    
            void execute() override;
            void undo() override;
            ~EditAction() = default;
    
        };
    
        void EditAction::execute() {
            // document.insertChar(cursorMover.getChar());
        }
    
        void EditAction::undo() {
            document.deleteChar();
            
        };

}

















#endif