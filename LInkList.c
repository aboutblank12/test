#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int status;
typedef struct Node* LinkNode;

typedef struct Node
{
	ElemType data;
	LinkNode next;
}Node;

void CreatList1(LinkNode *L, int n)
{
	int i;
	LinkNode p;
	*L = (LinkNode)malloc(sizeof(Node));
	(*L)->next = NULL;
	for (i = 0; i < n; i++)
	{
		p = (LinkNode)malloc(sizeof(Node));
		p->data = i;
		p->next = (*L)->next;
		(*L)->next = p;
	}
	(*L)->data = n;
}
void CreatList2(LinkNode* L, int n)
{
	int i; 
	LinkNode r, p;
	(*L) = (LinkNode)malloc(sizeof(Node));
	r = (*L);
	for (i = 0; i < n; i++)
	{
		p = (LinkNode)malloc(sizeof(Node));
		p->data = i;
 		r->next = p;
		p->next = NULL;
		r = p;
	}
	(*L)->data = n;
}

status GetElem(LinkNode L, int i, ElemType* e)
{
	int j = 1;
	LinkNode p;
	p = L->next;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
	{
		return FALSE;
	}
	*e = p->data;
	return TRUE;

}

status ListInsert(LinkNode L, int i, ElemType e)
{
	int j = 1;
	LinkNode p, s;
	s = (LinkNode)malloc(sizeof(Node));
	s->data = e;
	p = L->next;
	while (p && j < i-1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) return FALSE;
	s->next = p->next;
	p->next = s;
	L->data++;
	return TRUE;
}
status ListDelete(LinkNode L, int i, ElemType* e)
{
	int j = 1;
	LinkNode p,q;
	q = (LinkNode)malloc(sizeof(Node));
	p = L->next;
	while (p && j < i-1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i-1) return FALSE;
	q = p->next;
	*e = q->data;
	p->next = q->next;
	free(q);
	L->data--;
}
status ClearList(LinkNode L)
{
	LinkNode p, q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	L->data = 0;
	return TRUE;
}
int main(void)
{
	int e;
	LinkNode head1;
	CreatList1(&head1, 5);
	LinkNode head2;
	CreatList2(&head2, 5);
	ListInsert(head2,2,20);
	ListDelete(head2, 2, &e);
	return 0;
}



//void Union(LinkNode* La, LinkNode Lb)
//{
//	int La_len, Lb_len, i;
//	ElemType e;
//	La_len = ListLength(*La);
//	Lb_len = ListLength(Lb);
//	for (i = 1; i <= Lb_len; i++)
//	{
//		GetElem(Lb, i, &e);
//		if (!LocateElem(*La, e))
//			ListInsert(*La, ++La_len, e);
//	}
//
//}