#ifndef nodes
#define nodes
#include"Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Edge.h"


void createHead(struct Graph*, int );
void createNode(struct Node*, int );
void updateNode(struct Node*, int );
void removeNode(struct Node*, int );
int isNodeExist(struct Node*, int );

#endif
