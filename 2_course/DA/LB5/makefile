CC=g++

CFLAGS=--std=c++14 -c -O2
all: lb5

lb5: clean main.o SuffTree.o
	$(CC) main.o SuffTree.o -o solution
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
SuffTree.o: SuffTree.cpp
	$(CC) $(CFLAGS) SuffTree.cpp
clean:
	rm -rf *.o solution
