#include "view/Window.h"
#include <string>
#include <iostream>

#include "model/Document.h"
#include "view/Window.h"
#include "HolyVmEditor.h"




using namespace std;

int main(int argc, char *argv[]) {
    // cout << "HELLO" << endl;
    // string fileName = "view/Cursor.cc";

    string fileName = "test";
    // model::Document d(fileName);
    // view::Window w = view::Window::getInstance(d);
    // cout << "main filename: " << fileName << endl;

    if (argc == 2) {
        fileName = argv[1];
    }
    else if (argc > 2) {
        cout << "Usage: ./vm [filename]" << endl;
        return 1;
    }

    HolyVmEditor editor(fileName);

    // for (string &s : d.getWrappedLines(w.getCOLS())) {
    //     cout << s << endl;
    // }

    editor.run();
}