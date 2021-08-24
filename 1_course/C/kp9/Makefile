CC=gcc

CFLAGS= -c -Wall -g

LFLAGS= -g -lm

all: kp9

kp9: main.o list.o
	$(CC) $(LFLAGS) main.o list.o -o prog

main.o: main.c
	$(CC) $(CFLAGS) main.c

list.o: list.c
	$(CC) $(CFLAGS) list.c

clean:
	rm -rf *.o prog
