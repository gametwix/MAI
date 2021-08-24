CC=gcc

CFLAGS=-g -c -Wall

all: kp7

kp7: main.o matrix.o
	$(CC) -g main.o matrix.o -o prog

main.o: main.c
	$(CC) $(CFLAGS) main.c

matrix.o: matrix.c
	$(CC) $(CFLAGS) matrix.c

clean:
	rm -rf *.o prog
