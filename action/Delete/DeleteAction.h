#ifndef DELETE_ACTION_H 
#define DELETE_ACTION_H


#include "../Action.h"
#include "../../model/Document.h"
#include "../../model/YankRegister.h"
#include "../../controller/CursorMover.h"
#include "../../structs/ActionTypes.h"
#include "../../structs/Triple.h"
#include "../../structs/ReturnMessage.h"



namespace action {

    class DeleteAction : public Action {
        model::Document &document;
        controller::CursorMover &cursorMover;
        int multiplier;
        ActionTypes actionType;
        model::YankRegister &yankRegister;



        string deleteRange(const Triple &start, const Triple &end);



        // actions for deleting a char
        ReturnMessage dh(int m);
        ReturnMessage dl(int m);
        ReturnMessage dk(int m);
        ReturnMessage dj(int m);

        // more complex delete actions
        ReturnMessage dd(int m);
        ReturnMessage dw(int m);
        ReturnMessage dW(int m);
        ReturnMessage db(int m);
        ReturnMessage dB(int m);
        
        ReturnMessage d$(int m);
        ReturnMessage dCaret(int m);
        ReturnMessage d0(int m);


        // a copy of the above but without yanking
        string dh_wy(int m);
        string dl_wy(int m);
        string dk_wy(int m);
        string dj_wy(int m);
        string dd_wy(int m);
        string dw_wy(int m);
        string dW_wy(int m);
        string db_wy(int m);
        string dB_wy(int m);
        string d$_wy(int m);
        string dCaret_wy(int m);
        string d0_wy(int m);
        
        
        public:
        DeleteAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier,  ActionTypes actionType, model::YankRegister &yr): document{document}, cursorMover{cursorMover}, multiplier{multiplier}, actionType{actionType}, yankRegister{yr} { }

        ~DeleteAction() = default;

        ReturnMessage execute() override;

        ReturnMessage undo() override;
    };;


}














#endif