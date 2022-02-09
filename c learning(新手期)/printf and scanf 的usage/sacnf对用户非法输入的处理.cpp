# include<stdio.h>

int main(void)
{
	int i;
	char ch;//程序不中止的原因1

	scanf("%d", &i);//输入123m 输出123,且程序不中止
	printf("i = %d\n", i);

	//..........
	while ( (ch=getchar()) !='\n')// getchar()要求用户键盘输入一个字符,若用户输入的不是换行符(回车)就继续循环.
	   continue;//程序不中止的原因2//continue的意思为:继续
	int j;
	scanf("%d", &j);//输入123m 且输出123后再输入89,输出89
	printf("j = %d\n", j);

	return 0;
}
/*
  如何使用scanf编写出高质量代码
  3.应该编写代码对用户的非法输入做适当的处理
*/