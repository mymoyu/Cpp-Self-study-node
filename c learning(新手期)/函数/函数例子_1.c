# include <stdio.h>

//max是函数的名字, i和j是形式参数(函数中的变量), 简称形参, void表示函数没有返回值
void max1(int i, int j)// 此处的max是你定义的函数,可以不写max写成min之类都可以
{
    if (i > j)
        printf("%d\n", i);
    else
        printf("%d\n", j);
}

int max2(int i, int j)
{
    if (i > j)
        return i;
    else
        return j;
}

/*
如果程序没有定义两个整型变量,程序会报错
*/

int main(void)//main也是函数的名字, 主函数最优先执行
{
    int a, b, c, d, e, f;

    a = 1;
    b = 2;
    c = 3;
    d = 9;
    e = -5;
    f = 100;

	printf("%d\n", max2(a, b));
    printf("%d\n", max2(c, d));
    printf("%d\n", max2(e, f));

//  max1(a, b);//max是函数名,a会发送给i, b会发送给j,然后程序会跳到max函数中执行.
//  max1(c, d);//若你写此行这个代码,编译器就认为你一定定义了一个名为max的函数
//  max1(e, f);//如果你实际没有定义max这个函数,程序就会报错.

/*
    if (a > b)
        printf("%d\n", a);
    else
        printf("%d\n", b);

    if (c > d)
        printf("%d\n", c);
    else
        printf("%d\n", d);

    if (e > f)
        printf("%d\n", e);
    else
        printf("%d\n", f);
*///原始方法太繁琐

    return 0;
}
/*
  为什么需要函数?
       避免了重复性操作
       有利于程序的模块化
  c语言的基本单位是函数
*/
