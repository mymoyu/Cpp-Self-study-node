# include <stdio.h>

int k = 1000;//ȫ�ֱ���, Ҫ���ڸú���֮ǰ�ſ���ʹ��

void g()
{
    printf("k = %d\n", k);
}

void f(void)
{
    g();
    printf("k = %d\n", k);
}
/*
void f(int i)
{
    int j = 20;//�ֲ�����
    g();
    printf("k = %d\n", k);
}
*/

int main(void)
{
//    int i = 10;

    f();

    return 0;
}
