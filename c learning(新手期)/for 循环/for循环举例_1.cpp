/*
   求1到10之间所有的奇数之和
*/
# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;

	for (i=1; i<10; i+=2)// i+=2; 等价于 i = i +2;
	{
		sum = sum + 1;//如何去验证循环了几次?
//		printf("循环\n");//验证循环次数所用
		printf("%d\n", sum);
	}
	printf("i = %d\n", i);
	printf("sum = %d\n", sum);

	return 0;
}