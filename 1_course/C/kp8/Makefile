CC=gcc

CFLAGS= -c -Wall

all: kp8

kp8: main.o matrix.o
	$(CC) main.o list.o -o prog

main.o: main.c
	$(CC) $(CFLAGS) main.c

matrix.o: list.c
	$(CC) $(CFLAGS) list.c

clean:
	rm -rf *.o prog
