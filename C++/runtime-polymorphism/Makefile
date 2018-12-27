
COMP=g++
OPTS=-std=c++17 -I. -g

GPP=$(COMP) $(OPTS)

main: main.o
	$(GPP) -o main main.o

main.o: main.cpp object.h benchmarks.h
	$(GPP) -c -o $(@) $(<)

misc: misc.cpp
	$(GPP) -o $(@) $(<)

clean:
	-rm -f misc main *.o



