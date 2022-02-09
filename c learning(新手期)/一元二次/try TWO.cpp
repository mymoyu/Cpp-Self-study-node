# include<stdio.h>
# include<math.h>

int main(void)
{
	printf("请输入a,b,c  并用空格依次放入\n");

//	int a;
//	int b;
//	int c;    //错误写法,不简练
	int a, b, c;

	double delta;
	double x1;
	double x2;

//	scanf("%d", &a);
//	scanf("%d", &b);
//	scanf("%d", &c);    //错误的写法   教训:一次给多个变量键盘赋值的课程重看
	scanf("%d %d %d", &a, &b, &c);

	delta = b*b - 4*a*c;

	if(delta > 0)
	{
		x1 = (-b + sqrt(delta)) / (2*a);
		x2 = (-b - sqrt(delta)) / (2*a);
		printf("该一元二次方程有两个解, x1 = %f, x2 = %f\n", x1, x2);
	}
	else if(delta == 0)
	{
		x1 = (-b) / (2*a);
		x2 = x1;
		printf("该一元二次方程有一个唯一解, x1 = x2 = %f\n", x1);
	}
	else
	{
		printf("无解\n");
	}
	
	return 0;
}