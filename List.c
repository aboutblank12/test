#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "operate.h"


int main(void)
{
	int Elemget;
	ArrList mylist;
	ArrList* L= &mylist;
	InitList(L);
	preset(L, 20);
	GetElem(L, 5, &Elemget);
	ListInsert(L, 20, 80);
	//测试插入的节点
	for (int i = 0; i < L->length; i++)
	{
		printf("%d ", L->elem[i]);
	}
	printf("\n");
	ListDelete(L, 20, &Elemget);
	//测试删除的节点
	for (int i = 0; i < L->length; i++)
	{
		printf("%d ", L->elem[i]);
	}
	printf("\n");
	return 0;
}

