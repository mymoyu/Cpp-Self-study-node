# include <stdio.h>

int main(void)
{
	char ch = 'A';//OK
//	char ch = 'AB';//error because "AB"是字符串，我们不能把字符串赋予单个字符
//	char ch = "A"; //error  because用了双字符
//	char ch = 'B';//写了第二个，重复赋值
//	ch = 'C';//代替了A，重新赋值
	printf("%c\n", ch);

	return 0;
}//字符串用双引号，单个字符用单引号，字符串在最后面会加上\0(结束符)