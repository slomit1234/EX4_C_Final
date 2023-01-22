#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"
#include"Node.h"
#include <stdio.h>
#include <stdlib.h>
#include "Edge.h"


void createHead(struct Graph* head, int src)
{
    struct Node* head1 = (struct Node*)malloc(sizeof(struct Node));
    if (head1)
    {
        head1->src = src;
        head1->next = NULL;
        head->head = head1;

    }
}

void createNode(struct Node* head, int src)
{
    struct Node* temp = head;
    struct Node* toAdd = (struct Node*)malloc(sizeof(struct Node));

    if (toAdd)
    {
        toAdd->src = src;
        toAdd->next = NULL;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = toAdd;
    }
}

void updateNode(struct Node* head, int srcToUpdate)
{
    struct Node* temp = head;
    while (temp->next != NULL && temp->src != srcToUpdate)
    {
        temp = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->src = srcToUpdate;
    }
}

void removeNode(struct Node* head, int toDelete)
{
    struct Node* temp = head;
    struct Node* Delete;

    if (head->src != toDelete)
    {
        while (temp->next != NULL && temp->next->src != toDelete)
        {
            temp = temp->next;
        }
        Delete = temp->next;
        temp->next = temp->next->next;

        free(Delete); //free Memory of node to delete
    }
    else
    {
        Delete = head;
        head = head->next;
        free(Delete);
    }
}

int isNodeExist(struct Node* head, int isExist)
{
    struct Node* temp = head;
    int flag = 0;

    if (temp->src != isExist)
    {
        while (temp->next != NULL && temp->next->src != isExist)
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
