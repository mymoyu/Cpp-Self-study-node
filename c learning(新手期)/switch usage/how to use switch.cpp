# include <stdio.h>

int main(void)
{
	int val;

	printf("��������Ҫ�����¥��:");
	scanf("%d", &val);

	switch (val)
	{
	case 1:
		printf("1չ��!\n");
		break;//��breakȥ��,���ֽ��:   1չ��!   2չ��!
	case 2:
		printf("2չ��!\n");
		break;
	case 3:
		printf("3չ��!\n");
		break;
	default:
		printf("��û�ǵ���һ��\n");
		break;
	}

	return 0;
}
//switch��ѡ��,������ѭ��.