# include <stdio.h>

int i = 99;

void f(int i)
{
    printf("i = %d\n", i);//输出结果为8, 说明发送冲突时, 局部变量会把全局变量屏蔽了
}

int main(void)
{
    f(8);

    return 0;
}
