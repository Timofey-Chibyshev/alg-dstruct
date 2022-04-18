#ifndef TreePlus_H
#define TreePlus_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(disable:4996)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* p;
    int size;
    int keys[3];
    struct Node* sons[4];
} Node;

Node* root = NULL;

typedef struct listNode {
    struct listNode* next;
    struct listNode* prev;
    Node* val;
} listNode;

typedef struct SplitRetval {
    Node* left;
    Node* right;
} SplitRetval;

listNode* ListAdd(listNode* l, Node* v);
Node* NodeCreate();
Node* Search(Node* v, int x);
void Print(Node* t, int n);
int Cmpfu(const void* a, const void* b);
void SortSons(Node* v);
int SubTreeMax(Node* v);
void UpdateKeys(Node* v);
void SplitParent(Node* t);
Node* Add(Node* t, int x);
void DeleteInNode(Node* v);
Node* FindBrother(Node* v);
Node* Del(Node* v, int x);
int GetHeight(Node* v);
Node* Merge(Node* l, Node* r);
SplitRetval Split(Node* t, int key);

#ifdef __cplusplus
}
#endif

#endif