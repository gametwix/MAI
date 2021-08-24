CC = g++
FINALFLAGS =-lzmq -o

all: A B C

A: A.cpp
	$(CC) A.cpp $(FINALFLAGS) A
B: B.cpp
	$(CC) B.cpp $(FINALFLAGS) B
C: C.cpp
	$(CC) C.cpp $(FINALFLAGS) C
clean:
	rm -r A B C