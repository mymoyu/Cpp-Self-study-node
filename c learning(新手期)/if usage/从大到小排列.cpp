# include <stdio.h>

int main(void)
{
	int a, b, c;
	int t;//��ʱ����

	printf("��������������(�м��Կո�ָ�): ");
	scanf("%d %d %d", &a, &b, &c);

	//��д�������a�����ֵ b���м�ֵ c ����Сֵ,��������,��ʱ�õ���˼�������ֻ���
/*
	if (a > b && a > c)
		printf("���ֵΪa = %d\n", a);
	else if (b > a && b > c)
		printf("���ֵΪb = %d\n", b);
	else
		printf("���ֵΪc = %d\n", c);
*/
	if (a < b)
	{
		t = a;
		a = b;
		b = t;
	}

	if (a < c)
	{
		t = a;
		a = c;
		c = t;
	}
	if (b < c)
	{
		t = b;
		b = c;
		c = t;

	}
	printf("%d %d %d\n", a, b, c);

	return 0;
}
