/*
  确定一个一维数组需要几个参数[如果一个函数要处理一个一维数组,则需要接受该数组的哪些信息]
*/
# include <stdio.h>

//f函数可以输出任何一个一维数组的内容
void f(int * pArr, int len)
{
//    *pArr
//    *(pArr + 1)//数组的第二个元素

    int i;

    for(i=0; i<len; ++i)
        printf("%d ", *(pArr+i) );
    printf("\n");
}

int main(void)
{
    int a[5] = {1, 2, 3, 4, 5};
    int b[6] = {-1,-2,-3,4,5,-6};
    int c[100] = {1, 99, 22, 33};

    f(a, 5);//a 是int *类型, 数组长度无法通过数组名得知
    f(b, 6);
    f(c, 100);

    return 0;
}

