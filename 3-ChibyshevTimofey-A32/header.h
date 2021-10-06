#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

    typedef struct list_t
    {
        int data;
        struct list_t* next;
    }list_t;

    list_t* Create();

    void Destroy(list_t* head);

    int NumberCount(FILE* input);

    void AddElementEnd(int value, list_t* head);

    void ListPrint(list_t* list);

    int ReadNumbers(FILE* input, list_t* head, int size);

    void Merge(list_t* first, list_t* second, list_t* sum);

    list_t* InserationSort(list_t* head);

#ifdef __cplusplus
}
#endif

