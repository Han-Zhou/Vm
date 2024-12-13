#ifndef YANKREGISTER_H
#define YANKREGISTER_H


#include <string>


using namespace std;

namespace action {
    class DeleteAction;
    class YankAction;
    class ChangeAction;
}

namespace model {

    // stores the yanked text
    class YankRegister {
        string text = "";

        YankRegister() {}

    protected:
        void yank(const string text);

    public:
        friend action::DeleteAction;
        friend action::YankAction;
        friend action::ChangeAction;


        YankRegister(const YankRegister&) = delete;
        YankRegister& operator=(const YankRegister&) = delete;

        static YankRegister& getInstance() {
            static YankRegister instance;
            return instance;
        }

        const string &getText() const;
    };
}











#endif