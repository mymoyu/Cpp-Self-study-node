# include <stdio.h>

int main (void)
{
	if (3 > 2)//���ʽ1
		printf("AAAA\n");//���A
	else if (3 > 1)//���ʽ2
		printf("BBBB\n");//���B
	else
		printf("CCCC\n");

	return 0;
}
/*
      ��Vc++6.0�е���������:
------------------------------
AAAA
Press any key to continue
------------------------------
    �ܽ�:
	������ʽ1��2������,Ҳֻ��ִ�����A
*/
