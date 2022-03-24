#include "RBTree.h"

int main(void)
{
    Node* tree = NIL;
    Node* checkNode;
    char command;
    int key;
    while (fscanf(stdin, "%c %d", &command, &key) > 0)
    {
        if (command == 'a')
        {
            InsertNode(key, &tree);
        }
        if (command == 'r')
        {
            DeleteNode(key, &tree);
        }
        if (command == 'f') {
            checkNode = FindNode(key, tree);
            if (checkNode)
            {
                if (checkNode->data == key)
                {
                    printf("yes\n");
                }
                else
                {
                    printf("no\n");
                }
            }
            else
            {
                printf("no\n");
            }
        }
    }
    free(tree);
    return 0;
}