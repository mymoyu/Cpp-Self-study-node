#include <stdio.h>
int main(void)
{
int n1=13;
int n2=-13;
printf ("int 型数据所占字节数: %d\n",sizeof(int));
	printf ("整数23、所占字节数分别为: %d、%d\n",sizeof(23),sizeof(45678900000));
	printf ("char 型数据所占字节数: %d\n",sizeof(char));
	printf ("字符\'s\'所占字节数: %d\n",sizeof('a'));
	printf ("字符串\"s\"所占字节数: %d\n",sizeof("a"));
	printf ("字符串\"CCTV即中央电视台\" 所占字节数: %d\n\n",sizeof("CCTV即中央电视台"));
	printf ("%d\t%X\n",n1,n1);
	printf ("%d\t%X\n",n2,n2);
	return 0;
}
