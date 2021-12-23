#pragma warning(disable:4996)

#include <stdio.h>
#include "header.h"

int main()
{
    /*binary tree
                     9
                  6

               2
                     8
                  5
                     7

            0

                  4

               1 

                  3

    */
    //CreationABinaryTreeOnStack
    const char* filename = "Output.txt";
    FILE* fp = fopen(filename, "w");
    if (!fp)
    {
        return NULL;
    }
    tree t[10] = { 0 };
    t[0].left = &t[1];
    t[0].right = &t[2];
    t[1].left = &t[3];
    t[1].right = &t[4];
    t[2].left = &t[5];
    t[2].right = &t[6];
    t[5].left = &t[7];
    t[5].right = &t[8];
    t[6].right = &t[9];
    FillTree(t);
    printf("Tree:\n");
    PrintTree(fp, t, 0);
    fclose(fp);
	return 0;
}
