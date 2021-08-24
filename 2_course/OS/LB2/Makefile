CC = gcc
CFLAGS = -c -Wall

all: parent child

parent: main.o
	$(CC) main.o -o parent
parent.o: main.c
	$(CC) $(CFLAGS) main.c
child: sum.o
	$(CC) sum.o -o child
sum.o: sum.c
	$(CC) $(CFLAGS) sum.c
clean:
	rm -r *.o parent child

