# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;

	for (i = 1; i <= 10; ++i)
		sum = sum + i;
	printf("sum = %d\n", sum);

	return 0;
}
//����ִ��i = 1,Ȼ��ִ��i <= 10���ж�,�������,��־��ѭ������,
//Ȼ��ִ��sum = sum + i,��++iִ����,��־�ô�ѭ������
//++i����ָi=1