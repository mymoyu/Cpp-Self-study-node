/*
    格式:  (A,B,C,D);
	功能: 从左到右执行
	      最终表达式的值是最后一项的值
*/
# include <stdio.h>

int main (void)
{
	int i;

	i = (3, 2, 5, 6);
	printf("%d\n", i);

	return 0;
}