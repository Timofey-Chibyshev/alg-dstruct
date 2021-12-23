#ifndef HEADER_H
#define HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(disable:4996)

#define _CRT_SECURE_NO_WARNINGS

typedef struct tree 
{
    int height;
    struct tree* left;
    struct tree* right;
 } tree;

void FillTree(tree* binTree);
void PrintTree(FILE* stream, tree* binTree, int spaces);

#ifdef __cplusplus
}
#endif

#endif
