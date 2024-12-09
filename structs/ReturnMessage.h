#ifndef RETURNMESSAGE_H
#define RETURNMESSAGE_H

#include <string>

enum ReturnMessage {
    RUNNING,
    INSERT,
    NORMAL,
    QUIT,
    SUCCESS, // success means we have to clear the inputbuffer
    ERROR,
};




#endif