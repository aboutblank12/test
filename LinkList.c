#include<stdio.h>
#include <stdlib.h>


typedef int ElemType;
typedef struct LinkNode 
{
    ElemType data;
    struct LinkNode * next;
}LinkNode, *LinkListPtr;

void Insert(LinkListPtr head, int location, ElemType e)
{
    int i;
    LinkListPtr q = (LinkListPtr)malloc(sizeof(LinkNode));
    q->data = e;
    LinkListPtr p = head; 
    for(i = 1;i<location;i++)
    {
        p = p->next;
    }
    q->next = p->next;
    p->next = q;
}
void Delete(LinkListPtr head, int location, ElemType* e)
{
    int i;
    LinkListPtr p = head; 
    for(i = 1;i<location;i++)
    {
        p = p->next;
    }
    *e = p->next->data;
    p->next = p->next->next;
}

void del(LinkListPtr L, int x)
{
    LinkListPtr p = L;
    LinkListPtr q = L;
    while (p->next)
    {
        q = p->next;
        if(q->data == x)
        {
            p->next = q->next;
            free(q);
        }
        else p = p->next;
    }
}
int main(void)
{
    int i;
    int j;
    LinkListPtr p;
    LinkListPtr head;
    head = (LinkListPtr)malloc(sizeof(LinkNode));
    head->data = 0;
    head->next = NULL;
    for(i = 1;i<=10;i++)
    {
        Insert(head, i, i);
    }
    //for(p = head->next; p; p = p->next)
    //{
    //    printf("%d ", p->data);
    //}
    //printf("\n");
    Insert(head, 3, 6);
    for(p = head->next; p; p = p->next)
    {
        printf("%d ", p->data);
    }
    printf("\n");
    del(head, 6);
    for(p = head->next; p; p = p->next)
    {
        printf("%d ", p->data);
    }
    printf("\n");

    return 0;
}
