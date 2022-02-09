# include<stdio.h>

int main(void)
{
    int a[5] = {1, 2, 3, 4, 5};
        //a是数组的名字, 5表示数组元素的个数,并且这五个元素分别用a[0], a[1],.... a[4].五个元素只能到a[4]
        //a[0]表示第一个元素 a[1]表示第二个元素
    int i;

    for (i=0; i<5; ++i)
        printf("%d\n", a[i]);
    /*
    输出结果:
    1
    2
    3
    4
    5

    Process returned 0 (0x0)   execution time : 0.012 s
    Press any key to continue.
    */

    printf("%d\n", a[100]);

    return 0;
}
/*
数组,为了解决大量同类型数据的存储和使用问题
为了模拟现实事件
*/
