#ifndef GRAPH_
#define GRAPH_
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <limits.h>
#include <stdbool.h>

#define CHUNK 200
#define INF 99999
#define MAX_NODES 100


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
#include"Edge.h"
#include"Node.h"

//new dijestra
//Algo File
//all other
int* InitializeMatrix(struct Graph* , int );
char* str_slice(char str[], int , int );
char* readinput(int* len);
char* getD(char input[], struct Graph* );
char* getB(char input[], struct Graph* );
char* getS(char s[], struct Graph* , int );
char* getT(char input[], struct Graph* , int );
void OptionManager(char , char* , int );
void deleteGraph(struct Graph* );
struct Graph* createGraph(char** , int );

void new_shortest_path(int*, int, int*, int); //d
void N_shortest_path_dijkstra(int src, int dest, int num_vertices, int* edges);

void new_shortest_path_dijkstra(int , int , int , int* ); //V
void permute(int* arr, int l, int r, int num_vertices, int* edges, int* shortest_path, int* shortest_path_length);
int calculate_path_cost(int* permutation, int num_nodes, int num_vertices, int* edges, int* shortest_path);
void T_shortest_path(int* adj_matrix, int num_vertices, int* nods, int num_nodes);
int forT_dijkstra(int src, int dest, int num_vertices, int* edges);

#endif