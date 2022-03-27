#ifndef RBTree_H
#define RBTree_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR_ALLOC NULL
#define NIL &forLeaves 

    typedef enum
    {
        BLACK, RED
    } NodeColor;

    typedef struct Node
    {
        struct Node* left;
        struct Node* right;
        struct Node* parent;
        NodeColor color;
        int data;
    } Node;

    Node forLeaves;

    void RotateLeft(Node* x, Node** root);

    void RotateRight(Node* x, Node** root);

    Node* InsertNode(int data, Node** root);

    void InsertFixup(Node* x, Node** root);

    Node* FindNode(int data, Node* root);

    void DeleteNode(int data, Node** root);

    void DeleteFixup(Node* x, Node** root);

    void TreeDestroy(Node* x);

#ifdef __cplusplus
}
#endif

#endif
