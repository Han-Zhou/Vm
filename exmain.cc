#include "view/Window.h"
#include <string>
#include <iostream>

#include "model/Document.h"
#include "view/Window.h"
#include "HolyVmEditor.h"


using namespace std;


using namespace std;

int main() {
    // cout << "HELLO" << endl;
    string fileName = "view/Cursor.cc";
    // model::Document d(fileName);
    // view::Window w = view::Window::getInstance(d);
    // cout << "main filename: " << fileName << endl;

    HolyVmEditor editor(fileName);

    // for (string &s : d.getWrappedLines(w.getCOLS())) {
    //     cout << s << endl;
    // }

    editor.run();

    

}
