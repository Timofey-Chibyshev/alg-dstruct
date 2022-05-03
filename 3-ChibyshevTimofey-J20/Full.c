#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <crtdbg.h>

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define BUF_SIZE 16
#define INPUT_STR_SIZE 10000
#define TABLE_SIZE 5


typedef struct Node
{
    char* data;
    struct Node* next;
} Node;

unsigned int Hash(const char* s)
{
    unsigned int h = 0, g;
    while (*s)
    {
        h = (h << 4) + *s++;
        g = h & 0xf0000000L;
        if (g)
        {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h % TABLE_SIZE;
}

int LookUp(Node** table, const char* key)
{
    unsigned index = Hash(key);
    const Node* cur = table[index];
    while (cur && strcmp(cur->data, key))
    {
        cur = cur->next;
    }
    if (cur)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Insert(Node** table, char* key)
{
    if (!LookUp(table, key))
    {
        unsigned index = Hash(key);
        Node* newNode = (Node*)malloc(sizeof * newNode);
        if (!newNode)
        {
            return 0;
        }
        newNode->data = malloc((strlen(key) + 1) * sizeof(char));
        if (!newNode->data)
        {
            return 0;
        }
        strcpy(newNode->data, key);
        newNode->next = table[index];
        table[index] = newNode;
        return 1;
    }
    return 0;
}

int Delete(Node** table, char* key)
{
    if (LookUp(table, key))
    {
        unsigned int index = Hash(key);
        Node* cur = table[index];
        Node* prev = NULL;
        while (strcmp(cur->data, key))
        {
            prev = cur;
            cur = cur->next;
        }
        if (prev)
        {
            prev->next = cur->next;
        }
        else
        {
            table[index] = cur->next;
        }
    }
    return 0;
}

void DeleteChain(Node** head)
{
    Node* prev = NULL;
    while (*head)
    {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev->data);
        free(prev);
    }
}

void DeleteTable(Node** table)
{
    if (!table)
    {
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if ((table[i]))
        {
            DeleteChain(&table[i]);
        }
    }
    free(*table);
    table = NULL;
    free(table);
    return;
}

int StartProcess()
{
    char command;
    Node* table[TABLE_SIZE] = { NULL };
    char buf[BUF_SIZE] = { 0 };
    char value[INPUT_STR_SIZE] = { 0 };
    while (fgets(buf, BUF_SIZE, stdin))
    {
        sscanf(buf, "%c %s", &command, &value);
        switch (command)
        {
        case 'a':
            Insert(table, value);
            break;
        case 'r':
            Delete(table, value);
            break;
        case 'f':
            if (LookUp(table, value))
            {
                printf("%s", "yes\n");
            }
            else
            {
                printf("%s", "no\n");
            }
            break;
        default:
            DeleteTable(table);
            return 1;
        }
    }
    DeleteTable(table);
    return 0;
}

void MemoryLeaks(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}

int main(void)
{
    if (StartProcess())
    {
        MemoryLeaks();
        return -1;
    }
    MemoryLeaks();
    return 0;
}