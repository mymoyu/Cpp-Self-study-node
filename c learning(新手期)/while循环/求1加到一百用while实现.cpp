# include <stdio.h>

int main (void)
{
	int sum = 0;
	int i;

/*
	for (i = 1; i<101; ++i)
	{
		sum = sum + i;
	}
*/
	i = 0;
	while (i < 101)
	{
		sum = sum + i;
		++i;
	}
	printf("sum = %d\n", sum);

	return 0;
}
//for 和 while 可以相互转化
