#include <stdio.h>
int main(void)
{
    int r;
    double C;
    double S;
    double PI = 3.141592;//PI����.
//  #define PI 3.1415926


    printf("����������Ҫ��Բ�İ뾶:\n");
    printf("r = ");
    scanf("%d", &r);

    C = 2 * PI * r;
    S = PI * r * r;

    printf("��Բ���ܳ�ΪC = %f\n", C);
    printf("��Բ�����ΪS = %f\n", S);

	return 0;
}
