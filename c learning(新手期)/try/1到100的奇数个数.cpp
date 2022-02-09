# include <stdio.h>

int main(void)
{
	int i;
	int cnt = 0;
	
	for(i = 1; i <= 100; ++i)
	{
		if(i % 2 == 1)
			++cnt;
	}
	printf("quantity = %d\n", cnt);

	return 0;
}
//个数一般用cnt表示.