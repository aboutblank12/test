#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 100
#define INFINITY 65535
#define TRUE 1
#define FALSE 0

typedef char VertexType;
typedef int EdgeType;
typedef int status;
typedef int StackElemType;
typedef struct EdgeNode* EdgePtr;

typedef struct EdgeNode 
{
	int adjvex;
	EdgeType weight;
	EdgePtr next;
}EdgeNode;

typedef struct VertexNode
{
	VertexType data;
	int in;
	EdgePtr firstedge;
}VertexNode, VertexList[MAXVEX];

typedef struct Graph
{
	VertexList graphvertexlist;
	int numedge, numvertex;
}Graph, *GraphPtr;

typedef struct StackNode* StackLink;
typedef struct StackNode
{
	StackElemType data;
	StackLink next;
}StackNode;
typedef struct LinkStack
{
	StackLink top;
	int length;
}LinkStack;
status Push(LinkStack* s, StackElemType e)
{
	StackLink p = (StackLink)malloc(sizeof(StackNode));
	p->data = e;
	p->next = s->top;
	s->top = p;
	s->length++;
	return TRUE;
}
status Pop(LinkStack* s, StackElemType* e)
{
	StackLink p = s->top;
	if (s->top == NULL) return FALSE;
	*e = p->data;
	s->top = p->next;
	free(p);
	s->length--;
	return TRUE;
}

InsertEdge(GraphPtr, int, int, EdgeType);
void CreatTestGraph(GraphPtr);

status Toplogicalsort(GraphPtr G)
{
	int i, n;
	int count = 0;
	EdgePtr e;
	LinkStack* s;
	s = (LinkStack*)malloc(sizeof(LinkStack));
	s->top = NULL;
	s->length = 0;
	for (i = 0; i < G->numvertex; i++)
	{
		if (!G->graphvertexlist[i].in)
		{
			Push(s, i);
		}
	}
	while (s->top)
	{
		Pop(s, &n);
		printf("%c ", G->graphvertexlist[n].data);
		count++;
		G->graphvertexlist[n];
		for (e = G->graphvertexlist[n].firstedge; e;)
		{
			G->graphvertexlist[e->adjvex].in--;
			if (!G->graphvertexlist[e->adjvex].in)
			{
				Push(s, e->adjvex);
			}
			e = e->next;
		}
	}
	if (count == G->numvertex)
		return TRUE;
	else
		return FALSE;
}

int main(void)
{
	GraphPtr G;
	G = (GraphPtr)malloc(sizeof(Graph));
	CreatTestGraph(G);
	Toplogicalsort(G);

	return 0;
}

void CreatTestGraph(GraphPtr G)
{
	int i;
	G->numvertex = 14;
	G->numedge = 20;
	for (i = 0; i < G->numvertex; i++)
	{
		G->graphvertexlist[i].in = 0;
		G->graphvertexlist[i].data = 'A' + i;
		G->graphvertexlist[i].firstedge = NULL;
	}
	InsertEdge(G, 0, 4, 1);
	InsertEdge(G, 0, 5, 1);
	InsertEdge(G, 0, 11, 1);
	InsertEdge(G, 1, 2, 1);
	InsertEdge(G, 1, 4, 1);
	InsertEdge(G, 1, 8, 1);
	InsertEdge(G, 2, 5, 1);
	InsertEdge(G, 2, 6, 1);
	InsertEdge(G, 2, 9, 1);
	InsertEdge(G, 3, 2, 1);
	InsertEdge(G, 3, 13, 1);
	InsertEdge(G, 4, 7, 1);
	InsertEdge(G, 5, 8, 1);
	InsertEdge(G, 5, 12, 1);
	InsertEdge(G, 6, 5, 1);
	InsertEdge(G, 8, 7, 1);
	InsertEdge(G, 9, 10, 1);
	InsertEdge(G, 9, 11, 1);
	InsertEdge(G, 10, 13, 1);
	InsertEdge(G, 12, 9, 1);
}

InsertEdge(GraphPtr G, int v, int w, EdgeType weight)
{
	EdgePtr p;
	p = (EdgePtr)malloc(sizeof(EdgeNode));
	p->adjvex = w;
	p->weight = weight;
	p->next = G->graphvertexlist[v].firstedge;
	G->graphvertexlist[v].firstedge = p;
	G->graphvertexlist[w].in++;
}