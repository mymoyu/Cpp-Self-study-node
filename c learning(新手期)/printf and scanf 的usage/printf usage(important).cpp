# include <stdio.h>

int main(void)
{
//	printf("haha!\n");// \n��ʾ����(��һ��)

//	int i = 10;

//	printf("%d\n", i);(�ڶ���)

	int j = 3;
	int k = 5;
//	printf("%d %d\n", j, k);//OK
//	printf("%d\n", j, k); //error ������Ʒ�����������ĸ�ʽ��ƥ��
	printf("i = %d, j = %d\n", j, k);/*if "%d%d\n", input:35;
									 if"%d %d/n", input:3 5; those are ugly.   
	                                 "i = %d, j = %d\n" this is right.    */

	return 0;
}
/*printf �����÷�
1. printf("�ַ���\n");
2. printf("������Ʒ�", �������);
3. printf("������Ʒ�1 ������Ʒ�2.....", �������1, �������2, ......);
4. printf("������Ʒ� ��������Ʒ�", �������);
������Ʒ�����:
%d                --  int
%ld               --  long int
%c                --  char
%f                --  float
%lf               --  double
%x(or %X����%#X)  --  int OR long int OR short int
%o                --  ͬ��
%s                --�ַ���
*/
//Ϊ����Ҫ������Ʒ�,����:Ϊ��ָ�������ƴ�����ʲô��ʽ���.