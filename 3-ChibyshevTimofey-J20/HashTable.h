#pragma once

#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _CRTDBG_MAP_ALLOC
#define BUF_SIZE 16
#define TABLE_SIZE 5
#define INPUT_STR_SIZE 10000


typedef struct Node
{
    char* data;
    struct Node* next;
} Node;

unsigned int Hash(const char* s);

static int LookUp(Node** table, const char* key);

int Insert(Node** table, char* key);

int Delete(Node** table, char* key);

void DeleteChain(Node** head);

void DeleteTable(Node** table);

int StartProcess();