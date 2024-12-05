#include "HolyVmEditor.h"






void HolyVmEditor::run() {
    cout << "running" << endl;
    window.init();
    cout << "window initialized" << endl;
    mvprintw(0, 0, "window initialized");
    window.run();
    while (true) {
        string returnStatus = controller->processInput();
        if (returnStatus == "quit") {
            break;
        }
        window.run();
    }
    
}


