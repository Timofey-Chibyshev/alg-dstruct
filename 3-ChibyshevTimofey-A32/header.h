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
} list_t;

list_t* Create();
void Destroy(list_t* head);
int AddElementEnd(int value, list_t* head);
void ListPrint(list_t* list, int size);
int ReadNumbers(const char* filename, list_t* head, int* len);
int Merge(list_t* first, list_t* second, list_t* sum, int size1, int size2);
int Write(list_t* sum, const char* summary, int size);
int AllOperations(const char* name1, const char* name2, const char* sum);
#ifdef __cplusplus
}
#endif

