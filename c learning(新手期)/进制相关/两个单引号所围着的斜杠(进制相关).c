# include<stdio.h>

int main(void)
{
    int x;
    float answer;

    x = 8;

    answer = 'a' + x%3 + 5/2 - '\24'; //  '/'��Ӱ˽�������,��ʾASCII����ַ�; '/x'or'/X'���ʮ����������

    printf("%f", answer);

    return 0;
}
/*
������:
81.000000
Process returned 0 (0x0)   execution time : 0.016 s
Press any key to continue.
*/
