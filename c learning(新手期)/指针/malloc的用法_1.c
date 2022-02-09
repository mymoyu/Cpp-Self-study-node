/*
  malloc 是memory(内存) allocate(分配)的缩写
*/
# include <stdio.h>
# include <malloc.h>

int main(void)
{
    int i = 5;//分配了四个字节 静态分配
    int * p = (int *)malloc(4);//若(int *)malloc(100)则有25个变量
    /*
        1. 要使用malloc函数,必须添加malloc.h这个头文件
        2. malloc函数只要一个形参, 并且形参是整型
        3. 4表示请求系统为本程序分配4个字节
        4. malloc函数只能返回第一个字节的地址
        5. 该行分配了八个字节, p变量占4个字节, p所指向的内存也占4个字节
        6. p本身所占的内存是静态分配的, p所指向的内存是动态分配的.
    */
    *p = 5; //*p代表的就是一个int变量, 只不过*p这个整型变量的内存分配方式和9行的i变量的分配方式不同
    free(p);//free(p)表示把p所指向的内存给释放掉 p本身的内存是静态的,不能由程序员手动释放,p本身的内存只能在p变量所在的函数运行终止时由系统自动释放
    printf("同志们好!\n");

    return 0;
}
