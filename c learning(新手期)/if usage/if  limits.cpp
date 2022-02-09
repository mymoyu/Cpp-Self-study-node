# include<stdio.h>

int main(void)
{
	if(1 > 2)
		printf("AAAA\n");
	printf("BBBB\n");

	return 0;
}
/*
    在Vc++6.0的输出结果:
	-----------------------
	BBBB
	-----------------------
*/
/*
    if(表达式)
         语句a;
		 语句b;
	解释: if默认只能控制语句a的执行或不执行,不能控制语句b.

  如果要控制两个或者两个以上的语句就只能
    if(表达式)
	{
	     语句a;
		 语句b;
	}
    此时if可以控制语句a和语句b
*/