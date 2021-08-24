CC=gcc

CFLAGS=-c -Wall

all: lb23

lb23: main.o tree.o
	$(CC) main.o tree.o -o prog

main.o: main.c
	$(CC) $(CFLAGS) main.c

tree.o: tree.c
	$(CC) $(CFLAGS) tree.c

clean:
	rm -rf *.o prog
