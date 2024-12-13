#ifndef YANK_ACTION_H 
#define YANK_ACTION_H


#include <string>

using namespace std;

#include "../Action.h"
#include "../../model/Document.h"
#include "../../model/YankRegister.h"
#include "../../controller/CursorMover.h"
#include "../../structs/ActionTypes.h"
#include "../../structs/Triple.h"
#include "../../structs/ReturnMessage.h"



namespace action {

    class YankAction : public Action {
        model::Document &document;
        controller::CursorMover &cursorMover;
        int multiplier;
        ActionTypes actionType;
        model::YankRegister &yankRegister;


        ReturnMessage yy(int m);

        ReturnMessage yh(int m);
        ReturnMessage yl(int m);
        ReturnMessage yk(int m);
        ReturnMessage yj(int m);

        ReturnMessage yw(int m);
        ReturnMessage yW(int m);
        ReturnMessage yb(int m);
        ReturnMessage yB(int m);
        
        ReturnMessage y$(int m);
        ReturnMessage yCaret(int m);
        ReturnMessage y0(int m);


        // Helper function to get text from a given range without changing the YankRegister
        string yy_wy(int m);

        string yh_wy(int m);
        string yl_wy(int m);
        string yk_wy(int m);
        string yj_wy(int m);
        string yw_wy(int m);
        string yW_wy(int m);
        string yb_wy(int m);
        string yB_wy(int m);
        
        string y$_wy(int m);
        string yCaret_wy(int m);
        string y0_wy(int m);



        string getRangeText(const Triple &start, const Triple &end);

        
        public:
        YankAction(model::Document &document, controller::CursorMover &cursorMover, int multiplier,  ActionTypes actionType, model::YankRegister &yr): document{document}, cursorMover{cursorMover}, multiplier{multiplier}, actionType{actionType}, yankRegister{yr} { }

        ~YankAction() = default;

        ReturnMessage execute() override;

        ReturnMessage undo() override;
    };


}










#endif
