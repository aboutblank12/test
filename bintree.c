#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0;

typedef int status;

typedef char telemtype;
typedef struct BinNode* BiTree;
typedef struct BinNode
{
	telemtype data;
	BiTree lchild, rchild;
}BinNode;

status CreatTree(BiTree *T)
{
	telemtype ch;
	scanf("%c", &ch);
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BinNode));
		if (!*T)
			return FALSE;
		(*T)->data = ch;
		CreatTree(&(*T)->lchild);
		CreatTree(&(*T)->rchild);
	}
	return TRUE; 
}

status InitTree(BiTree *T)
{
	*T = NULL;
	return TRUE;
}

status PreOrderTraverse(BiTree T)
{
	if (T == NULL)
		return FALSE;
	printf("%c", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	return TRUE;
}
status InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return FALSE;
	InOrderTraverse(T->lchild);
	printf("%c", T->data);
	InOrderTraverse(T->rchild);
	return TRUE;
}
status PostOrderTraverse(BiTree T)
{
	if (T == NULL)
		return FALSE;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c", T->data);
	return TRUE;
}
int main(void)
{
	BiTree bintree;
	InitTree(&bintree);
	CreatTree(&bintree);
	printf("\n前序遍历结果为：\n");
	PreOrderTraverse(bintree);
	printf("\n中序遍历结果为：\n");
	InOrderTraverse(bintree);
	printf("\n后序遍历结果为：\n");
	PostOrderTraverse(bintree);
	return 0;
}

