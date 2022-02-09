# include <stdio.h>

void f(int i, float x)
{
    printf("%d\n", i);//形参
}

int main(void)
{
    f(5, 6.6);//5是实参

    return 0;
}
//形参与实参, 数据类型相互兼容, 位置和数目都得一一对应
