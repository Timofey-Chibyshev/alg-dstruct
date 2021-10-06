#pragma warning(disable:4996)

#include"header.h"
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


void MemoryLeaks(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}

int main()
{
    FILE* input = fopen("Mass.txt", "r");
    if (input == NULL)
    {
        printf("cant open file\n");
        return 1;
    }
    FILE* input1 = fopen("Mass1.txt", "r");
    if (input1 == NULL)
    {
        printf("cant open file\n");
        return 1;
    }
    int size, size1;
    size = NumberCount(input);
    size1 = NumberCount(input1);
    list_t* first = Create();
    list_t* second = Create();
    list_t* sum = Create();
    if (ReadNumbers(input, first, size))
    {
        printf("\nThe numbers are read...\n");
    }
    else
    {
        printf("\nERROR!!!\n");
        return -1;
    }
    printf("\nFirst list: \n");
    ListPrint(first);
    first = InserationSort(first);
    printf("\nSort first list: \n");
    ListPrint(first);
    if (ReadNumbers(input1, second, size1))
    {
        printf("\nThe numbers are read...\n");
    }
    else
    {
        printf("\nERROR!!!\n");
        return -1;
    }
    printf("\nSecond list: \n");
    ListPrint(second);
    second = InserationSort(second);
    printf("\nSort second list: \n");
    ListPrint(second);
    Merge(first, second, sum);
    printf("\nSum list: \n");
    ListPrint(sum);
    Destroy(sum);
    if (first->data < second->data)
    {
        free(second);
    }
    else
    {
        free(first);
    }
    fclose(input);
    fclose(input1);
    MemoryLeaks();
    return 0;
}

