/*
   用两个函数来实现求1到某个数字之间(包括该数字)所有的素数, 并将其输出
   本程序 与前面的那个相比, 代码量更少, 可重用性更高

   一个函数的功能尽量独立,单一, 可重用性才会比较高
   多学习, 多模仿牛人的代码
*/
# include <stdio.h>

bool IsPrime(int m);

//本函数的功能是把1到n之间所有的素数在显示器上输出
void TraverseVal(int n)
{
    int i;

    for (i=2; i<=n; ++i)
    {
        if ( IsPrime (i) )
            printf("%d\n", i);
    }
}

//本函数的功能是: 判断m是否是素数, 是返回true, 不是返回false
bool IsPrime(int m)
{
    int i;

    for (i=2; i<m; ++i)
    {
        if (0 == m%i)
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

    scanf("%d", &val);
    TraverseVal(val);

    return 0;
}
