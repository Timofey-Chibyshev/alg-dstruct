#include "header.h"

list_t* Create()
{
    list_t* tmp = NULL;
    tmp = (list_t*)malloc(sizeof(list_t));
    if (tmp == NULL)
    {
        printf("\nMemory is no allocated!\n");
        return NULL;
    }
    else
    {
        tmp->next = NULL;
    }
    return tmp;
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
    while (fscanf(input, "%d", &value) == 1)
    {
        if (AddElementEnd(value, head))
        {
            (*len)++;
        }
        else
        {
            return 0;
        }
    }
    if (!feof(input))
    {
        printf("\n������ ������: ��������� ����� �����\n");
    }
    else if (ferror(input))
    {
        printf("\n������ ������ �����\n");
    }
    fclose(input);
    return 1;
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

int Merge(list_t* first, list_t* second, list_t* sum, int size1, int size2)
{
    int i = 0;
    int buffer;
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
            second = second->next;
            sum->next = NULL;
            while (second != 0)
            {
                if (AddElementEnd(second->data, sum))
                {
                    second = second->next;
                }
                else
                {
                    return -1;
                }
            }
        }
        if (size2 == 0)
        {
            sum->data = first->data;
            sum->next = first->next;
            first = first->next;
            sum->next = NULL;
            while (first != 0)
            {
                if (AddElementEnd(first->data, sum))
                {
                    first = first->next;
                }
                else
                {
                    return -1;
                }
            }
        }
        return 1;
    }
    if (first->data < second->data)
    {
        buffer = first->data;
        sum->data = first->data;
        sum->next = first->next;
        first = first->next;
    }
    else
    {
        if (first->data > second->data)
        {
            buffer = second->data;
            sum->data = second->data;
            sum->next = second->next;
            second = second->next;
        }
        else
        {
            buffer = first->data;
            sum->data = first->data;
            sum->next = first->next;
            first = first->next;
            second = second->next;
        }
    }
    sum->next = NULL;
    while ((first != 0) && (second != 0))
    {
        if (first->data < second->data)
        {
            if (buffer < first->data)
            {
                if (AddElementEnd(first->data, sum))
                {
                    buffer = first->data;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                first = first->next;
            }
        }
        else
        {
            if (first->data > second->data)
            {
                if (buffer < second->data)
                {
                    if (AddElementEnd(second->data, sum))
                    {
                        buffer = second->data;
                    }
                    else
                    {
                        return -1;
                    }
                }
                else
                {
                    second = second->next;
                }
            }
            else
            {
                if (AddElementEnd(second->data, sum))
                {
                    buffer = second->data;
                    first = first->next;
                    second = second->next;
                }
                else
                {
                    return -1;
                }
            }
        }
    }
    if (first == 0)
    {
        while (second != 0)
        {
            if (AddElementEnd(second->data, sum))
            {
                second = second->next;
            }
            else
            {
                return -1;
            }
        }
    }
    if (second == 0)
    {
        while (first != 0)
        {
            if (AddElementEnd(first->data, sum))
            {
                first = first->next;
            }
            else
            {
                return -1;
            }
        }
    }
    return 2;
}

int AllOperations(const char* name1, const char* name2, const char* sum)
{
    int size1, size2, k;
    size1 = 0;
    size2 = 0;
    k = 0;
    list_t* first = Create();
    list_t* second = Create();
    list_t* third = Create();
    if (ReadNumbers(name1, first, &size1))
    {
        printf("\nThe numbers are read...\n");
    }
    else
    {
        printf("\nERROR!!!\n");
        free(first);
        free(second);
        free(third);
        return -1;
    }
    printf("\nFirst list: \n");
    ListPrint(first, size1);
    if (ReadNumbers(name2, second, &size2))
    {
        printf("\nThe numbers are read...\n");
    }
    else
    {
        printf("\nERROR!!!\n");
        free(first);
        free(second);
        free(third);
        return -1;
    }
    printf("\nSecond list: \n");
    ListPrint(second, size2);
    k = Merge(first, second, third, size1, size2);
    printf("\nSum list: \n");
    ListPrint(third, (size1 + size2));
    Write(third, sum, (size1 + size2));
    Destroy(first);
    Destroy(second);
    Destroy(third);
    return k;
}







