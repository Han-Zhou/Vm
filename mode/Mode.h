#ifndef MODE_H
#define MODE_H

#include <vector>
#include <string>

#include "../structs/ReturnMessage.h"

using namespace std;

namespace mode {

    class Mode {

    public: 
        virtual ReturnMessage processInput(vector<int> input) = 0;
        virtual ~Mode() = default;
    };
}




#endif