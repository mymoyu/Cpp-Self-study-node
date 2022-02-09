# include <stdio.h>

int main(void)

{
	int x= 47;//100是十进制

	printf("%x\n", x);//输出: 2f
	printf("%X\n", x);//输出: 2F
	printf("%#x\n", x);//输出: 0x2f
	printf("%#X\n", x);//输出: 0X2F 推荐使用
	
	return 0;
}
/* 在vc++的输出结果是:
------------------------
*/