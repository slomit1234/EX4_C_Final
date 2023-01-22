
CFLAGS = -g -Wall
OBJ = Graph.o Node.o Edge.o
CC = gcc

all: output functions

Graph.o: Graph.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Graph.c

Node.o: Node.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Node.c

Edge.o: Edge.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Edge.c

libfunctions.so: $(OBJ)
	$(CC) -shared -fPIC -o libfunctions.so $(OBJ)

functions: libfunctions.so

Main.o: Main.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Main.c

output: Main.o libfunctions.so
	$(CC) $(CFLAGS) -o Graph Main.o ./libfunctions.so

.PHONY: all clean functions output

clean:
	rm -f *.o *.so $(OUTPUT)