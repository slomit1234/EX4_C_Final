#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Edge.h"


int isEdgeExist(struct Edge* head, int src)
{
    struct Edge* temp = head;
    int flag = 0;
    if (temp->src != src)
    {
        while (temp->next != NULL && temp->next->src != src)
        {
            temp = temp->next;
        }

        if (temp->next != NULL)
        {
            flag = 1;
        }
    }
    else
    {
        flag = 1;
    }

    return flag;
}

void removeEdge(struct Edge* head, int src)
{
    struct Edge* temp = head;
    struct Edge* toDelete = NULL;

    if (!temp)
    {
        return;
    }

    while (temp != NULL && temp->next!=NULL)
    {
        if (temp->src == src)
        {
            toDelete = head;
            head = head->next;
            free(toDelete);
            temp = head;
        }
        else if (temp->next->src == src)
        {
            toDelete = temp->next;
            temp->next = temp->next->next;

            free(toDelete); //free Memory of node to delete
            //break;
        }
        else
        {
            temp = temp->next;
        }
            
    }
}

void createStart(struct Graph* start, int src, int dest, int weight)
{
    struct Edge* start1 = (struct Edge*)malloc(sizeof(struct Edge));

    if (start1)
    {
        start1->src = src;
        start1->dest = dest;
        start1->weight = weight;
        start1->next = NULL;

        start->start = start1;
    }
}

void updateEdge(struct Edge* head, int src)
{
    if (head != NULL)
    {
        struct Edge* temp = head;
        while (temp->next != NULL)
        {
            if (temp->src == src)
            {
                removeEdge(head, temp->src);
            }
            temp = temp->next;
        }
    }
}

void createEdge(struct Graph* start, int src, int dest, int weight)
{
    struct Edge* temp = start->start;
    struct Edge* toAdd = (struct Edge*)malloc(sizeof(struct Edge));

    if (toAdd)
    {
        toAdd->src = src;
        toAdd->dest = dest;
        toAdd->weight = weight;
        toAdd->next = NULL;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = toAdd;
    }
}
