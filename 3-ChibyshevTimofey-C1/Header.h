#ifndef __HEADER_H_
#define __HEADER_H_

#ifdef __cplusplus
extern "C" {
#endif
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>

    typedef struct
    {
        int* neighbours;
        int neighboursCount;
    } LineOfList;

    typedef struct
    {
        LineOfList* verticesOfLine;
        int verticesCount;
    } AdjList;

    typedef struct node_t
    {
        int vertex;
        struct node_t* next;
    } node_t;

    typedef struct
    {
        node_t* top;
    } Stack;

    int IntLength(int num);
    AdjList* AdjListReadFromStream(FILE* stream);
    AdjList* AdjListCreate(int verticesCount);
    void AdjListDestroy(AdjList* graph);
    bool DFS(FILE* stream, AdjList* graph, int vertex);
    int AllOperations();
    bool AddingVertexToGraph(AdjList* graph, int position, int neighbour);

    Stack* StackInit();
    Stack* StackPush(Stack* stack, int vertex);
    int StackPop(Stack* stack);
    bool StackIsEmpty(Stack* stack);
    void StackDestroy(Stack* stack);
    bool StackPushAllVertexNeighbours(Stack* stack, AdjList* graph, int vertex);

#ifdef __cplusplus
}
#endif

#endif