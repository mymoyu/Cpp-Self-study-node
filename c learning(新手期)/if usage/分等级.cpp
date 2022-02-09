# include <stdio.h>

int main(void)
{
	float score;

	printf("请输入您的单科考试成绩(100分制): ");
	scanf ("%f", &score);

	if (score > 100)
		printf("这是做梦!\n");
	else if (score >= 90 && score <= 100 )
	/*<=是逻辑值,判断结果是真或假,按顺序来说,优先执行90 <= score输出"1 or 0",
		              所以90 <= score <= 100不能执行该代码,结果无论如何都是真. */
		printf("优秀!\n");
	else if (score >= 80 && score < 90)
		printf("良好!\n");
	else if (score >= 60 && score < 80)
		printf("及格!\n");
	else if(score > 10 && score < 60)
		printf("不合格!\n");
/*	else
		printf("重考吧!笨蛋\n");
*///可以去掉也可以保留
	return 0;
}