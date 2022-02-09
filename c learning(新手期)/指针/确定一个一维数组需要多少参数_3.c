# include <stdio.h>

void f(int * pArr, int len)
{
    int i ;

    for (i=0; i<len; ++i)
        printf("%d\n", pArr[i]); //*(pArr + i)等价于 pArr[i] 也等价于 b[i] 也等价于 *(b + i)
    printf("\n");
}

int main(void)
{
    int a[5] = {1, 2, 3, 4, 5};
    int b[6] = {-1,-2,-3,4,5,-6};
    int c[100] = {1, 99, 22, 33};

    f(b, 6);

    b[i]

    return 0;
}
