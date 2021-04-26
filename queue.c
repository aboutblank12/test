#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int elemtype;
typedef int status;
typedef struct QueueNode* QueueNodePtr;

typedef struct QueueNode
{
	elemtype data;
	QueueNodePtr next;
}QueueNode;

typedef struct Queue
{
	QueueNodePtr head, rear;
}Queue;

InitQueue(Queue *Q)
{
	Q->head = (QueueNodePtr)malloc(sizeof(Queue));
	Q->rear = Q->head;
}

status InQueue(Queue *Q,elemtype e)
{
	QueueNodePtr r;
	r = (QueueNodePtr)malloc(sizeof(Queue));
	if (!r) return FALSE;
	r->data = e;
	r->next = NULL;
	Q->rear->next = r;
	Q->rear = r;
	return TRUE;
}

status OutQueue(Queue* Q, elemtype* e)
{
	if (Q->head == Q->rear)
	{
		return FALSE;
	}
	QueueNodePtr h;
	h = Q->head->next;
	*e = h->data;
	Q->head->next = h->next;
	if (Q->rear == h)
	{
		Q->rear = Q->head;
	}
	free(h);
	return TRUE;
}

int main(void)
{
	status a;
	elemtype e;
	Queue Q;
	InitQueue(&Q);
	for (e = 0; e < 10; e++)
	{
		InQueue(&Q, e);
    }
	OutQueue(&Q, &e);
	return 0;
}