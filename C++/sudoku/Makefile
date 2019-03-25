
COMP=g++
OPTS=-std=c++11 -I. -g

GPP=$(COMP) $(OPTS)

main: sudoku.o colour.o boardrunner.o main.cpp
	$(GPP) -c main.cpp
	$(GPP) -o main main.o boardrunner.o sudoku.o colour.o

sudoku.o: sudoku.h sudoku.cpp
	$(GPP) -c sudoku.cpp

boardrunner.o: boardrunner.h boardrunner.cpp
	$(GPP) -c boardrunner.cpp

colour.o: colour.h colour.cpp
	$(GPP) -c colour.cpp


clean:
	-rm -f main *.o



