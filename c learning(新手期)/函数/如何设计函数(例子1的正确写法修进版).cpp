/*
   ������������ʵ����1��ĳ������֮��(����������)���е�����, ���������
   ������ ��ǰ����Ǹ����, ����������, �������Ը���

   һ�������Ĺ��ܾ�������,��һ, �������ԲŻ�Ƚϸ�
   ��ѧϰ, ��ģ��ţ�˵Ĵ���
*/
# include <stdio.h>

bool IsPrime(int m);

//�������Ĺ����ǰ�1��n֮�����е���������ʾ�������
void TraverseVal(int n)
{
    int i;

    for (i=2; i<=n; ++i)
    {
        if ( IsPrime (i) )
            printf("%d\n", i);
    }
}

//�������Ĺ�����: �ж�m�Ƿ�������, �Ƿ���true, ���Ƿ���false
bool IsPrime(int m)
{
    int i;

    for (i=2; i<m; ++i)
    {
        if (0 == m%i)
            break;
    }
    if(i == m)
        return true;
    else
        return false;
}

int main(void)
{
    int val;

    scanf("%d", &val);
    TraverseVal(val);

    return 0;
}
