# include <stdio.h>

int main (void)
{
	double delta = -1;

	if (delta > 0)
		printf("两个解\n");
//	    printf("hh\n");//应该去掉
	else if (delta == 0)
		printf("有一个唯一解!\n");
	else
		printf("无解\n");

	return 0;
}
//编译失败:没有以else if开头的语句类型,内容illegal,
//或者解释为:没有匹配if造成.
//else if为顺序性的.