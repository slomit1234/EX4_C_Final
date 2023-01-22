#ifndef edgesh
#define edgesh
#include"Graph.h"
#include "Node.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void createStart(struct Graph* , int , int , int );
void createEdge(struct Graph* , int , int , int );
void updateEdge(struct Edge* , int );
int isEdgeExist(struct Edge* , int );
void removeEdge(struct Edge* , int );


#endif