# include<stdio.h>

int main(void)
{
    int a[5] = {1, 2, 3, 4, 5};
        //a�����������, 5��ʾ����Ԫ�صĸ���,���������Ԫ�طֱ���a[0], a[1],.... a[4].���Ԫ��ֻ�ܵ�a[4]
        //a[0]��ʾ��һ��Ԫ�� a[1]��ʾ�ڶ���Ԫ��
    int i;

    for (i=0; i<5; ++i)
        printf("%d\n", a[i]);
    /*
    ������:
    1
    2
    3
    4
    5

    Process returned 0 (0x0)   execution time : 0.012 s
    Press any key to continue.
    */

    printf("%d\n", a[100]);

    return 0;
}
/*
����,Ϊ�˽������ͬ�������ݵĴ洢��ʹ������
Ϊ��ģ����ʵ�¼�
*/
