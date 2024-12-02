g++20 = g++ -std=c++20 -fmodules-ts -Wall -g
g++20h = g++ -std=c++20 -fmodules-ts -c -x c++-system-header

.PHONY: all main run rc ro test rmall move

all: main
	@echo "All done"


exmain.o: exmain.cc
	@${g++20} -c exmain.cc

./utils/FileReader.o: ./utils/FileReader.cc
	@${g++20} -c ./utils/FileReader.cc

./utils/TextWrapper.o: ./utils/TextWrapper.cc
	@${g++20} -c ./utils/TextWrapper.cc

./model/Document.o: ./model/Document.cc
	@${g++20} -c ./model/Document.cc

window.o: window.cc
	@${g++20} -c window.cc

main: exmain.o ./utils/FileReader.o ./utils/TextWrapper.o ./model/Document.o window.o move
	@${g++20} exmain.o ./utils/FileReader.o ./utils/TextWrapper.o ./model/Document.o -lncurses -o exec

move:
	@mv FileReader.o ./utils
	@mv TextWrapper.o ./utils
	@mv Document.o ./model

run: main
	@./a4q1

rc:
	@rm -r *.cache

ro:
	@rm *.o
	@rm utils/*.o
	@rm model/*.o

rmall:
	@rm -r *.cache *.o exec

test:
	@./tests.sh
