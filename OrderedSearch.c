#include<stdio.h>
#include<stdlib.h>

int BinarySearch(int *a, int length, int key)
{
    int low, high, mid;
    low = 0;
    high = 10;
    while(1)
    {
        if(low == high)
        {
            return 0;
        }
        else
        {
            mid = (low + high)/2;
        }
        if(key < a[mid])
        {
            high = mid;
        }
        else if(key > a[mid])
        {
            low = mid;
        }
        else
        {
            return mid;
        }

    }
}
int main(void)
{ 
    int consequence;
    int a[10] = {0, 4, 5, 12, 13, 15, 7, 8, 10, 2};
    consequence = BinarySearch(a, 10, 10);
    if(!consequence)
    {
        printf("����ʧ��");
    }
    else
    { 
        printf("Ҫ���ҵ������ڵ�%dλ", consequence);
    }
    return 0;
}
