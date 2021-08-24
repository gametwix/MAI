CC=g++

CFLAGS=--std=c++14 -c -O3

all: lb1 benchmark



lb1: main.o 
	$(CC) main.o -o solution
benchmark: benchmark.cpp
	$(CC) $(CFLAGS) benchmark.cpp -o benchmark
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
clean:
	rm -rf *.o solution
