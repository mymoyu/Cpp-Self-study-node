# include <stdio.h>

int main(void)
{
	int i, j, k;

	printf("请输入三个数值, 中间以逗号分隔开:");//为输入者提供讯息
	scanf("%d, %d, %d", &i, &j, &k);
	printf("i = %d, j = %d, k = %d\n", i, j, k);

	return 0;
}
//如果输入1 2 3    只有第一个有效,第二第三个全错[","是非输出控制符,需要原样输入]
//如果输入1,2,3    输出i = 1, j = 2, k = 3
/*
   如何使用scanf编写出高质量代码
       1. 使用scanf之前最好使用printf提示用户以什么样的形式输入
	   2. scanf中尽量不要使用非输入控制符,尤其是不要用\n
	   3. 
*/