# include <stdio.h>

int main(void)
{
	int i;
	int Qsum = 0;//����֮��
	int Osum = 0;//ż��֮��

	for(i = 1;i <= 100; ++i)
	{
		if(i % 2 == 0)
			Osum = Osum + i; //��ż��֮��
		else if(i % 2 == 1)
			Qsum = Qsum + i;//������֮��

	}
	printf("ż��֮��Ϊ%d\n", Osum);
	printf("����֮��Ϊ%d\n", Qsum);

	return 0;
}