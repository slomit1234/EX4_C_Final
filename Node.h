#ifndef nodes
#define nodes
#include <stdio.h>
#include <stdlib.h>
#include<string.h>


#include"Graph.h"
void createHead(struct Graph* head, int src);
void createNode(struct Node* head, int src);
void updateNode(struct Node* head, int srcToUpdate);
void removeNode(struct Node* head, int toDelete);
int isNodeExist(struct Node* head, int isExist);

#endif