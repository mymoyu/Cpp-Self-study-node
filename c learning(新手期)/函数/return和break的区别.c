# include<stdio.h>

void f(void)//�޲κ���
{
    int i;

    for(i=0; i<5; ++i)
    {
        printf("���������!\n");
        return;//break��ֹforѭ��
               //return���ʽ�ĺ���: 1.��ֹ��������,�������������ر��ʽ��ֵ
    }          //������ʽΪ��, ��ֻ��ֹ����, �����������������κ�ֵ
    printf("ͬ־�Ǻ�!\n");
}

int main(void)
{
    f();

    return 0;
}
/*
void f()
{
    return;  //returnֻ������ֹ����, �����������������κ�ֵ
}

int f()
{
    return 10;  //��һ :��ֹ����, �ڶ�: ��������������10
}
*/
