/*
   ��1��10֮�����е�����֮��
*/
# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;

	for (i=1; i<10; i+=2)// i+=2; �ȼ��� i = i +2;
	{
		sum = sum + 1;//���ȥ��֤ѭ���˼���?
//		printf("ѭ��\n");//��֤ѭ����������
		printf("%d\n", sum);
	}
	printf("i = %d\n", i);
	printf("sum = %d\n", sum);

	return 0;
}