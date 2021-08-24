CC = gcc
CFLAGS = -c -Wall
FINALFLAGS = -pthread -o

all: main

main: main.o bitonic.o
	$(CC) main.o bitonic.o $(FINALFLAGS) main
main.o: src/main.c src/bitonic.h
	$(CC) $(CFLAGS) src/main.c
bitonic.o: src/bitonic.c src/bitonic.h
	$(CC) $(CFLAGS) src/bitonic.c
clean:
	rm -r *.o main
