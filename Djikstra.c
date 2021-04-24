#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 100
#define INFINITY 65535
#define TRUE 1

typedef int status;
typedef char VertexType;
typedef int EdgeType;
typedef struct Graph* GraphPtr;
typedef int Patharc2[MAXVEX][MAXVEX];
typedef int ShortPathTable2[MAXVEX][MAXVEX];
typedef int Patharc[MAXVEX];
typedef int ShortPathTable[MAXVEX];


void CreatEdge(GraphPtr, int, int, int);
void TextGraph(GraphPtr G);

typedef struct Graph
{
    VertexType vertex[MAXVEX];
    EdgeType edge[MAXVEX][MAXVEX];
    int numvertex, numedge;
}Graph;

void ShorttestPath_Djikstra(GraphPtr G, int v0, Patharc *P, ShortPathTable *D){
    int i, j, k, min;
    int *final = (int *)malloc(sizeof(int)*G->numvertex);
    for(i = 0; i < G->numvertex; i++)
    {
        final[i] = 0;
        (*P)[i] = 0;
        (*D)[i] = G->edge[v0][i];
    }
    (*D)[v0] = 0;
    final[v0] = 1;
    for(i = 1;i<G->numvertex;i++)
    {
        min = INFINITY;
        for(j = 0; j<G->numvertex;j++)
        {
            if(!final[j]&&(*D)[j]<min)
            {
                k = j;
                min = (*D)[j];
            }
        }
        final[k] = 1;
        for(j = 0; j<G->numvertex;j++)
        {
            if(!final[j]&& (min + G->edge[k][j]<(*D)[j]))
            {
                (*P)[j] = k;
                (*D)[j] = min + G->edge[k][j];
            }
        }
    }
    printf("Djikstra算法中D，P数组的值为");
    printf("\nD数组的值为:\n");
    for(i = 0; i<G->numvertex;i++)
    {
        printf("%d ",(*D)[i]);
    } 
    printf("\nP数组的值为:\n");
    for(i = 0; i<G->numvertex;i++)
    {
        printf("%d ",(*P)[i]);
    } 
}


void ShortPathTable_Floyd(GraphPtr G, Patharc2 *P, ShortPathTable2 *D)
{
    int v, w, k;
    for(v = 0;v<G->numvertex;v++)
    {
        for(w = 0;w < G->numvertex;w++)
        {
            (*D)[v][w] = G->edge[v][w];
            (*P)[v][w] = w;
        }
    }
    for(k = 0;k < G->numvertex;k++)
    {
        for(v = 0;v < G->numvertex;v++)
        {
            for(w = 0;w < G->numvertex;w++)
            {
                if((*D)[v][w] > ((*D)[v][k] + (*D)[k][w]))
                {
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    (*P)[v][w] = (*P)[v][k];
                }
            }
        }
    }
    printf("\nFLoyd算法生成的D矩阵为:\n");
    for (v = 0;v< G->numvertex;v++)
    {
        for(w = 0; w < G->numvertex;w++)
        {     
            printf("%-3d", (*D)[v][w]);
        }
        printf("\n");
    }
    printf("FLoyd算法生成的P矩阵为:\n");
    for (v = 0;v< G->numvertex;v++)
    {
        for(w = 0; w < G->numvertex;w++)
        {     
            printf("%-3d", (*P)[v][w]);
        }
        printf("\n");
    }
}

int main (void)
{
    int v0 = 0;
    Patharc *P = (Patharc *)malloc(sizeof(Patharc));
    ShortPathTable *D = (ShortPathTable *)malloc(sizeof(ShortPathTable));
    Patharc2 *P2 = (Patharc2 *)malloc(sizeof(Patharc2));
    ShortPathTable2 *D2 = (ShortPathTable2 *)malloc(sizeof(ShortPathTable2));
    GraphPtr G = (GraphPtr)malloc(sizeof(Graph));
    TextGraph(G);
    ShorttestPath_Djikstra(G, v0, P, D);
    ShortPathTable_Floyd(G, P2, D2);

    return 0;
}


void TextGraph(GraphPtr G)
{
    int i, j;
    G->numvertex = 9;
    G->numedge = 16;
    for (i = 0; i < G->numvertex; i++)
    {
        for (j = 0; j < G->numvertex; j++)
        {
            if(i==j)
            {
                G->edge[i][j] = 0;
            }
            else
            { 
                G->edge[i][j] = INFINITY;
            }
        }
    }
    CreatEdge(G, 1, 0, 1);
    CreatEdge(G, 5, 0, 2);
    CreatEdge(G, 3, 1, 2);
    CreatEdge(G, 7, 1, 3);
    CreatEdge(G, 5, 4, 1);
    CreatEdge(G, 1, 2, 4);
    CreatEdge(G, 7, 2, 5);
    CreatEdge(G, 2, 3, 4);
    CreatEdge(G, 3, 4, 5);
    CreatEdge(G, 3, 3, 6);
    CreatEdge(G, 6, 4, 6);
    CreatEdge(G, 9, 4, 7);
    CreatEdge(G, 5, 5, 7);
    CreatEdge(G, 2, 6, 7);
    CreatEdge(G, 7, 6, 8);
    CreatEdge(G, 4, 7, 8);
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
