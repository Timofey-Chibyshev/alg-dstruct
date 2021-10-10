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

int AddElementEnd(int value, list_t* head)
{
    list_t* tmp = NULL;
    list_t* p = NULL;
    p = head;
    tmp = (list_t*)malloc(sizeof(list_t));
    if (tmp == NULL)
    {
        printf("\nMemory is no allocated!\n");
        return 0;
    }
    tmp->data = value;
    tmp->next = NULL;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = tmp;
    return 1;
}

void ListPrint(list_t* head, int size)
{
    if (size == 0)
    {
        printf("clear list\n");
        return;
    }
    list_t* p = NULL;
    p = head;
    do
    {
        printf("%d ", p->data);
        p = p->next;
    } while (p != NULL);
    printf("\n\n");
}

int ReadNumbers(const char* filename, list_t* head, int* len)
{
    FILE* input = fopen(filename, "r");
    if (input == NULL)
    {
        printf("cant open file\n");
        return 0;
    }
    int value = 0;
    fseek(input, 0, SEEK_SET);
    fscanf_s(input, "%d", &head->data);
    while(fscanf(input, "%d", &value) == 1)
    {
        AddElementEnd(value, head);
        (*len)++;
    }
    if (!feof(input))
    {
        printf("\nОшибка чтения: достигнут конец файла\n");
    }
    else if (ferror(input))
    {
        printf("\nОшибка чтения файла\n");
    }
    fclose(input);
    return 1;
}

int Merge(list_t* first, list_t* second, list_t* sum, int size1, int size2)
{
    int i = 0;
    if ((size1 == 0) && (size2 == 0))
    {
        return 0;
    }
    if ((size1 == 0) || (size2 == 0))
    {
        if (size1 == 0)
        {
            sum->data = second->data;
            sum->next = second->next;
        }
        if (size2 == 0)
        {
            sum->data = first->data;
            sum->next = first->next;
        }
        return 1;
    }
    while ((first != 0) && (second != 0))
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
    return 2;
}

int Write(list_t* sum, const char* filename, int size)
{
    FILE* input = fopen(filename, "w");
    if (input == NULL)
    {
        printf("cant open file\n");
        return 0;
    }
    if (size == 0)
    {
        fclose(input);
        return 1;
    }
    else
    {
        while (sum->next)
        {
            fprintf(input, "%d ", sum->data);
            sum = sum->next;
        }
        fprintf(input, "%d ", sum->data);
        fclose(input);
        return 2;
    }
}