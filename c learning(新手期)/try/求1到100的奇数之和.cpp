# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;

	for(i = 1;i <= 100; ++i)
	{
		if (i % 2 == 1)
			sum = sum + i;
	}
	printf("1到100的奇数之和为:%d\n", sum);
}