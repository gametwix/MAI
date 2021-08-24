CC=gcc

CFLAGS=-c -Wall

all: lb25-26

lb25-26: main.o stack.o arvir.o tree.o
	$(CC) main.o stack.o arvir.o tree.o -o prog

main.o: main.c
	$(CC) $(CFLAGS) main.c

stack.o: stack.c
	$(CC) $(CFLAGS) stack.c

arvir.o: arvir.c
	$(CC) $(CFLAGS) arvir.c

tree.o: tree.c
	$(CC) $(CFLAGS) tree.c

clean:
	rm -rf *.o prog
