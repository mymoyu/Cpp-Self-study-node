# include<stdio.h>
# include<math.h>

int main(void)
{
	printf("������a,b,c  ���ÿո����η���\n");

//	int a;
//	int b;
//	int c;    //����д��,������
	int a, b, c;

	double delta;
	double x1;
	double x2;

//	scanf("%d", &a);
//	scanf("%d", &b);
//	scanf("%d", &c);    //�����д��   ��ѵ:һ�θ�����������̸�ֵ�Ŀγ��ؿ�
	scanf("%d %d %d", &a, &b, &c);

	delta = b*b - 4*a*c;

	if(delta > 0)
	{
		x1 = (-b + sqrt(delta)) / (2*a);
		x2 = (-b - sqrt(delta)) / (2*a);
		printf("��һԪ���η�����������, x1 = %f, x2 = %f\n", x1, x2);
	}
	else if(delta == 0)
	{
		x1 = (-b) / (2*a);
		x2 = x1;
		printf("��һԪ���η�����һ��Ψһ��, x1 = x2 = %f\n", x1);
	}
	else
	{
		printf("�޽�\n");
	}
	
	return 0;
}