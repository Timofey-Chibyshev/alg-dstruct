#include "pch.h"
#include <time.h>
#include "Header.h"

/*
IDE: Microsoft Visual Studio 2019
OS: Windows 10 Home rus 20H2 Build 19042.1348
PC configuration:
    CPU:            Intel(R) Core(TM) i3-7020U CPU @ 2.30GHz
    Motherboard:    LENOVO
    RAM:            8GB
    HDD:            1TB
*/

/*
AllOperations_StressTest results (run on Release VS configuration):
    Time:   19.031 sec to generate graph
            53.957 sec to output answer
    RAM:    about 824MB
*/

const char* filenameGraph = "Graph.txt";
const char* filenameResult = "Result.txt";
const int verticesCount = (int)600000;

TEST(AllOperations_StressTest, AllOperationsGraphCreating) 
{
    srand(time(NULL));
    int max = verticesCount;
    int numOfVertex, neighbour, tmp, tmp1;
    FILE* fp = fopen(filenameGraph, "w");
    if (!fp) 
    {
        printf("ERROR");
        ASSERT_TRUE(fp);
    }
    fprintf(fp, "%d\n", verticesCount);
    for (numOfVertex = 0; numOfVertex < verticesCount - 1; numOfVertex++) 
    {
        fprintf(fp, "%d", numOfVertex);
        tmp = (numOfVertex + 1) + rand() % (max - 1);
        tmp1 = rand() % (max - 1) + 1;
        for (neighbour = tmp; neighbour < verticesCount; neighbour += tmp1)
        {
            fprintf(fp, " %d", neighbour);
            tmp = (numOfVertex + 1) + rand() % (max - 1);
            tmp1 = rand() % (max - 1) + 1;
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "%d\n", verticesCount - 1);
    fclose(fp);
}

TEST(AllOperations_StressTest, AllOperationsDFSResult)
{
    int dfsResult = 0;
    FILE* fp = fopen(filenameGraph, "r");
    if (!fp) 
    {
        printf("ERROR");
        ASSERT_TRUE(fp);
    }
    AdjList_t* graph = AdjListReadFromStream(fp);
    fclose(fp);
    if (!graph) 
    {
        printf("Failed to read graph!\n");
        ASSERT_TRUE(graph);
    }
    FILE* fp1 = fopen(filenameResult, "w");
    if (!fp1) 
    {
        AdjListDestroy(graph);
        printf("ERROR");
        ASSERT_TRUE(fp1);
    }
    dfsResult = DFS(fp1, graph, 0);
    if (!dfsResult) 
    {
        fclose(fp1);
        AdjListDestroy(graph);
        printf("ERROR DFS!");
        ASSERT_TRUE(dfsResult);
    }
    fclose(fp1);
    AdjListDestroy(graph);
}