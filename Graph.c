//#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"

int theShortestPathElement = INF;


int* InitializeMatrix(struct Graph* g, int numOfNodes)
{
    int SqueredNum = numOfNodes * numOfNodes;
    struct Edge* temp;
    struct Node* t = g->head;
    struct Node* ith = NULL;
    struct Node* jth = NULL;
    int ci = 0;
    int cj = 0;
    int* mat = (int*)malloc(SqueredNum*sizeof(int));
    int flag1 = 0;
    int flag2 = 0;

    if (!mat)
    {
        return NULL;
    }

    for (int i = 0; i < numOfNodes; i++)
    {
        for (int j = 0; j < numOfNodes; j++)
        {
            flag1 = 0;
            flag2 = 0;
            ci = 0;
            cj = 0;
            t = g->head;

            while (t != NULL)
            {
                if (i == ci)
                {
                    ith = t;
                    flag1 = 1;
                }
                if (j == cj)
                {
                    jth = t;
                    flag2 = 1;
                }
                ci++;
                cj++;
                t = t->next;
                if (flag1 && flag2)
                {
                    break;
                }
            }

            if (ith && jth)
            {
                //search for a edge between thw nodes, otherwise -> 0
                temp = g->start;
                while (temp != NULL)
                {
                    if (ith->src == jth->src)
                    {
                        mat[(i*numOfNodes)+j] = 0;
                        //mat[0] = 0;
                        break;
                    }
                    if (temp->src == ith->src && temp->dest == jth->src)
                    {
                        mat[(i*numOfNodes)+j] = temp->weight;
                        break;
                    }
                    else
                    {
                        mat[(i*numOfNodes)+j] = 0;
                    }
                    temp = temp->next;
                }

            }
        }
    }

    return mat;
}


char* str_slice(char str[], int slice_from, int slice_to)
{
    // if a string is empty, returns nothing
    if (str[0] == '\0')
        return NULL;

    //char* buffer;
    size_t str_len;
    //size_t buffer_len;

    // for negative indexes "slice_from" must be less "slice_to"
    if (slice_to < 0 && slice_from < slice_to) {
        str_len = strlen(str);

        // if "slice_to" goes beyond permissible limits
        if (abs(slice_to) > str_len - 1)
            return NULL;

        // if "slice_from" goes beyond permissible limits
        if (abs(slice_from) > str_len)
            slice_from = (-1) * str_len;

        //buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);

        // for positive indexes "slice_from" must be more "slice_to"
    }
    else if (slice_from >= 0 && slice_to > slice_from) {
        str_len = strlen(str);

        // if "slice_from" goes beyond permissible limits
        if (slice_from > str_len - 1)
            return NULL;

        //buffer_len = slice_to - slice_from;
        str += slice_from;

        // otherwise, returns NULL
    }
    else
        return NULL;

    //buffer = calloc(buffer_len, sizeof(char));
    //strncpy(buffer, str, buffer_len);
    //free(str);
    return str;
}

char* readinput(int* len)
{
    int flag = 1;
    char* input = NULL;
    char tempbuf[200];
    size_t templen = 0;
    do {
        fgets(tempbuf, 200, stdin);
        templen = strlen(tempbuf);
        input = (char*)malloc((templen+1)*sizeof(char));
        //input = (char*)malloc(input, templen + 1);
        strcpy(input, tempbuf);
        //strncat(input, tempbuf, templen);
        //inputlen += templen;
        //tempbuf[200 - 2] = '\n';
        flag = 0;
    } while (flag);
    //printf("%d,%d", *len, templen);
    *len = (int)templen;
    return input;
}


void deleteGraph(struct Graph* g)
{
    struct Node* temp1 = g->head;
    struct Node* delete1;
    struct Edge* temp2 = g->start;
    struct Edge* delete2;

    while (temp1->next != NULL)
    {
        delete1 = temp1;
        temp1 = temp1->next;
        free(delete1);
    }
    free(temp1);

    while (temp2->next != NULL)
    {
        delete2 = temp2;
        temp2 = temp2->next;
        free(delete2);
    }
    free(temp2);

    g->head = NULL;
    g->start = NULL;
}

