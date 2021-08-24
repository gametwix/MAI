CC = g++
FINALFLAGS =-lzmq -o

all: client worker

client: client.cpp
	$(CC) client.cpp $(FINALFLAGS) client
worker: worker.cpp
	$(CC) worker.cpp $(FINALFLAGS) worker
clean:
	rm -r client worker