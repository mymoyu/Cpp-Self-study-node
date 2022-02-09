# include <stdio.h>

int main(void)
{
//	float i;//这儿也不能用int,用int会输出i=1;
	int i;
	float sum = 0;

	for (i = 1; i <= 100; ++i)
	{
		sum = sum + 1.0 / i; //图中为推荐写法,或者在此处加上float, 但(float)(1/i)这样写是错误的,但可以写为1 / (float)(i),这叫做强制类型转化
	}
	printf("sum = %f\n", sum);

	return 0;
}
/*
    1/i会出现小数,所以应该用double和float.
*/