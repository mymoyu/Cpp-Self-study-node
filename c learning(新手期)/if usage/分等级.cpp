# include <stdio.h>

int main(void)
{
	float score;

	printf("���������ĵ��ƿ��Գɼ�(100����): ");
	scanf ("%f", &score);

	if (score > 100)
		printf("��������!\n");
	else if (score >= 90 && score <= 100 )
	/*<=���߼�ֵ,�жϽ��������,��˳����˵,����ִ��90 <= score���"1 or 0",
		              ����90 <= score <= 100����ִ�иô���,���������ζ�����. */
		printf("����!\n");
	else if (score >= 80 && score < 90)
		printf("����!\n");
	else if (score >= 60 && score < 80)
		printf("����!\n");
	else if(score > 10 && score < 60)
		printf("���ϸ�!\n");
/*	else
		printf("�ؿ���!����\n");
*///����ȥ��Ҳ���Ա���
	return 0;
}