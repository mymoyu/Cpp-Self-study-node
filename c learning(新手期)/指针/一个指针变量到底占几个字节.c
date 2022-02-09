# include <stdio.h>

int main(void)
{
    char ch = 'A';
    int i = 99;
    double x = 66.6;
    char * p = &ch;
    int * q = &i;
    double * r = &x;

    printf("%d %d %d", sizeof(p), sizeof(q), sizeof(r));

    return 0;
}
/*
总结:
     一个指针变量, 无论它指向的变量占几个字节, 该指针只占四个字节

     一个变量的地址使用该变量首字节的地址来表示
*/
