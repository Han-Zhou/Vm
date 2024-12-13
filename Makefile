CXX = g++-14.2.0
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g -lncurses
EXEC = vm
OBJECTS = utils/TextWrapper.o utils/FileSaver.o model/Document.o model/YankRegister.o controller/CursorMover.o model/UndoRedoStack.o action/YankAndPaste/PasteAction.o action/YankAndPaste/YankAction.o action/Colon/ColonAction.o action/MoveCursor/MoveCursorAction.o action/ChangeMode/ChangeModeAction.o action/Delete/DeleteAction.o  action/Change/ChangeAction.o action/ActionFactory.o mode/InsertMode.o mode/NormalMode.o view/Window.o view/Cursor.o controller/MainController.o HolyVmEditor.o exmain.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${GIVEN} -o ${EXEC} ${CXXFLAGS}

# -include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
