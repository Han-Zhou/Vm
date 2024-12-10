CXX = g++-14.2.0
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g -lncurses
EXEC = vm
OBJECTS = utils/TextWrapper.o model/Document.o controller/CursorMover.o model/UndoRedoStack.o action/MoveCursor/MoveCursorAction.o action/ChangeMode/ChangeModeAction.o action/ActionFactory.o mode/InsertMode.o mode/NormalMode.o view/Window.o view/Cursor.o controller/MainController.o HolyVmEditor.o exmain.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${GIVEN} -o ${EXEC} ${CXXFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
