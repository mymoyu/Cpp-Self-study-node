# include<stdio.h>

void f(void)//无参函数
{
    int i;

    for(i=0; i<5; ++i)
    {
        printf("大家辛苦了!\n");
        return;//break终止for循环
               //return表达式的含义: 1.终止被调函数,向主调函数返回表达式的值
    }          //如果表达式为空, 则只终止函数, 不向主调函数返回任何值
    printf("同志们好!\n");
}

int main(void)
{
    f();

    return 0;
}
/*
void f()
{
    return;  //return只用来终止函数, 不向主调函数返回任何值
}

int f()
{
    return 10;  //第一 :终止函数, 第二: 向主调函数返回10
}
*/
