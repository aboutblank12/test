#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 100
#define IFINITY 65535
#define TRUE 1
#define FALSE 0



typedef char VetexType;
typedef int EdgeType;
typedef int elemtype;
typedef int status;
typedef struct QueueNode* QueueNodePtr;
typedef struct EdgeNode* EdgePtr;

char ch;
status visited[MAXVEX];

typedef struct EdgeNode
{
	int adjvex;
	EdgeType weight;
	EdgePtr next;
}EdgeNode;

typedef struct VetexNode
{
	VetexType data;
	EdgePtr firstedge;
}VetexNode, AdjList[MAXVEX];

typedef struct LinkGraph
{
	AdjList adjlist;
	int numvetex, numedge;
}LinkGraph;



typedef struct QueueNode
{
	elemtype data;
	QueueNodePtr next;
}QueueNode;

typedef struct Queue
{
	QueueNodePtr head, rear;
}Queue;






InitQueue(Queue* Q)
{
	Q->head = (QueueNodePtr)malloc(sizeof(Queue));
	Q->rear = Q->head;
}

status InQueue(Queue* Q, elemtype e)
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
status QueueEmpty(Queue* Q)
{
	if (Q->head == Q->rear)
	{
		return TRUE;
	}
	return FALSE;
}




status CreatLinkGraph(LinkGraph* G)
{
	int i, j, k;
	EdgePtr e;
	printf("请输入顶点数和边数:\n");
	scanf("%d,%d", &G->numvetex, &G->numedge);
	for (i = 0; i < G->numvetex; i++)
	{
		printf("请输入第%d个顶点的信息", i + 1);
		while (ch = getchar() != '\n' && ch != EOF);
		scanf("%c", &G->adjlist[i].data);
		G->adjlist[i].firstedge = NULL;
	}
	for (k = 0; k < G->numedge; k++)
	{
		printf("请输入边（vi, vj）对应的下标i, j\n");
		scanf("%d,%d", &i, &j);
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	return TRUE;
}

void DFS(LinkGraph* G, int i)
{
	EdgePtr p;
	printf("%c", G->adjlist[i].data);
	visited[i] = TRUE;
	p = G->adjlist[i].firstedge;
	while (p)
	{
		if (!visited[p->adjvex])
		{
			DFS(G, p->adjvex);
		}
		p = p->next;
	}
}

void DFSTRraverse(LinkGraph* G)
{
	int i;
	for (i = 0; i < G->numvetex; i++)
	{
		visited[i] = FALSE;
	}
	for (i = 0; i < G->numvetex; i++)
	{
		if (!visited[i])
		{
			DFS(G, i);
		}
	}
}

void BFSTraverse(LinkGraph* G)
{
	int i, e;
	EdgePtr p;
	Queue* Q;
	Q = (Queue*)malloc(sizeof(Queue));
	for (i = 0; i < G->numvetex; i++)
	{
		visited[i] = FALSE;
	}
	InitQueue(Q);
	for (i = 0; i < G->numvetex; i++)
	{
		if (!visited[i])
		{
			printf("%c", G->adjlist[i].data);
			visited[i] = TRUE;
			InQueue(Q, i);
			while (!QueueEmpty(Q))
			{
				OutQueue(Q, &e);
				p = G->adjlist[e].firstedge;
				while (p)
				{
					if (!visited[p->adjvex])
					{
						InQueue(Q, p->adjvex);
						printf("%c", G->adjlist[p->adjvex].data);
						visited[p->adjvex] = TRUE;
					}
					p = p->next;
				}
			}
		}
	}
}







status CreatTestGraph(LinkGraph*);

int main(void)
{
	LinkGraph *G;
	G = (LinkGraph*)malloc(sizeof(LinkGraph));
	CreatTestGraph(G);
	printf("\n深度优先遍历的结果为：\n");
	DFSTRraverse(G);
	printf("\n广度优先遍历的结果为：\n");
	BFSTraverse(G);
	return 0;
}

status CreatTestGraph(LinkGraph* G)
{
	int i, j;
	EdgePtr e;
	G->numvetex = 9; G->numedge = 15;
	for (i = 0; i < G->numvetex; i++)
	{
		G->adjlist[i].data = 'A'+i;
		G->adjlist[i].firstedge = NULL;
	}
	{
		i = 0; j = 1;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 1; j = 2;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 2; j = 3;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 3; j = 4;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 4; j = 5;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 0; j = 5;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 6; j = 1;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 5; j = 6;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 8; j = 1;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 2; j = 8;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 3; j = 8;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 3; j = 6;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 3; j = 7;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 6; j = 7;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	{
		i = 4; j = 7;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e = (EdgePtr)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
	return TRUE;
}

//int main(void)
//{
//	char get(void);
//	int ch;
//
//	while ((ch = get()) != EOF)
//		putchar(ch);
//	return 0;
//}
//char get(void)
//{
//	int ch;
//	ch = getchar();
//	while (getchar() != '\n')
//		continue;
//	return ch;
//}