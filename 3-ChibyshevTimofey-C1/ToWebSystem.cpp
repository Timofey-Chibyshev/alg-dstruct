#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    int* neighbours;
    int neighboursCount;
} LineOfList_t;

typedef struct
{
    LineOfList_t* verticesOfLine;
    int verticesCount;
} AdjList_t;

typedef struct Node_t
{
    int vertex;
    struct Node_t* next;
} Node_t;

typedef struct
{
    Node_t* top;
} Stack_t;

AdjList_t* AdjListReadFromStream(FILE* stream);
AdjList_t* AdjListCreate(int verticesCount);
void AdjListDestroy(AdjList_t* graph);
bool DFS(FILE* stream, AdjList_t* graph, int vertex);
int AllOperations();
bool AddingVertexToGraph(AdjList_t* graph, int position, int neighbour);

Stack_t* StackInit();
Stack_t* StackPush(Stack_t* stack, int vertex);
int StackPop(Stack_t* stack);
bool StackIsEmpty(Stack_t* stack);
void StackDestroy(Stack_t* stack);
bool StackPushAllVertexNeighbours(Stack_t* stack, AdjList_t* graph, int vertex);

int main()
{
    return (AllOperations());
}

AdjList_t* AdjListReadFromStream(FILE* stream)
{
    int verticesCount = 0, numOfVertex = 0, currentVertex = 0, currentNeighbour = 0;
    char ch;
    if (fscanf(stream, "%d", &verticesCount) != 1)
    {
        perror("ERROR!");
        return NULL;
    }
    AdjList_t* graph = AdjListCreate(verticesCount);
    if (!graph)
    {
        return NULL;
    }
    if (fscanf(stream, "%c", &ch) != 1)
    {
        perror("ERROR!");
        AdjListDestroy(graph);
        return NULL;
    }
    for (numOfVertex = 0; numOfVertex < verticesCount; numOfVertex++)
    {
        if (fscanf(stream, "%d", &currentVertex) != 1)
        {
            perror("ERROR!");
            AdjListDestroy(graph);
            return NULL;
        }
        if (fscanf(stream, "%c", &ch) != 1)
        {
            perror("ERROR!");
            AdjListDestroy(graph);
            return NULL;
        }
        while (ch == ' ')
        {
            if (fscanf(stream, "%d", &currentNeighbour) != 1)
            {
                perror("ERROR!");
                AdjListDestroy(graph);
                return NULL;
            }
            if (fscanf(stream, "%c", &ch) != 1)
            {
                perror("ERROR!");
                AdjListDestroy(graph);
                return NULL;
            }
            if (AddingVertexToGraph(graph, currentVertex, currentNeighbour) == false)
            {
                perror("ERROR!");
                AdjListDestroy(graph);
                return NULL;
            }
            if (AddingVertexToGraph(graph, currentNeighbour, currentVertex) == false)
            {
                perror("ERROR!");
                AdjListDestroy(graph);
                return NULL;
            }
        }
    }
    return graph;
}

AdjList_t* AdjListCreate(int verticesCount)
{
    int numOfVertex = 0;
    AdjList_t* graph = NULL;
    graph = (AdjList_t*)malloc(sizeof(AdjList_t));
    if (!graph)
    {
        return NULL;
    }
    graph->verticesCount = verticesCount;
    graph->verticesOfLine = (LineOfList_t*)malloc(verticesCount * sizeof(LineOfList_t));
    if (!graph->verticesOfLine)
    {
        free(graph);
        return NULL;
    }
    for (numOfVertex = 0; numOfVertex < verticesCount; numOfVertex++)
    {
        graph->verticesOfLine[numOfVertex].neighbours = NULL;
        graph->verticesOfLine[numOfVertex].neighboursCount = 0;
    }
    return graph;
}

