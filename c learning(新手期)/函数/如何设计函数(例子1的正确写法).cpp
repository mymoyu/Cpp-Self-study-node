/*
   求1到某个数字之间(包括该数字)所有的素数, 并将其输出
   用一个函数来判断一个数学是否是素数
   优点:
        代码的可读性相对较好
   缺点:
        可重用性仍然不是非常高, 比如求一千个数字, 他们每个数字从1到他本身的素数
		也要写1000次
*/

# include <stdio.h>

bool IsPrime(int m)
{
    int i;

    for (i=2; i<m; ++i)
    {
        if (0 == m % i)
            break;
    }
    if(i == m)
        return true;
    else
        return false;
}

int main(void)
{
    int val;
    int i;

    scanf("%d", &val);
    for (i=2; i<=val; ++i)
    {
        if ( IsPrime(i) )
            printf("%d\n", i);
    }

    return 0;
}
