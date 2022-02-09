# include <stdio.h>
# include <stdlib.h>
# include <time.h>
int main()
{
    int a, b;

    srand(time(0)); //设置种子, 而选用的种子用时间来确定,  time(0)指当前的时间
    a = rand() % 100; //rand()产生随机数而%100就是让取值都在一百以内
    b = rand() % 101 + 100; //让随机值在100 - 500之间 [a, b]可以用(b-a+1)+a

    printf("a = %d\n", a);
    printf("b = %d", b);

    return 0;
}
