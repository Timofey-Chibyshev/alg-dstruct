#include <stdio.h>
#include "header.h"

void FillTree(tree* t)
{
    int min;
    if (t)
    {
        if ((!t->left) && (!t->right))
        {
            t->height = 0;
            return;
        }
        if (!t->left)
        {
            FillTree(t->right);
            t->height = 1 + t->right->height;
            return;
        }
        if (!t->right)
        {
            FillTree(t->left);
            t->height = 1 + t->left->height;
            return;
        }
        FillTree(t->left);
        FillTree(t->right);
        min = t->left->height < t->right->height ? t->left->height : t->right->height;
        t->height = 1 + min;
    }
}

void PrintTree(FILE* stream, tree* t, int vertex)
{
    int i;
    if (t) 
    {
        PrintTree(stream, t->right, vertex + 1);
        for (i = 0; i < vertex; i++)
        {
           fprintf(stream, "  ");
        }
        fprintf(stream, "%d\n", t->height);
        PrintTree(stream, t->left, vertex + 1);
    }
}