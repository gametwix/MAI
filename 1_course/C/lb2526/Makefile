CC=gcc

CFLAGS=-c -Wall

all: lb25-26

lb25-26: main.o queuef.o
	$(CC) main.o queuef.o -o hello

main.o: main.c
	$(CC) $(CFLAGS) main.c

queuef.o: queuef.c
	$(CC) $(CFLAGS) queuef.c

clean:
	rm -rf *.o hello
