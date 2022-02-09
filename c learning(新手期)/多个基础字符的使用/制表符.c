#include <stdio.h>
/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300; floating-point version */
int main(void)
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0; /* lower limit of temperatuire scale */
    upper = 300; /* upper limit */
    step = 20; /* step size */

    fahr = lower;
    while (fahr <= upper) {
            celsius = (5.0/9.0) * (fahr-32.0);
    printf("%3.0f\t%6.1f\n", fahr, celsius);// 其中\t就是我们的制表符,它可以使数字对齐变得更为美观.
    fahr = fahr + step;

    return 0;
}
}
