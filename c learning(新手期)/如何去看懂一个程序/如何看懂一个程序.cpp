# include <stdio.h>

int main(void)
{
	int val;
	int m;
	int sum = 0;

	printf ("请输入您需要判断是否为回文数的数字:  ");
	scanf("%d", &val);

	m = val;
	while (m)
	{
		sum = sum * 10 + m%10;
		m /= 10;
	}//要实际花功夫去按顺序写出来,才可以知道为何如此算,其中有一个必知条件:0为否.
	/*

	*/

	if (sum == val)
		printf("yes\n");
	else
		printf("no\n");

	return 0;
}