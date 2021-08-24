#Вариант 34
CC = gcc
CFLAGS = -g -c -Wall
ADDLIB = -lm

# Реализация 1 или 2
REALIZE_STATIC_LIB = 1

all: static dynamic 

static: static.o libfunc.a
	$(CC) static.o -o static -L. -lfunc $(ADDLIB)
dynamic: main_dynamic.o lib1.so lib2.so
	$(CC) main_dynamic.o -o dynamic $(ADDLIB) -ldl

libfunc_1.o:
	$(CC) $(CFLAGS) -fpic functions_1.c -o libfunc_1.o 
libfunc_2.o:
	$(CC) $(CFLAGS) -fpic functions_2.c -o libfunc_2.o
static.o: main_static.c
	$(CC) $(CFLAGS) main_static.c -o static.o
dynamic.o: main_dynamic.c 
	$(CC) $(CFLAGS) main_dynamic.c -o dynamic.o

libfunc.a: libfunc_$(REALIZE_STATIC_LIB).o
	ar cr libfunc.a libfunc_$(REALIZE_STATIC_LIB).o
lib1.so: libfunc_1.o
	$(CC) -shared libfunc_1.o -o lib1.so 
lib2.so: libfunc_2.o
	$(CC) -shared libfunc_2.o -o lib2.so

clean:
	rm -r *.o *.a *.so static dynamic

