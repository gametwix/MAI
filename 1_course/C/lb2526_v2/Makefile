CC=gcc

CFLAGS=-c -Wall

all: lb25-26

lb25-26: main.o deque.o
	$(CC) main.o deque.o -o prog

main.o: main.c
	$(CC) $(CFLAGS) main.c

deque.o: deque.c
	$(CC) $(CFLAGS) deque.c

clean:
	rm -rf *.o prog
