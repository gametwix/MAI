CC = g++
CFLAGS = -c -O3 --std=c++14 -Wall

all: main

main: main.o bignum.o
	$(CC) main.o bignum.o -o solution
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
bignum.o: bignum.cpp
	$(CC) $(CFLAGS) bignum.cpp
clean:
	rm -rf *.o solution

clean_tar:
	rm solution.tar
	make clean_folder

clean_folder:
	rm -rf solution

get_sol: main.cpp bignum.cpp bignum.hpp Makefile
	mkdir solution
	cp main.cpp bignum.cpp bignum.hpp Makefile ./solution
	tar -rf solution.tar solution
	#make clean_folder

