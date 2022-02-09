# include <stdio.h>

int main(void)
{
	int i;
	int Qsum = 0;//奇数之和
	int Osum = 0;//偶数之和

	for(i = 1;i <= 100; ++i)
	{
		if(i % 2 == 0)
			Osum = Osum + i; //求偶数之和
		else if(i % 2 == 1)
			Qsum = Qsum + i;//求奇数之和

	}
	printf("偶数之和为%d\n", Osum);
	printf("奇数之和为%d\n", Qsum);

	return 0;
}