#include "YankRegister.h"

#include <fstream>

using namespace std;

namespace model {

    void YankRegister::yank(const string text) {
        ofstream log("yank.log", ios::app);
        this->text = text;
        log << "Yanked: " << text << endl;
    }

    const string &YankRegister::getText() const {
        return text;
    }
}
