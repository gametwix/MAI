CC = g++
CFLAGS = -c -O3 --std=c++14 -Wall

all: main

main: main.o bignum.o
	$(CC) main.o sufftree.o -o solution
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
sufftree.o: SuffTree.cpp SuffTree.hpp
	$(CC) $(CFLAGS) SuffTree.cpp
clean:
	rm -rf *.o solution

clean_tar:
	rm solution.tar
	make clean_folder

clean_folder:
	rm -rf solution

get_sol: main.cpp SuffTree.cpp SuffTree.hpp Makefile
	mkdir solution
	cp main.cpp SuffTree.cpp SuffTree.hpp Makefile ./solution
	tar -rf solution.tar solution
	#make clean_folder