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


listNode* ListAdd(listNode* l, Node* v) {
    listNode* n = (listNode*)malloc(sizeof(listNode));
    if (!n) {
        return NULL;
    }
    l->next = n;
    n->next = NULL;
    n->prev = l;
    n->val = v;
    return n;
}


typedef struct SplitRetval {
    Node* left;
    Node* right;
} SplitRetval;


Node* NodeCreate() {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) {
        return NULL;
    }
    n->p = NULL;
    n->size = 1;
    n->sons[0] = NULL;
    n->sons[1] = NULL;
    n->sons[2] = NULL;
    n->sons[3] = NULL;
    return n;
}


Node* Search(Node* v, int x) {
    Node* t = v;
    if (t == NULL) {
        return NULL;
    }
    while (t->size != 1) {
        if (t->size == 2) {
            if (x <= t->keys[0]) {
                t = t->sons[0];
            }
            else {
                t = t->sons[1];
            }
        }
        else if (x <= t->keys[0]) {
            t = t->sons[0];
        }
        else if (x <= t->keys[1]) {
            t = t->sons[1];
        }
        else {
            t = t->sons[2];
        }
    }
    return t;
}


void Print(Node* t, int n) {
    if (t == NULL) return;
    int i;
    if (t->size == 2) {
        Print(t->sons[1], n + 2);
        for (i = 0; i < n; i++) putchar(' ');
        printf("%d\n", t->keys[0]);
        Print(t->sons[0], n + 2);
    }
    if (t->size == 3) {
        Print(t->sons[2], n + 5);
        for (i = 0; i < n; i++) putchar(' ');
        printf("%d|%d\n", t->keys[0], t->keys[1]);
        Print(t->sons[1], n + 5);
        Print(t->sons[0], n + 5);
    }
    if (t->size == 1) {
        for (i = 0; i < n; i++) putchar(' ');
        printf("%d\n", t->keys[0]);
        return;
    }
}


int Cmpfu(const void* a, const void* b) {
    Node** val1 = (Node**)a;
    Node** val2 = (Node**)b;
    return (*val1)->keys[0] - (*val2)->keys[0];
}


void SortSons(Node* v) {
    if (v == NULL) {
        return;
    }
    Node* arr[4];
    for (int i = 0; i < v->size; i++) {
        arr[i] = v->sons[i];
    }
    qsort(arr, v->size, sizeof(Node*), Cmpfu);
    for (int i = 0; i < v->size; i++) {
        v->sons[i] = arr[i];
    }
}


int SubTreeMax(Node* v) {
    Node* t = v;
    while (t->size != 1) {
        t = t->sons[t->size - 1];
    }
    return t->keys[0];
}


void UpdateKeys(Node* v) {
    if (v == NULL) {
        return;
    }
    Node* p = v->p;
    while (p != NULL) {
        for (int i = 0; i < p->size - 1; i++) {
            p->keys[i] = SubTreeMax(p->sons[i]);
        }
        p = p->p;
    }
}


void SplitParent(Node* t) {
    if (t == NULL) return;
    if (t->size > 3) {
        Node* b = NodeCreate();
        b->p = t->p;
        b->sons[0] = t->sons[2];
        b->sons[1] = t->sons[3];
        b->keys[0] = t->keys[2];
        b->size = 2;
        t->sons[2]->p = b;
        t->sons[3]->p = b;
        t->size = 2;
        t->sons[2] = NULL;
        t->sons[3] = NULL;

        Node* p = t->p;
        if (p != NULL) {
            p->sons[p->size] = b;
            b->p = p;
            p->size++;
            SortSons(p);
            UpdateKeys(b);
            SplitParent(p);
        }
        else {
            Node* newRoot = NodeCreate();
            newRoot->sons[0] = t;
            newRoot->sons[1] = b;
            newRoot->keys[0] = t->keys[1];
            newRoot->size = 2;
            t->p = newRoot;
            b->p = newRoot;
            root = newRoot;
        }
    }
}


Node* Add(Node* t, int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) {
        return NULL;
    }
    n->size = 1;
    n->keys[0] = x;
    t = root;
    if (t == NULL) {
        root = n;
        return root;
    }
    Node* a = Search(t, x);
    if (a->keys[0] == x) return root;
    if (a->p == NULL) {
        Node* newRoot = NodeCreate();
        newRoot->size = 2;
        newRoot->sons[0] = a;
        newRoot->sons[1] = n;
        a->p = newRoot;
        n->p = newRoot;
        SortSons(newRoot);
        root = newRoot;
    }
    else {
        Node* p = a->p;
        p->sons[p->size] = n;
        n->p = p;
        p->size++;
        SortSons(p);
        UpdateKeys(n);
        SplitParent(p);
    }
    UpdateKeys(n);
    return root;
}


void DeleteInNode(Node* v) {
    Node* p = v->p;
    int pos = 4;
    for (int i = 0; i < p->size; i++) {
        if (v == p->sons[i]) {
            pos = i;
            free(p->sons[i]);
        }
        if (i > pos) {
            p->sons[i - 1] = p->sons[i];
        }
    }
    p->size--;
    UpdateKeys(p->sons[0]);
}


