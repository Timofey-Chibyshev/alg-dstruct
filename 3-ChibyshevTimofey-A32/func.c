#include "header.h"

list_t* Create()
{
    list_t* tmp = NULL;
    tmp = (list_t*)malloc(sizeof(list_t));
    if (tmp == NULL)
    {
        printf("\nMemory is no allocated!\n");
        exit(-1);
    }
    else
    {
        tmp->next = NULL;
    }
    return(tmp);
}

void Destroy(list_t* head)
{
    list_t* p = NULL;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
}

int NumberCount(FILE* input)
{
    char let;
    int value, l, counter;
    l = 0;
    counter = 0;
    fseek(input, 0, SEEK_SET);
    while (!feof(input))
    {
        if (fscanf(input, "%d", &value) == 1)
        {
            counter++;
        }
        else if (fscanf(input, "%c", &let) == 1)
        {
            l++;
        }
    }
    return counter;
}

void AddElementEnd(int value, list_t* head)
{
    list_t* tmp = NULL;
    list_t* p = NULL;
    p = head;
    tmp = (list_t*)malloc(sizeof(list_t));
    if (tmp == NULL)
    {
        printf("\nMemory is no allocated!\n");
        return;
    }
    tmp->data = value;
    tmp->next = NULL;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = tmp;
}

void ListPrint(list_t* head)
{
    list_t* p = NULL;
    p = head;
    do
    {
        printf("%d ", p->data);
        p = p->next;
    } while (p != NULL);
    printf("\n\n");
}

int ReadNumbers(FILE* input, list_t* head, int size)
{
    int value = 0;
    int l = 0;
    if (size == 0)
    {
        return 0;
    }
    fseek(input, 0, SEEK_SET);
    fscanf_s(input, "%d", &head->data);
    for (int i = 1; i < size; ++i)
    {
        if (fscanf(input, "%d", &value) == 1)
        {
            AddElementEnd(value, head);
        }
    }
    return 1;
}

void Merge(list_t* first, list_t* second, list_t* sum)
{
    int i = 0;
    while (first != 0 && second != 0)
    {
        if (first->data < second->data)
        {
            if (i == 0)
            {
                sum->data = first->data;
                sum->next = first->next;
                first = first->next;
            }
            else
            {
                sum->next = first;
                sum = first;
                first = first->next;
            }
        }
        else
        {
            if (i == 0)
            {
                sum->data = second->data;
                sum->next = second->next;
                second = second->next;
            }
            else
            {
                sum->next = second;
                sum = second; second = second->next;
            }
        }
        i++;
        sum->next = (first == 0) ? second : first;
    }
}

list_t* InserationSort(list_t* head)
{
    list_t* newhead = NULL;
    list_t* cur = NULL;
    list_t* buffer = NULL;
    while (head != NULL)
    {
        buffer = head;
        head = head->next;
        if (newhead == NULL || buffer->data < newhead->data)
        {
            buffer->next = newhead;
            newhead = buffer;
        }
        else
        {
            cur = newhead;
            while (cur->next != NULL && !(buffer->data < cur->next->data))
            {
                cur = cur->next;
            }
            buffer->next = cur->next;
            cur->next = buffer;
        }
    }
    return newhead;
}