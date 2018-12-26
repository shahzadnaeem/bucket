
COMP=g++
OPTS=-std=c++14 -I. -g

GPP=$(COMP) $(OPTS)

main: main.o
	$(GPP) -o main main.o

main.o: main.cpp object.h benchmarks.h
	$(GPP) -c -o $(@) $(<)

object.o: object.cpp object.h
	$(GPP) -c -o $(@) $(<)

clean:
	-rm -f main *.o



