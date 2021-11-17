#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Header.h"

AdjList* AdjListReadFromStream(FILE* stream)
{
    int verticesCount = 0, numOfVertex = 0, currentVertex = 0, currentNeighbour = 0;
    char ch;
    if (fscanf(stream, "%d", &verticesCount) != 1)
    {
        perror("ERROR!");
        return NULL;
    }
    AdjList* graph = AdjListCreate(verticesCount);
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

AdjList* AdjListCreate(int verticesCount)
{
    int numOfVertex = 0;
    AdjList* graph = NULL;
    graph = (AdjList*)malloc(sizeof(AdjList));
    if (!graph)
    {
        return NULL;
    }
    graph->verticesCount = verticesCount;
    graph->verticesOfLine = (LineOfList*)malloc(verticesCount * sizeof(LineOfList));
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

void AdjListDestroy(AdjList* graph)
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

bool AddingVertexToGraph(AdjList* graph, int position, int neighbour)
{
    int counter;
    graph->verticesOfLine[position].neighboursCount++;
    int* tmp = NULL;
    tmp = (int*)realloc(graph->verticesOfLine[position].neighbours, graph->verticesOfLine[position].neighboursCount * sizeof(int));
    if (!tmp)
    {
        AdjListDestroy(graph);
        return false;
    }
    graph->verticesOfLine[position].neighbours = tmp;
    counter = graph->verticesOfLine[position].neighboursCount - 1;
    graph->verticesOfLine[position].neighbours[counter] = neighbour;
    return true;
}

bool DFS(FILE* stream, AdjList* graph, int vertex) 
{
    int* visited = NULL;
    int currentVertex = 0;
    int numOfVertex = 0;
    Stack* stack = StackInit();
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
    AdjList* graph = AdjListReadFromStream(stdin);
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

Stack* StackInit()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack)
    {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

Stack* StackPush(Stack* stack, int vertex)
{
    node_t* tmp = (node_t*)malloc(sizeof(node_t));
    if (!tmp)
    {
        return NULL;
    }
    tmp->vertex = vertex;
    tmp->next = stack->top;
    stack->top = tmp;
    return stack;
}

int StackPop(Stack* stack)
{
    node_t* tmp = stack->top;
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

bool StackIsEmpty(Stack* stack)
{
    return (!stack->top);
}

void StackDestroy(Stack* stack)
{
    node_t* iter = stack->top;
    node_t* tmp = iter;
    while (iter)
    {
        tmp = iter;
        iter = iter->next;
        free(iter);
    }
    free(stack);
}

bool StackPushAllVertexNeighbours(Stack* stack, AdjList* graph, int vertex)
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