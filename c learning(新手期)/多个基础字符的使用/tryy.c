#include <stdio.h>
int main(void)
{
int n1=13;
int n2=-13;
printf ("int ��������ռ�ֽ���: %d\n",sizeof(int));
	printf ("����23����ռ�ֽ����ֱ�Ϊ: %d��%d\n",sizeof(23),sizeof(45678900000));
	printf ("char ��������ռ�ֽ���: %d\n",sizeof(char));
	printf ("�ַ�\'s\'��ռ�ֽ���: %d\n",sizeof('a'));
	printf ("�ַ���\"s\"��ռ�ֽ���: %d\n",sizeof("a"));
	printf ("�ַ���\"CCTV���������̨\" ��ռ�ֽ���: %d\n\n",sizeof("CCTV���������̨"));
	printf ("%d\t%X\n",n1,n1);
	printf ("%d\t%X\n",n2,n2);
	return 0;
}
