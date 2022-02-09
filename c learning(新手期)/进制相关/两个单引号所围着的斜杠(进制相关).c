# include<stdio.h>

int main(void)
{
    int x;
    float answer;

    x = 8;

    answer = 'a' + x%3 + 5/2 - '\24'; //  '/'后接八进制数字,表示ASCII码的字符; '/x'or'/X'后接十六进制数字

    printf("%f", answer);

    return 0;
}
/*
输出结果:
81.000000
Process returned 0 (0x0)   execution time : 0.016 s
Press any key to continue.
*/
