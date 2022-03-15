#include "RBTree.h"

Node forLeaves = { NIL, NIL, NULL, BLACK, 0 };

void RotateLeft(Node* x, Node** root)
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL)
    {
        y->left->parent = x;
    }
    if (y != NIL)
    {
        y->parent = x->parent;
    }
    if (x->parent)
    {
        if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }
    else
    {
        *root = y;
    }
    y->left = x;
    if (x != NIL)
    {
        x->parent = y;
    }
}

void RotateRight(Node* x, Node** root)
{
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL)
    {
        y->right->parent = x;
    }
    if (y != NIL)
    {
        y->parent = x->parent;
    }
    if (x->parent)
    {
        if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
    }
    else
    {
        *root = y;
    }
    y->right = x;
    if (x != NIL)
    {
        x->parent = y;
    }
}

Node* InsertNode(int data, Node** root)
{
    Node* current, * parent, * x;
    current = *root;
    parent = NULL;
    if (!current)
    {
        return NULL;
    }
    while (current != NIL)
    {
        if (data == current->data)
        {
            return current;
        }
        parent = current;
        current = (data < current->data) ? current->left : current->right;
    }
    x = (Node*)malloc(sizeof(Node));
    if (!x)
    {
        return ERROR_ALLOC;
    }
    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;
    if (parent)
    {
        if (data < parent->data)
        {
            parent->left = x;
        }
        else
        {
            parent->right = x;
        }
    }
    else
    {
        *root = x;
    }
    InsertFixup(x, root);
    return x;
}

void InsertFixup(Node* x, Node** root)
{
    while ((x != *root) && (x->parent->color == RED))
    {
        if (x->parent == x->parent->parent->left)
        {
            Node* y = x->parent->parent->right;
            if (y->color == RED)
            {

                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->right)
                {

                    x = x->parent;
                    RotateLeft(x, root);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                RotateRight(x->parent->parent, root);
            }
        }
        else
        {

            Node* y = x->parent->parent->left;
            if (y->color == RED)
            {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->left)
                {
                    x = x->parent;
                    RotateRight(x, root);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                RotateLeft(x->parent->parent, root);
            }
        }
    }
    (*root)->color = BLACK;
}

Node* FindNode(int data, Node* root)
{
    Node* current = root;
    while (current != NIL)
    {
        if (data == current->data)
        {
            return current;
        }
        else
        {
            current = (data < current->data) ? current->left : current->right;
        }
    }
    return NULL;
}

void DeleteNode(int data, Node** root)
{
    Node* x, * y, * z;
    z = FindNode(data, (*root));
    if (!z || z == NIL)
    {
        return;
    }
    if ((z->left == NIL) || (z->right == NIL))
    {
        y = z;
    }
    else
    {
        y = z->right;
        while (y->left != NIL)
        {
            y = y->left;
        }
    }
    if (y->left != NIL)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }
    x->parent = y->parent;
    if (y->parent)
    {
        if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
    }
    else
    {
        *root = x;
    }

    if (y != z)
    {
        z->data = y->data;
    }
    if (y->color == BLACK)
    {
        DeleteFixup(x, root);
    }
    free(y);
}

void DeleteFixup(Node* x, Node** root)
{
    while ((x != *root) && (x->color == BLACK))
    {
        if (x == x->parent->left)
        {
            Node* w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RotateLeft(x->parent, root);
                w = x->parent->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RotateRight(w, root);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                RotateLeft(x->parent, root);
                x = *root;
            }
        }
        else
        {
            Node* w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RotateRight(x->parent, root);
                w = x->parent->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    RotateLeft(w, root);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RotateRight(x->parent, root);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

void ReadingData(Node* tree)
{
    char command;
    int key;
    Node* checkNode;
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
}