#include "RBTree.h"
#include <crtdbg.h>

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define BUF_SIZE 16

void MemoryLeaks(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}

int StartProcess()
{
    Node* tree = NIL;
    Node* checkNode;
    char command, space;
    char buf[BUF_SIZE] = { 0 };
    int key;
    while(fgets(buf, BUF_SIZE, stdin))
    {
        if (sscanf(buf, "%c%c%d", &command, &space, &key) <= 0)
        {
            TreeDestroy(tree);
            return 1;
        }
        if (!(((command == 'a') || (command == 'r') || (command == 'f')) && (space == ' ')))
        {
            TreeDestroy(tree);
            return 1;
        }
        if (command == 'a')
        {
            InsertNode(key, &tree);
        }
        if (command == 'r')
        {
            DeleteNode(key, &tree);
        }
        if (command == 'f') 
        {
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
    TreeDestroy(tree);
    return 0;
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