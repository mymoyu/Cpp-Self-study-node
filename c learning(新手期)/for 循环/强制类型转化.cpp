# include <stdio.h>

int main(void)
{
//	float i;//���Ҳ������int,��int�����i=1;
	int i;
	float sum = 0;

	for (i = 1; i <= 100; ++i)
	{
		sum = sum + 1.0 / i; //ͼ��Ϊ�Ƽ�д��,�����ڴ˴�����float, ��(float)(1/i)����д�Ǵ����,������дΪ1 / (float)(i),�����ǿ������ת��
	}
	printf("sum = %f\n", sum);

	return 0;
}
/*
    1/i�����С��,����Ӧ����double��float.
*/