/*
scanf()[通过键盘将数据输入到变量中]
两种用法:
    用法一:  scanf("输入控制符", 输入参数);
	功能:  将从键盘输入的字符转化为输入控制符所规定格式的数据,
	       然后存入以输入参数的值为地址的变量中
*/
#include <stdio.h>

int main(void)
{
	int i;
	char ch;

	scanf("%d", &i);//&i 表示i的地址 &是一个取地址符
	printf("i = %d\n", i);

/*	scanf("%c", &ch);
	printf("ch = %c\n", ch);*//*有这两时,输入12m,输出i = 12
	                                                 ch = m   
	有这两时,输入9km,输出i = 9
	                     ch = k 原因是char只能存放一个字符*/

	return 0;
}