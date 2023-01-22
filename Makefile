CFLAGS = -g -Wall
CC = gcc

clean:
	rm -f *.o *.so $(OUTPUT)

# units
Graph.o: Graph.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Graph.c

Node.o: Node.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Node.c

Edge.o: Edge.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Edge.c

Main.o: Main.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Main.c

Graph: Main.o Graph.o Node.o Edge.o
	$(CC) $(CFLAGS) -o Graph Main.o Graph.o Node.o Edge.o

# build
all: Graph

.PHONY: all clean Graph