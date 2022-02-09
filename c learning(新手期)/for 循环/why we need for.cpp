# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;

	for (i = 1; i <= 10; ++i)
		sum = sum + i;
	printf("sum = %d\n", sum);

	return 0;
}
//优先执行i = 1,然后执行i <= 10的判断,如果成立,标志这循环成立,
//然后执行sum = sum + i,当++i执行完,标志该次循环结束
//++i就是指i=1