# include <stdio.h>

/*  ������ɻ�������
void huhuan(int a, int b)
{
    int t;

    t = a;
    a = b;
    b = t;

    return;
}//���������β�a,b ��������������a, b, ��������Ľ����Ȼ����������ֵ,�����ǵ��ú��ֵ
*/

/*   ������ɻ�������
void huhuan (int * p, int * q)
{
    int * t;//���Ҫ����p��q��ֵ, ��t������int *, ������int, ��������

    t = p;
    p = q;
    q = t;
}//��������Ȼ��a = 3, b = 5, û��Ӱ��ʵ�ε�ֵ
*/

void huhuan (int * p, int * q)//pָ��a qָ��b, ����*p����a��ֵ, *q����b��ֵ
{
    int t;

    t = *p; //p�� int*, *p��int
    *p = *q;
    *q = t;
}

int main(void)
{
    int a = 3;
    int b = 5;

    huhuan(&a, &b);//(*p, *q)�Ǵ����, (a, b)Ҳ�Ǵ����.
    printf("a = %d, b = %d\n", a, b);

    return 0;
}
