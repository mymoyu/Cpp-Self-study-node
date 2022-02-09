# include <stdio.h>

int main(void)
{
	int val;

	printf("请输入您要进入的楼层:");
	scanf("%d", &val);

	switch (val)
	{
	case 1:
		printf("1展开!\n");
		break;//把break去掉,出现结果:   1展开!   2展开!
	case 2:
		printf("2展开!\n");
		break;
	case 3:
		printf("3展开!\n");
		break;
	default:
		printf("还没盖到这一层\n");
		break;
	}

	return 0;
}
//switch是选择,而不是循环.