struct Graph* createGraph(char** input, int strlen)
{ 
    *input = str_slice(*(input), 2, strlen + 1);
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    if (!graph)
    {
        return NULL;
    }

    graph->head = NULL;
    graph->start = NULL;
    int numOfNodes = atoi(input[0]);
    int curNode = 0;
    int newNodes = 0;
    int i = 0;

    for  (i = 2; i < strlen; i+=2)
    {
        if (*(input[0]+i) == 'n')
        {
            i += 2;
            curNode = atoi(input[0] + i);
            if (graph->head == NULL)
            {
                createHead(graph, curNode);
                newNodes++;
            }
            else
            {
                if (!isNodeExist(graph->head, curNode))
                {
                    createNode(graph->head, curNode);
                    newNodes++;
                }
            }
        }
        else
        {
            if (!isNodeExist(graph->head, atoi(input[0] + i)))
            {
                createNode(graph->head, atoi(input[0] + i));
                newNodes++;
            }
            if (graph->start == NULL)
            {
                createStart(graph, curNode, atoi(input[0] + i), atoi(input[0] + i+2));
            }
            else
            {
                createEdge(graph, curNode, atoi(input[0] + i), atoi(input[0] + i + 2));
            }
            //if node dosent exist create it
            i = i + 2;
        }

        if (*(input[0]+i + 2) == 'B' || *(input[0] + i + 2) == 'A' || *(input[0] + i + 2) == 'D' || *(input[0] + i + 2) == 'S' || *(input[0] + i + 2) == 'T')
        {
            break;
        }
    }

    //test
    if (newNodes == numOfNodes)
    {
        //printf("A - OK nodes");
    }
   *input = str_slice(*(input), i+2, strlen + 1);
    return graph;
}

char* getD(char input[], struct Graph* g)
{
    int toD = atoi(&(input[2]));
    struct Edge* temp = NULL;
    struct Edge* toDelete = NULL;

    removeNode(g->head, toD);
    removeEdge(g->start, toD);

    temp = g->start;

    if (!temp)
    {
        return NULL;
    }


    while (temp != NULL && temp->next != NULL)
    {
        if (temp->dest == toD)
        {
            toDelete = g->start;
            g->start = g->start->next;
            free(toDelete);
            temp = g->start;
        }
        else if (temp->next->dest == toD)
        {
            toDelete = temp->next;
            temp->next = temp->next->next;

            free(toDelete); //free Memory of node to delete
        }
        else
        {
            temp = temp->next;
        }
    }

    input = str_slice(input,4, strlen(input) + 1);

    return input;
}

char* getB(char input[], struct Graph* g)
{

    int curNode = atoi(&(input[2]));
    //int newNodes = 0;
    int i = 0;

    if (isNodeExist(g->head, atoi(&(input[2]))))
    {
        removeEdge(g->start, curNode);
        //create edge down 
    }
    else
    {
        createNode(g->head, atoi(&(input[2])));
    }

    for (i = 4; i < strlen(input); i += 2)
    {
        
        if (g->start == NULL)
        {
            createStart(g, curNode, atoi(&(input[i])), atoi(&(input[i + 2])));
            i = i + 2;
        }
        else
        {
            createEdge(g, curNode, atoi(&(input[i])), atoi(&(input[i + 2])));
            i = i + 2;
        }

        if (input[i + 2] == 'B' || input[i + 2] == 'A' || input[i + 2] == 'D' || input[i + 2] == 'S' || input[i + 2] == 'T')
        {
            break;
        }
    }

    input = str_slice(input, i+2, strlen(input) + 1);
    return input;
}

char* getS(char s[], struct Graph* g, int numOfNodes)
{
   int src = atoi(&(s[2]));
   int dst = atoi(&(s[4]));
   int newS = 0;
   int newD = 0;
   int flag = 0;

   struct Node* h = g->head;
   while (h != NULL)
   {
       if (h->src == src)
       {
           newS = flag;
       }
       if (h->src == dst)
       {
           newD = flag;
       }
       h = h->next;
       flag++;
   }

   new_shortest_path_dijkstra(newS, newD, numOfNodes, InitializeMatrix(g, numOfNodes));

   s= str_slice(s, 6, strlen(s) + 1);

    return s;
}

