# include <stdio.h>

int main(void)
{
    char ch = 'A';
    int i = 99;
    double x = 66.6;
    char * p = &ch;
    int * q = &i;
    double * r = &x;

    printf("%d %d %d", sizeof(p), sizeof(q), sizeof(r));

    return 0;
}
/*
�ܽ�:
     һ��ָ�����, ������ָ��ı���ռ�����ֽ�, ��ָ��ֻռ�ĸ��ֽ�

     һ�������ĵ�ַʹ�øñ������ֽڵĵ�ַ����ʾ
*/