Node* FindBrother(Node* v) {
    Node* p = v->p;
    if (p == NULL) {
        return NULL;
    }
    if (p->size == 1) {
        return NULL;
    }
    int pos;
    for (int i = 0; i < p->size; i++) {
        if (v == p->sons[i]) {
            pos = i;
            break;
        }
    }
    if (pos == 0 || pos == 2) {
        return p->sons[1];
    }
    else {
        return p->sons[0];
    }
}


Node* Del(Node* v, int x) {
    Node* t = Search(v, x);
    if (t == NULL) {
        return NULL;
    }
    if (t->keys[0] != x) return root;
    Node* p = t->p;
    if (p == NULL) {
        free(v);
        root = NULL;
    }
    else {
        if (p->size > 2) {
            DeleteInNode(t);
            return root;
        }
        if (p->size == 2) {
            Node* np = FindBrother(p);
            if (np == NULL) {
                DeleteInNode(t);
                p->sons[0]->p = NULL;
                root = p->sons[0];
            }
            else {
                Node* b = FindBrother(t);
                np->sons[np->size] = b;
                b->p = np;
                np->size++;
                p->size = 1;
                p->keys[0] = x;
                SortSons(np);
                Del(v, x);
                UpdateKeys(b);
                SplitParent(np);
                UpdateKeys(b);
            }
        }
    }
    return root;
}


int GetHeight(Node* v) {
    int h = 0;
    while (v->size != 1) {
        h++;
        v = v->sons[0];
    }
    return h;
}


Node* Merge(Node* l, Node* r) {
    if (l == NULL) return r;
    if (r == NULL) return l;
    int hRight = GetHeight(r);
    int hLeft = GetHeight(l);
    if (hLeft == hRight) {
        Node* newRoot = (Node*)malloc(sizeof(Node));
        if (!newRoot) {
            return NULL;
        }
        newRoot->size = 2;
        newRoot->sons[0] = l;
        l->p = newRoot;
        newRoot->sons[1] = r;
        r->p = newRoot;
        UpdateKeys(r);
        return newRoot;
    }
    Node* v;
    if (hRight > hLeft) {
        v = r;
        while (abs(hRight - GetHeight(v)) > 1) {
            v = v->sons[0];
        }
        r->sons[r->size] = l;
        r->size++;
        l->p = r;
        SortSons(r);
        UpdateKeys(l);
        Node* newRoot = r;
        SplitParent(r);
        return newRoot;
    }
    else {
        v = l;
        while (abs(hLeft - GetHeight(v)) > 1) {
            v = v->sons[0];
        }
        l->sons[l->size] = r;
        l->size++;
        r->p = l;
        UpdateKeys(r);
        Node* newRoot = l;
        SplitParent(l);
        return newRoot;
    }
}


SplitRetval Split(Node* t, int key) {
    SplitRetval ret;
    listNode* lList = (listNode*)malloc(sizeof(listNode));
    if (!lList) {
        ret.left = NULL;
        ret.right = NULL;
        return ret;
    }
    listNode* lPtr = lList;
    listNode* rList = (listNode*)malloc(sizeof(listNode));
    if (!rList) {
        ret.left = NULL;
        ret.right = NULL;
        return ret;
    }
    listNode* rPtr = rList;
    while (t->size != 1) {
        if (t->size == 2) {
            if (key <= t->keys[0]) {
                rPtr = ListAdd(rPtr, t->sons[1]);
                t = t->sons[0];
            }
            else {
                lPtr = ListAdd(lPtr, t->sons[0]);
                t = t->sons[1];
            }
        }
        else if (key <= t->keys[0]) {
            rPtr = ListAdd(rPtr, t->sons[1]);
            rPtr = ListAdd(rPtr, t->sons[2]);
            t = t->sons[0];
        }
        else if (key <= t->keys[1]) {
            lPtr = ListAdd(lPtr, t->sons[0]);
            rPtr = ListAdd(rPtr, t->sons[2]);
            t = t->sons[1];
        }
        else {
            lPtr = ListAdd(lPtr, t->sons[0]);
            lPtr = ListAdd(lPtr, t->sons[1]);
            t = t->sons[2];
        }
    }
    lPtr = ListAdd(lPtr, t);
    Node* l = NULL;
    Node* r = NULL;
    lPtr = lList->next;
    while (lPtr != NULL) {
        l = Merge(l, lPtr->val);
        lPtr = lPtr->next;
    }
    while (rPtr != rList) {
        r = Merge(r, rPtr->val);
        rPtr = rPtr->prev;
    }
    ret.left = l;
    ret.right = r;
    return ret;
}


int main() {
    char cmd;
    int key;
    Node* tree = NULL;
    while (fscanf(stdin, "%c %d", &cmd, &key) > 0) {
        if (cmd == 'a') {
            tree = Add(tree, key);
        }
        if (cmd == 'r') {
            tree = Del(tree, key);
        }
        if (cmd == 'f') {
            Node* s = Search(tree, key);
            if (s != NULL) {
                if (s->keys[0] == key) {
                    printf("yes\n");
                }
                else {
                    printf("no\n");
                }
            }
            else {
                printf("no\n");
            }
        }
    }
    return 0;
}