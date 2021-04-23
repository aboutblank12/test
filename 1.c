#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define MAXVEX 100
#define INFINITY 65535
#define TRUE 1
#define FALSE 0


typedef int status;
typedef char VertexType;
typedef int EdgeType;
typedef struct Graph* GraphPtr;

void CreatEdge(GraphPtr, int, int, int);
void TextGraph(GraphPtr G);

typedef struct Graph
{
    VertexType vertex[MAXVEX];
    EdgeType edge[MAXVEX][MAXVEX];
    int numvertex, numedge;
}Graph;

typedef struct Edge
{
    int begin;
    int weight;
    int end;
}Edge;

void MiniSpanTree_Prim(GraphPtr G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];
    int lowcost[MAXVEX];
    lowcost[0] = 0;
    adjvex[0] = 0;
    for (i = 1; i < G->numvertex; i++)
    {
        adjvex[i] = 0;
        lowcost[i] = G->edge[0][i];
    }
    for (i = 1; i < G->numvertex; i++)
    {
        min = INFINITY;
        k = 0;
        for (j = 1; j < G->numvertex; j++)
        {
            if (lowcost[j] && lowcost[j] < min)
            {
                min = lowcost[j];
                k = j;
            }
        }
        printf("(%d->%d)", adjvex[k], k);
        lowcost[k] = 0;
        for (j = 1; j < G->numvertex; j++)
        {
            if (lowcost[j] && G->edge[k][j] < lowcost[j])
            {
                lowcost[j] = G->edge[k][j];
                adjvex[j] = k;
            }
        }
    }
}

status Transfer_Graph_To_ArrEdge(GraphPtr G, Edge* edges)
{
    int i, j, k, n;
    int **visited;
    if( NULL == (visited = (int **)malloc(G->numvertex * sizeof(int *))))
        return FALSE;
    for(i = 0; i < G->numvertex; i++)
    {
        if( NULL == (visited[i] = (int *)malloc(G->numvertex * sizeof(int)))  )
           return FALSE;
    }


    for (i = 0; i < G->numedge; i++)
    {
        edges[i].begin = 0;
        edges[i].end = 0;
        edges[i].weight = INFINITY;
    }
    for (i = 0; i < G->numvertex; i++)
    {
        for (j = 0; j < G->numvertex; j++)
        {
            if (G->edge[i][j] == INFINITY)
                visited[i][j] = 0;
            else
                visited[i][j] = 1;
        }
    }
    for (i = 0; i < G->numvertex; i++)
    {
        for (j = 0; j < G->numvertex; j++)
        {
            if (visited[i][j])
            {
                visited[i][j] = 0;
                visited[j][i] = 0;
                for (k = 0; G->edge[i][j] != INFINITY && G->edge[i][j] > edges[k].weight; k++);
                for (n = G->numedge; n > k; n--)
                {
                    edges[n].begin = edges[n - 1].begin;
                    edges[n].end = edges[n - 1].end;
                    edges[n].weight = edges[n - 1].weight;
                }
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G->edge[i][j];
            }
        }
    }
    for(i = 0;i<G->numvertex;i++)
    {
        free(visited[i]);
    }
    free(visited);
    printf("创建的边集数组为:\n");
    printf("           begin  end  weight\n");
    for (i = 0; i < G->numedge; i++)
    {
        printf("edges[%d]:  %-5d  %-3d  %-5d\n", i, edges[i].begin, edges[i].end, edges[i].weight);
    }
    return TRUE;
}

int Find(int *parent, int f)
{
    while(parent[f]>0)
    {
        f = parent[f];
    }
    return f;
}

void MiniSpanTree_Kruskal(GraphPtr G)
{
    int i, n, m;
    Edge* edge;
    int parent[MAXVEX];
    edge = (Edge*)malloc(sizeof(Edge) * G->numedge);
    Transfer_Graph_To_ArrEdge(G, edge);
    for (i = 0; i<G->numvertex; i++)
    {
        parent[i] = 0;
    }
    printf("kruskal算法的最小生成树过程为:\n");
    for(i = 0;i<G->numedge;i++)
    {
        n = Find(parent,edge[i].begin);
        m = Find(parent,edge[i].end);
        if(n!=m)
        {
            parent[n] = m;
            printf("(%d,%d) %d\n", edge[i].begin, edge[i].end,edge[i].weight);
        }
    }
}



int main(void)
{
    GraphPtr G = (GraphPtr)malloc(sizeof(Graph));
    TextGraph(G);
    printf("prim算法生成的最小生成树的路径为\n");
    MiniSpanTree_Prim(G);
    MiniSpanTree_Kruskal(G);
    return 0;
}

void TextGraph(GraphPtr G)
{
    int i, j;
    G->numvertex = 9;
    G->numedge = 15;
    for (i = 0; i < G->numvertex; i++)
    {
        for (j = 0; j < G->numvertex; j++)
        {
            G->edge[i][j] = INFINITY;
        }
    }
    CreatEdge(G, 10, 0, 1);
    CreatEdge(G, 11, 0, 5);
    CreatEdge(G, 16, 1, 6);
    CreatEdge(G, 17, 5, 6);
    CreatEdge(G, 18, 2, 1);
    CreatEdge(G, 12, 8, 1);
    CreatEdge(G, 24, 3, 6);
    CreatEdge(G, 19, 6, 7);
    CreatEdge(G, 26, 4, 5);
    CreatEdge(G, 8, 2, 8);
    CreatEdge(G, 22, 2, 3);
    CreatEdge(G, 21, 3, 8);
    CreatEdge(G, 16, 3, 7);
    CreatEdge(G, 7, 4, 7);
    CreatEdge(G, 20, 3, 4);
    printf("创建的矩阵为:\n");
    for (i = 0; i < G->numvertex; i++)
    {
        for (j = 0; j < G->numvertex; j++)
            printf("%-5d,", G->edge[i][j]);
        printf("\n");
    }
}
void CreatEdge(GraphPtr G, int weight, int i, int j)
{
    G->edge[i][j] = weight;
    G->edge[j][i] = weight;
}
