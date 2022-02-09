# include <stdio.h>

f(int * p, int * j)
{
    *p = 1;
    *q = 2;
}

int main(void)
{
    int a = 3, b = 5;

    g(&a, &b);
    printf("%d %d\n", a, b);

    return 0;
}
/*
  如何通过被调函数修改主调函数普通变量的值
      1. 实参必须为该普通变量的地址
      2. 形参必须为指针变量
      3. 在被调函数中通过
             *形参名 = ......
         的方式就可以修改主调函数相关变量的值
*/