char* getT(char input[], struct Graph* g, int numOfNodes)
{
    int num_nodes = atoi(&(input[2]));
    int count=4;
    int *nods = (int*)malloc(num_nodes * sizeof(int));
    int* toSend = (int*)malloc(num_nodes * sizeof(int));
    int* mat;
    int flag = 0;
    struct Node* h = g->head;
    
    if (!nods)
    {
        return NULL;
    }

    while ((count-4)/2 < num_nodes)
    {
        h = g->head;
        flag = 0;
        nods[(count - 4) / 2] = atoi(&(input[count]));
        
        while (h != NULL)
        {
            if (nods[(count - 4) / 2] == h->src)
            {
                toSend[(count - 4) / 2] = flag;
            }
            flag++;
            h = h->next;
        }
        //toSend[(count - 4) / 2] = flag;
        count += 2;
        

    }
    //initilize 
    mat = InitializeMatrix(g, numOfNodes);
    /*
    for (int i = 0; i < numOfNodes; i++)
    {
        for (int j = 0; j < numOfNodes; j++)
        {
            printf("%d\t", mat[i*numOfNodes+j]);
        }
        printf("\n");
    }
    */

    T_shortest_path(mat, numOfNodes, toSend, num_nodes);
    printf("\n");
    
    input = str_slice(input, 4+2*num_nodes, strlen(input) + 1);
    free(nods);
    free(mat);
    return input;
}

void OptionManager(char choise, char* input, int lenStr)
{
    struct Graph* graph = NULL;
    int flag = 1;
    int numOfNodes = 0;
    while (flag)
    {
        switch (choise)
        {
        case 'A':
            if (graph != NULL)
            {
                deleteGraph(graph);
            } 
            numOfNodes = atoi(&(input[2]));
            graph = createGraph(&input, lenStr);
            break;
        case 'B':
            if (!isNodeExist(graph->head, atoi(&(input[2]))))
            {
                numOfNodes++;
            }
            input = getB(input, graph);
            break;
        case 'D':
            input = getD(input, graph);
            numOfNodes--;
            break;
        case 'S':
            input = getS(input, graph, numOfNodes);
            break;
        case 'T':
            input = getT(input, graph, numOfNodes);
            break;
        default:
            flag = 0;
            break;
        }
        
        if (input != NULL)
        {
            choise = input[0];
        }
        else
        {
            flag = 0;
        }
        
    }

    free(graph);

}

void new_shortest_path_dijkstra(int src, int dest, int num_vertices, int* edges) {
    // Create a dist array to store the shortest distance from src to each vertex
    int* dist = (int*)malloc(num_vertices * sizeof(int));
    // Create a visited array to mark which vertices have been visited
    int* visited = (int *)malloc(num_vertices * sizeof(int));
    // Initialize all distances as infinite and all vertices as unvisited
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    // The distance from src to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int i = 0; i < num_vertices - 1; i++) {
        // Pick the minimum distance vertex from the unvisited set
        int u = -1, min = INF;
        for (int j = 0; j < num_vertices; j++) {
            if (!visited[j] && dist[j] <= min) {
                min = dist[j];
                u = j;
            }
        }
        // Mark the picked vertex as visited
        visited[u] = 1;

        // Update the distance of the adjacent vertices of the picked vertex
        for (int v = 0; v < num_vertices; v++) {
            if (!visited[v] && edges[u * num_vertices + v] && dist[u] != INF && dist[u] + edges[u * num_vertices + v] < dist[v]) {
                dist[v] = dist[u] + edges[u * num_vertices + v];
            }
        }
    }

    // Print the shortest distance from src to dest
    if (dist[dest] < INF)
    {
        printf("Dijsktra shortest path: %d\n", dist[dest]);
    }
    else
    {
        printf("Dijsktra shortest path: %d\n", -1);
    }

    free(dist);
    free(visited);

    printf("\n");
}

