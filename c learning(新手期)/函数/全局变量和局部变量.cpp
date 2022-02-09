# include <stdio.h>

int k = 1000;//全局变量, 要放在该函数之前才可以使用

void g()
{
    printf("k = %d\n", k);
}

void f(void)
{
    g();
    printf("k = %d\n", k);
}
/*
void f(int i)
{
    int j = 20;//局部变量
    g();
    printf("k = %d\n", k);
}
*/

int main(void)
{
//    int i = 10;

    f();

    return 0;
}
