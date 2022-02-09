# include <stdio.h>

int main(void)
{
	float i;//错误了, because循环中更新的变量不能定义为浮点型
	float sum = 0;

	for (i = 1; i <= 100; ++i)
	{
		sum = sum + 1/i;
	}
	printf("sum = %f\n", sum);//float 必须用%f输出

	return 0;
}
//float 和 double 都不能保证可以精确的存储一个小数
/*
   题目: 有一个浮点型变量x, 如何判断x的值是否是零
   若 if(0 == x)
         是
	  else
	     不是 //这种写法是错误的,因为浮点数是有可能包含零的.

	可以这样写:
	   if (|x - 0.000001| < 0.000001)
	      是零
	   else
	      不是零


  为什么循环中更新的变量不能定义为浮点型
  理由:  因为浮点型不能准确存储
*/
