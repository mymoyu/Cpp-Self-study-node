# include <stdio.h>

bool IsPrime(int val)//������Ӣ����,ֻ�ж�һ�������Ƿ�Ϊ����,��ֻдһ���β�
{
    int i;

    for (i=2; i<val; ++i)
    {
        if(val%i == 0)
            break;
    }
    if (i == val)
        return true;
    else
        return false;//һ��ʹ��return ����ľͲ���ִ����
}//һ��һ������дһ������,д��true��false��Ϊ���ñ����Լ�ȥ���,�ʲ�Ӧ����printf

int main(void)
{
    int m;//������valҲ�ǿ��Ե�

    scanf("%d", &m);
    if ( IsPrime(m) )
        printf("Yes!\n");
    else
        printf("No!\n");

    return 0;
}