void T_shortest_path(int* adj_matrix, int num_vertices, int* nods, int num_nodes) {
    // Create an array to store the shortest path between each pair of important nodes
    int* shortest_path = (int*)malloc(num_nodes * num_nodes * sizeof(int));
    int* shortest_path_length = (int*)malloc(num_nodes * num_nodes * sizeof(int));
    int dest = 0;
    //int end = 0;
    //int temp = 0;
    // Initialize the array with INF
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            shortest_path[i * num_nodes + j] = INF;
        }
    }

    // Calculate the shortest path between each pair of important nodes
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i != j) {
                dest = forT_dijkstra(nods[i], nods[j], num_vertices, adj_matrix);
                //shortest_path[i * num_nodes + j] = dist[nods[j]];
                //shortest_path_length[i * num_nodes + j] = dist[nods[j]];
                shortest_path[i * num_nodes + j] = dest;
                shortest_path_length[i * num_nodes + j] = dest;
            }
            else
            {
                //shortest_path[i * num_nodes + j] = 0;
                //shortest_path_length[i * num_nodes + j] = 0;
            }
        }
    }
    // Extract all possible permutations for the must-visit nodes
    int* permutation = (int*)malloc(num_nodes * sizeof(int));
    for (int i = 0; i < num_nodes; i++) {
        permutation[i] = i; //##need to check
    }

    /*
   for (int x = 0; x< num_nodes; x++)
    {
        for (int y= 0; y< num_nodes; y++)
        {
            printf("%d\t", shortest_path[x*num_nodes+y]);
        }
        printf("\n");
    }
    */
    permute(permutation, 0, num_nodes-1, num_nodes, adj_matrix, shortest_path, shortest_path_length); //changed num_vertics to num_nods

    if (theShortestPathElement < INF)
    {
        printf("TSP shortest path: %d", theShortestPathElement);
    }
    else
    {
        printf("TSP shortest path: %d", -1);
    }

    free(permutation);
    free(shortest_path);
    free(shortest_path_length);
    theShortestPathElement = INF;
}

// Function to calculate the cost of a given permutation of the important nodes
int calculate_path_cost(int* permutation, int num_nodes, int* num_vertices, int* edges, int* shortest_path) {
    int cost = 0;
    for (int i = 0; i < num_nodes - 1; i++) {
        cost += shortest_path[permutation[i] * num_nodes + permutation[i + 1]];
    }
    return cost;
}


int forT_dijkstra(int src, int dest, int num_vertices, int* edges) {
    int shortest = -1;
    // Create a dist array to store the shortest distance from src to each vertex
    int* dist = (int*)malloc(num_vertices * sizeof(int));
    // Create a visited array to mark which vertices have been visited
    int* visited = (int*)malloc(num_vertices * sizeof(int));
    // Initialize all distances as infinite and all vertices as unvisited
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    // The distance from src to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int i = 0; i < num_vertices - 1; i++) {
        // Pick the minimum distance vertex from the unvisited set
        int u = -1, min = INF;
        for (int j = 0; j < num_vertices; j++) {
            if (!visited[j] && dist[j] <= min) {
                min = dist[j];
                u = j;
            }
        }
        // Mark the picked vertex as visited
        visited[u] = 1;

        // Update the distance of the adjacent vertices of the picked vertex
        for (int v = 0; v < num_vertices; v++) {
            if (!visited[v] && edges[u * num_vertices + v] && dist[u] != INF && dist[u] + edges[u * num_vertices + v] < dist[v]) {
                dist[v] = dist[u] + edges[u * num_vertices + v];
            }
        }
    }

    // Print the shortest distance from src to dest
    //printf("Dijsktra shortest path: %d\n", dist[dest]);
    
    shortest = dist[dest];

    free(dist);
    free(visited);

    //printf("\n");

    return shortest;
}

void permute(int* arr, int l, int r, int num_vertices, int* edges, int* shortest_path, int* shortest_path_length) {
    
    if (l == r) {
        // Calculate the cost of the current permutation
        int cost = calculate_path_cost(arr, num_vertices, edges, shortest_path, shortest_path_length);
        /*
        printf("Permutation: ");
        for (int i = 0; i <= r; i++) {
            printf("%d ", arr[i]);
        }
        printf("Cost: %d\n", cost);
        */
        if (cost < theShortestPathElement)
        {
            theShortestPathElement = cost;
        }
    }
    else {
        for (int i = l; i <= r; i++) {
            // Swap current element with first element
            int temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
            // Recursive call for next permutation
            permute(arr, l + 1, r, num_vertices, edges, shortest_path, shortest_path_length);
            // Swap back the current element with first element
            temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
        }
    }
}
