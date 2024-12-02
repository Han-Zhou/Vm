#include "Window.h"
#include <string>
#include <iostream>

#include "model/Document.h"

using namespace std;

int main() {
    cout << "HELLO" << endl;
    string fileName = "test";
    view::Window w;
    cout << "main filename: " << fileName << endl;
    Document d(fileName);

    w.run(d.getWrappedLines(w.getCOLS()));
}