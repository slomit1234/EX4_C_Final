//#define _CRT_SECURE_NO_WARNINGS
#include "edge.h"

int isEdgeExist(struct edge* head, int src)
{
    struct edge* temp = head;
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

void removeEdge(struct edge* head, int src)
{
    struct edge* temp = head;
    struct edge* toDelete = NULL;

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
    struct edge* start1 = (struct edge*)malloc(sizeof(struct edge));

    if (start1)
    {
        start1->src = src;
        start1->dest = dest;
        start1->weight = weight;
        start1->next = NULL;

        start->start = start1;
    }
}

void updateEdge(struct edge* head, int src)
{
    if (head != NULL)
    {
        struct edge* temp = head;
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
    struct edge* temp = start->start;
    struct edge* toAdd = (struct edge*)malloc(sizeof(struct edge));

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
