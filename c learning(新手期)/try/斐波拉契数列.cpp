# include <stdio.h>

/*
long f(long int n)
{
	if(0 == n)
		return 0L;
	else if (1L == n || 2L == n)
		return 1L;
	else
		return ( f(n - 1) + f(n - 2));

}
*/
int main(void)
{
	int n;
	int f1, f2, f3;
	int i;

	f1 = 1;
	f2 = 2;

	printf("请输入你想要的序列: ");
	scanf("%d", &n);

	if(n == 1)
	{
		f3 = 1;
	}
	else if(n == 2)
	{
		f3 = 2;
	}
	else
	{
		for(i = 3; i <= n; ++i)
//		for (f3 = 0;n > 2; n =n - 1)
		{
			 f3 = f1 + f2;
			 f1 = f2;
			 f2 = f3;
		}
	}
	printf("%d\n", f3);

	return 0;
}
