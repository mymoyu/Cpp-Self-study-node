# include <stdio.h>

int main(void)
{
	char ch = 'A';//OK
//	char ch = 'AB';//error because "AB"���ַ��������ǲ��ܰ��ַ������赥���ַ�
//	char ch = "A"; //error  because����˫�ַ�
//	char ch = 'B';//д�˵ڶ������ظ���ֵ
//	ch = 'C';//������A�����¸�ֵ
	printf("%c\n", ch);

	return 0;
}//�ַ�����˫���ţ������ַ��õ����ţ��ַ��������������\0(������)