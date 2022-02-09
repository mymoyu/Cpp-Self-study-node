#include <stdio.h>
int main(void)
{
    int r;
    double C;
    double S;
    double PI = 3.141592;//PI即派.
//  #define PI 3.1415926


    printf("请输入你想要的圆的半径:\n");
    printf("r = ");
    scanf("%d", &r);

    C = 2 * PI * r;
    S = PI * r * r;

    printf("该圆的周长为C = %f\n", C);
    printf("该圆的面积为S = %f\n", S);

	return 0;
}
