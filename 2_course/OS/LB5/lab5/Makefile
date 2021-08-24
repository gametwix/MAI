CC = gcc
CFLAGS = -c
ADDLIB = -lm

REALIZE_STATIC_LIB = 1

all: linking dynamic 

linking: linking.o lib$(REALIZE_STATIC_LIB).so 
	$(CC) linking.o -o linking -L. -l$(REALIZE_STATIC_LIB) $(ADDLIB) 
dynamic: main_dynamic.o lib1.so lib2.so
	$(CC) main_dynamic.o -o dynamic $(ADDLIB) -ldl 

libfunc_1.o:
	$(CC) $(CFLAGS) -fpic functions_1.c -o libfunc_1.o 
libfunc_2.o:
	$(CC) $(CFLAGS) -fpic functions_2.c -o libfunc_2.o
linking.o: main_static.c
	$(CC) $(CFLAGS) main_static.c -o linking.o
dynamic.o: main_dynamic.c 
	$(CC) $(CFLAGS) main_dynamic.c -o dynamic.o


lib1.so: libfunc_1.o
	$(CC) -shared libfunc_1.o -o lib1.so $(ADDLIB)
lib2.so: libfunc_2.o
	$(CC) -shared libfunc_2.o -o lib2.so $(ADDLIB)

clean:
	rm -r *.o *.so linking dynamic