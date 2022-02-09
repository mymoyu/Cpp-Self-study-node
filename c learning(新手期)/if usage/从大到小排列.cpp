# include <stdio.h>

int main(void)
{
	int a, b, c;
	int t;//临时变量

	printf("请输入三个整数(中间以空格分隔): ");
	scanf("%d %d %d", &a, &b, &c);

	//编写代码完成a是最大值 b是中间值 c 是最小值,并且排列,此时用到的思想是数字互换
/*
	if (a > b && a > c)
		printf("最大值为a = %d\n", a);
	else if (b > a && b > c)
		printf("最大值为b = %d\n", b);
	else
		printf("最大值为c = %d\n", c);
*/
	if (a < b)
	{
		t = a;
		a = b;
		b = t;
	}

	if (a < c)
	{
		t = a;
		a = c;
		c = t;
	}
	if (b < c)
	{
		t = b;
		b = c;
		c = t;

	}
	printf("%d %d %d\n", a, b, c);

	return 0;
}
