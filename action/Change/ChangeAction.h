#ifndef CHANGE_ACTION_H
#define CHANGE_ACTION_H


#include "../Action.h"
#include "../../model/Document.h"
#include "../../model/YankRegister.h"
#include "../../controller/CursorMover.h"
#include "../../structs/ActionTypes.h"
#include "../../structs/Triple.h"
#include "../../structs/ReturnMessage.h"



namespace action {

    class ChangeAction : public Action {
        model::Document &document;
        controller::CursorMover &cursorMover;
        int multiplier;
        ActionTypes actionType;
        model::YankRegister &yankRegister;



        string deleteRange(const Triple &start, const Triple &end);



        // actions for deleting a char
        ReturnMessage ch(int m);
        ReturnMessage cl(int m);
        ReturnMessage ck(int m);
        ReturnMessage cj(int m);

        // more complex change actions
        ReturnMessage cc(int m);
        ReturnMessage cw(int m);
        ReturnMessage cW(int m);
        ReturnMessage cb(int m);
        ReturnMessage cB(int m);
        
        ReturnMessage c$(int m);
        ReturnMessage cCaret(int m);
        ReturnMessage c0(int m);


        // a copy of the above but without yanking
        string ch_wy(int m);
        string cl_wy(int m);
        string ck_wy(int m);
        string cj_wy(int m);
        string cc_wy(int m);
        string cw_wy(int m);
        string cW_wy(int m);
        string cb_wy(int m);
        string cB_wy(int m);
        string c$_wy(int m);
        string cCaret_wy(int m);
        string c0_wy(int m);
        
        
        public:
        ChangeAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier,  ActionTypes actionType, model::YankRegister &yr): document{document}, cursorMover{cursorMover}, multiplier{multiplier}, actionType{actionType}, yankRegister{yr} { }

        ~ChangeAction() = default;

        ReturnMessage execute() override;

        ReturnMessage undo() override;
    };


}














#endif