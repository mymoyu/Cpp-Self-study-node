# include <stdio.h>

//max�Ǻ���������, i��j����ʽ����(�����еı���), ����β�, void��ʾ����û�з���ֵ
void max1(int i, int j)// �˴���max���㶨��ĺ���,���Բ�дmaxд��min֮�඼����
{
    if (i > j)
        printf("%d\n", i);
    else
        printf("%d\n", j);
}

int max2(int i, int j)
{
    if (i > j)
        return i;
    else
        return j;
}

/*
�������û�ж����������ͱ���,����ᱨ��
*/

int main(void)//mainҲ�Ǻ���������, ������������ִ��
{
    int a, b, c, d, e, f;

    a = 1;
    b = 2;
    c = 3;
    d = 9;
    e = -5;
    f = 100;

	printf("%d\n", max2(a, b));
    printf("%d\n", max2(c, d));
    printf("%d\n", max2(e, f));

//  max1(a, b);//max�Ǻ�����,a�ᷢ�͸�i, b�ᷢ�͸�j,Ȼ����������max������ִ��.
//  max1(c, d);//����д�����������,����������Ϊ��һ��������һ����Ϊmax�ĺ���
//  max1(e, f);//�����ʵ��û�ж���max�������,����ͻᱨ��.

/*
    if (a > b)
        printf("%d\n", a);
    else
        printf("%d\n", b);

    if (c > d)
        printf("%d\n", c);
    else
        printf("%d\n", d);

    if (e > f)
        printf("%d\n", e);
    else
        printf("%d\n", f);
*///ԭʼ����̫����

    return 0;
}
/*
  Ϊʲô��Ҫ����?
       �������ظ��Բ���
       �����ڳ����ģ�黯
  c���ԵĻ�����λ�Ǻ���
*/
