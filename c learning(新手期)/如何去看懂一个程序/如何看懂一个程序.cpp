# include <stdio.h>

int main(void)
{
	int val;
	int m;
	int sum = 0;

	printf ("����������Ҫ�ж��Ƿ�Ϊ������������:  ");
	scanf("%d", &val);

	m = val;
	while (m)
	{
		sum = sum * 10 + m%10;
		m /= 10;
	}//Ҫʵ�ʻ�����ȥ��˳��д����,�ſ���֪��Ϊ�������,������һ����֪����:0Ϊ��.
	/*

	*/

	if (sum == val)
		printf("yes\n");
	else
		printf("no\n");

	return 0;
}