# include <stdio.h>
# include <stdlib.h>
# include <time.h>
int main()
{
    int a, b;

    srand(time(0)); //��������, ��ѡ�õ�������ʱ����ȷ��,  time(0)ָ��ǰ��ʱ��
    a = rand() % 100; //rand()�����������%100������ȡֵ����һ������
    b = rand() % 101 + 100; //�����ֵ��100 - 500֮�� [a, b]������(b-a+1)+a

    printf("a = %d\n", a);
    printf("b = %d", b);

    return 0;
}
