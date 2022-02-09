# include <stdio.h>

int main(void)
{
    int a[5];// a是数组名 5是数组元素的个数 元素就是变量 a[0] -- a[4]
//  int a[3][4];  //3行4列, a[0][0]是第一个元素 a[i][j]第i+1行j+1列
    int b[5];

//    a = b;//error a是常量
    printf("%#X\n", &a[0]);//地址可以用十六进制输出或者用%p输出
    printf("%#X", a);

    return 0;
}
/*
  一维数组名
      一维数组名是个指针常量
      它存放的是一维数组第一个元素的地址
*/
/*
输出结果为:
-------------------------------
0X60FEEC
0060FEEC
Process returned 0 (0x0)   execution time : 0.017 s
Press any key to continue.
-------------------------------
*/
/*
a[1], a[2], a[3], a[i]里 1, 2, 3, i就是下标
下标和指针的关系
    如果p是给指针变量, 则
      p[i]永远等价于 *(p+i)
*/
