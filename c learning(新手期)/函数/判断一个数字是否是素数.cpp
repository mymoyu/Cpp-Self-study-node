# include <stdio.h>

bool IsPrime(int val)//素数的英文名,只判断一个数字是否为素数,就只写一个形参
{
    int i;

    for (i=2; i<val; ++i)
    {
        if(val%i == 0)
            break;
    }
    if (i == val)
        return true;
    else
        return false;//一旦使用return 后面的就不会执行了
}//一般一个功能写一个函数,写成true和false是为了让别人自己去表达,故不应该用printf

int main(void)
{
    int m;//这里用val也是可以的

    scanf("%d", &m);
    if ( IsPrime(m) )
        printf("Yes!\n");
    else
        printf("No!\n");

    return 0;
}
