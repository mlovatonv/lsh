CPPFLAGS=-std=c++14
OPFLAGS=-O3

all:
	g++ ${CPPFLAGS} ${OPFLAGS} -pthread -o lsh.o src/testLSH.cpp
	g++ ${CPPFLAGS} ${OPFLAGS} -pthread -o kdtree.o src/testKdtree.cpp

clean:
	rm -f lsh.o
	rm -f kdtree.o
