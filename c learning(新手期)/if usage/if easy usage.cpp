# include<stdio.h>

int main(void)
{
	if (3>2)
		printf("AAAA\n"); //会输出AAAA

	if (0)
		printf("BBBB\n"); //不会输出

	if (0 == 0)
		printf("CCCC\n"); //会输出


	return 0;
}

/*  格式:
          if (表达式)
		        语句
	功能:
	     如果表达式为真,执行语句
		 如果表达式为假,语句不执行
*/