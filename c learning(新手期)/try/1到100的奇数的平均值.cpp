# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;
	float avg = 0;//average
	int cnt = 0;

	for(i = 1; i <= 100; ++i)
	{
		if(i % 2 == 1)
		{
			cnt = cnt + 1;
			sum = sum + i;
		}
	}
	avg = 1.0*sum / cnt;
	printf("%d\n", cnt);
	printf("%d\n", sum);
	printf("1到100的奇数之平均数 = %f\n", avg);//记得写为%f

	return 0;
}
