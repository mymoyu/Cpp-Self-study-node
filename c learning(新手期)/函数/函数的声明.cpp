# include <stdio.h>

void f(void);//函数声明, 分号不能丢掉

int main(void)
{
    f();

    return 0;
}

void f(void)
{
    printf("haha!\n");
}
/*
函数前置声明:  1.告诉编译器即将可能出现的若干个字母代表的是一个函数
               2.告诉编译器即将可能出现的若干个字母所代表的函数的形参和返回值的具体情况
               3.函数声明是一个语句, 末尾必须加分号
               4.对库函数的声明是通过 # include <库函数所在的文件的名字.h>

  5.前置声明一般不写形参  像int max(int a)的前置声明: int max(int );
*/