void AdjListDestroy(AdjList_t* graph)
{
    int numOfVertex = 0;
    for (numOfVertex = 0; numOfVertex < graph->verticesCount; numOfVertex++)
    {
        if (graph->verticesOfLine[numOfVertex].neighbours)
        {
            free(graph->verticesOfLine[numOfVertex].neighbours);
        }
    }
    free(graph->verticesOfLine);
    free(graph);
}

bool AddingVertexToGraph(AdjList_t* graph, int position, int neighbour)
{
    int counter;
    graph->verticesOfLine[position].neighboursCount++;
    int* tmp = NULL;
    tmp = (int*)realloc(graph->verticesOfLine[position].neighbours, graph->verticesOfLine[position].neighboursCount * sizeof(int));
    if (!tmp)
    {
        return false;
    }
    graph->verticesOfLine[position].neighbours = tmp;
    counter = graph->verticesOfLine[position].neighboursCount - 1;
    graph->verticesOfLine[position].neighbours[counter] = neighbour;
    return true;
}

bool DFS(FILE* stream, AdjList_t* graph, int vertex)
{
    int* visited = NULL;
    int currentVertex = 0;
    int numOfVertex = 0;
    Stack_t* stack = StackInit();
    if (!stack)
    {
        return false;
    }
    visited = (int*)malloc(graph->verticesCount * sizeof(int));
    if (!visited)
    {
        StackDestroy(stack);
        return false;
    }
    for (numOfVertex = 0; numOfVertex < graph->verticesCount; numOfVertex++)
    {
        visited[numOfVertex] = 0;
    }
    visited[vertex] = 1;
    fprintf(stream, "%d ", vertex);
    if (!StackPushAllVertexNeighbours(stack, graph, vertex))
    {
        free(visited);
        StackDestroy(stack);
        return false;
    }
    while (!StackIsEmpty(stack))
    {
        currentVertex = StackPop(stack);
        if (!visited[currentVertex])
        {
            visited[currentVertex] = 1;
            fprintf(stream, "%d ", currentVertex);
            if (!StackPushAllVertexNeighbours(stack, graph, currentVertex))
            {
                free(visited);
                StackDestroy(stack);
                return false;
            }
        }
    }
    free(visited);
    StackDestroy(stack);
    return true;
}

int AllOperations()
{
    AdjList_t* graph = AdjListReadFromStream(stdin);
    if (!graph)
    {
        return -1;
    }
    if (!DFS(stdout, graph, 0))
    {
        AdjListDestroy(graph);
        return -1;
    }
    AdjListDestroy(graph);
    return 0;
}

Stack_t* StackInit()
{
    Stack_t* stack = (Stack_t*)malloc(sizeof(Stack_t));
    if (!stack)
    {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

Stack_t* StackPush(Stack_t* stack, int vertex)
{
    Node_t* tmp = (Node_t*)malloc(sizeof(Node_t));
    if (!tmp)
    {
        return NULL;
    }
    tmp->vertex = vertex;
    tmp->next = stack->top;
    stack->top = tmp;
    return stack;
}

int StackPop(Stack_t* stack)
{
    Node_t* tmp = stack->top;
    int vertex;
    if (!StackIsEmpty(stack))
    {
        tmp = stack->top;
        vertex = tmp->vertex;
        stack->top = stack->top->next;
        free(tmp);
        return vertex;
    }
    return -1;
}

bool StackIsEmpty(Stack_t* stack)
{
    return (!stack->top);
}

void StackDestroy(Stack_t* stack)
{
    Node_t* iter = stack->top;
    Node_t* tmp = iter;
    while (iter)
    {
        tmp = iter;
        iter = iter->next;
        free(iter);
    }
    free(stack);
}

bool StackPushAllVertexNeighbours(Stack_t* stack, AdjList_t* graph, int vertex)
{
    int i = graph->verticesOfLine[vertex].neighboursCount - 1;
    int neighbour = graph->verticesOfLine[vertex].neighbours[i];
    for (i; i >= 0; i--)
    {
        neighbour = graph->verticesOfLine[vertex].neighbours[i];
        if (!StackPush(stack, neighbour))
        {
            return false;
        }
    }
    return true;
}