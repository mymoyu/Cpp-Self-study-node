# include <stdio.h>

int main (void)
{
	double delta = -1;

	if (delta > 0)
		printf("������\n");
//	    printf("hh\n");//Ӧ��ȥ��
	else if (delta == 0)
		printf("��һ��Ψһ��!\n");
	else
		printf("�޽�\n");

	return 0;
}
//����ʧ��:û����else if��ͷ���������,����illegal,
//���߽���Ϊ:û��ƥ��if���.
//else ifΪ˳���Ե�.