#pragma once
#ifndef __HEADER_H_
#define __HEADER_H_

#ifdef __cplusplus
extern "C" {
#endif
#pragma warning(disable:4996)

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

#ifdef __cplusplus
}
#endif
#endif