# include <stdio.h>

void f(int * pArr, int len)
{
    pArr[3] = 88;//pArr[3] = * (pArr + 3), 所以
}

int main(void)
{
    int a[6] = {1, 2, 3, 4, 5, 6};

    printf("%d\n", a[3]); //4
    f(a, 6);
    printf("%d\n", a[3]);//a[3]就是 * (a + 3)

    return 0;
}
