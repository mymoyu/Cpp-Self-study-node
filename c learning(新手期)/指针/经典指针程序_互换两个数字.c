# include <stdio.h>

/*  不能完成互换功能
void huhuan(int a, int b)
{
    int t;

    t = a;
    a = b;
    b = t;

    return;
}//互换的是形参a,b 而不是主函数的a, b, 所以输出的结果依然是主函数的值,而不是调用后的值
*/

/*   不能完成互换功能
void huhuan (int * p, int * q)
{
    int * t;//如果要互换p和q的值, 则t必须是int *, 不能是int, 否则会出错

    t = p;
    p = q;
    q = t;
}//输出结果依然是a = 3, b = 5, 没有影响实参的值
*/

void huhuan (int * p, int * q)//p指向a q指向b, 所以*p就是a的值, *q就是b的值
{
    int t;

    t = *p; //p是 int*, *p是int
    *p = *q;
    *q = t;
}

int main(void)
{
    int a = 3;
    int b = 5;

    huhuan(&a, &b);//(*p, *q)是错误的, (a, b)也是错误的.
    printf("a = %d, b = %d\n", a, b);

    return 0;
}
