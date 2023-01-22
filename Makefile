CFLAGS = -g -Wall
CC = gcc

clean:
	rm -f *.o *.so $(OUTPUT)

# units
graph.o: graph.c node.h graph.h edge.h
	$(CC) -c $(CFLAGS) graph.c

node.o: node.c node.h graph.h edge.h
	$(CC) -c $(CFLAGS) node.c

edge.o: edge.c node.h graph.h edge.h
	$(CC) -c $(CFLAGS) edge.c

main.o: main.c node.h graph.h edge.h
	$(CC) -c $(CFLAGS) main.c

graph: main.o graph.o node.o edge.o
	$(CC) $(CFLAGS) -o graph main.o graph.o node.o edge.o

# build
all: graph

.PHONY: all clean graph