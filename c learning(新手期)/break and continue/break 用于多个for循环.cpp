# include <stdio.h>

int main(void)
{
	int i, j;

	for (i=0; i<3; ++i)
	{
		for (j=1; j<4; ++j)
			break;
		printf("不在沉默中爆发,就在沉默中灭亡!\n");
		//break只能终止距离他最近的循环
	}

	return 0;
}