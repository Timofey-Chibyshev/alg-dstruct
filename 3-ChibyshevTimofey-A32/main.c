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
    const char *name1 = "Mass.txt";
    const char *name2 = "Mass1.txt";
    const char *summary = "Sum.txt";
    setlocale(LC_CTYPE, "Russian");
    int size1, size2;
    size1 = 0;
    size2 = 0;
    list_t* first = Create();
    list_t* second = Create();
    list_t* sum = Create();
    if (ReadNumbers(name1, first, &size1))
    {
        printf("\nThe numbers are read...\n");
    }
    else
    {
        printf("\nERROR!!!\n");
        return -1;
    }
    printf("\nFirst list: \n");
    ListPrint(first, size1);
    if (ReadNumbers(name2, second, &size2))
    {
        printf("\nThe numbers are read...\n");
    }
    else
    {
        printf("\nERROR!!!\n");
        return -1;
    }
    printf("\nSecond list: \n");
    ListPrint(second, size2);
    Merge(first, second, sum, size1, size2);
    printf("\nSum list: \n");
    ListPrint(sum, (size1 + size2));
    Write(sum, summary, (size1 + size2));
    Destroy(sum);
    if ((size1 == 0) || (size2 == 0))
    {
        free(first);
        free(second);
    }
    else
    {
        if (first->data < second->data)
        {
            free(second);
        }
        else
        {
            free(first);
        }
    }
    MemoryLeaks();
    return 0;
}

