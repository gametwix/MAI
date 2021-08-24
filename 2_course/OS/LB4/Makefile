CC = gcc
CFLAGS = -c -Wall
FINALFLAGS = -pthread -lrt -o

all: parent child

parent: parent.o
	$(CC) parent.o $(FINALFLAGS) parent
parent.o: parent.c
	$(CC) $(CFLAGS) parent.c
child: child.o
	$(CC) child.o $(FINALFLAGS) child
child.o: child.c
	$(CC) $(CFLAGS) child.c
clean:
	rm -r *.o parent child