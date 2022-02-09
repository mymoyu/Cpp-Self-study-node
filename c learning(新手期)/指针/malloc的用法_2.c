# include <stdio.h>
# include <malloc.h>

void f(int * q)
{
    //*p = 200; //error
    //q = 200; //error
    *q = 200; //ok   注: 指针变量前面才能加* 所以**q是错误的
    //free(q);  //把q所指向的内存释放掉
}

int main(void)
{
    int * p = (int *)malloc(sizeof(int)); //sizeof(int)返回值是int所占的字符数
    *p = 10;

    printf("%d\n", *p);
    f(p);
    printf("%d\n", *p);

    return 0;
}
