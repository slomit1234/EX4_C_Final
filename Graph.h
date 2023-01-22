#ifndef GRAPH_
#define GRAPH_

struct Node
{
    int src;
    struct Node* next;
};

struct Edge {
    int src, dest, weight;
    struct Edge* next;
};

struct Graph
{
    struct Node* head;
    struct Edge* start;
};

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

#define CHUNK 200
#define INF 99999
#define MAX_NODES 100

#include"Edge.h"
#include"Node.h"

char* readinput(int* len);
void OptionManager(char , char* , int );

int* InitializeMatrix(struct Graph* , int );
char* str_slice(char str[], int , int );

char* getD(char input[], struct Graph* );
char* getB(char input[], struct Graph* );
char* getS(char s[], struct Graph* , int );
char* getT(char input[], struct Graph* , int );

void deleteGraph(struct Graph* );
struct Graph* createGraph(char** , int );

//void new_shortest_path(int*, int, int*, int); //d
//void N_shortest_path_dijkstra(int , int , int , int* );

void new_shortest_path_dijkstra(int , int , int , int* ); //V
void permute(int* , int , int , int , int* , int* , int* );
int calculate_path_cost(int* , int , int* , int* , int* );
void T_shortest_path(int* , int , int* , int );
int forT_dijkstra(int , int , int , int* );

#endif
