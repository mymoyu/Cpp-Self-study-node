# include<stdio.h>

int main(void)
{
    int r = 0;
    int a[22] = {1, 2, 3, 0};

    for(int i = 3; i < 20; i++)
    {
        a[i] = a[i-1] + a[i-2]+ a[i-3];
    }

    for(int i = 19; i >= 0; i--)
    {
        printf("%6d \t", a[i]);//加上%后的6,即六位输出
        r++;
        if(r % 5 == 0)
            printf("\n");
    }

    return 0;
}