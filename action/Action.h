#ifndef ACTION_H
#define ACTION_H 



#include "../structs/ReturnMessage.h"


namespace action {

    class Action {
    public:

        virtual ReturnMessage execute() = 0;
        virtual ReturnMessage undo() = 0;
        virtual ~Action() = default;
    };





}

























#endif