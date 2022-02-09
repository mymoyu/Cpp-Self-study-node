#include <stdio.h>

#define LOWER 0 /* lower limit of table */
#define UPPER 300 /* upper limit */
#define STEP 20 /* step size */
/* print Fahrenheit-Celsius table */
int main(void)
{
    int fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));

    return 0;
}
/*
  其中这个#define的使用是
  #define 名字 替换文本
  名字与普通变量名的形式相同,它们都是以字符大头的字母和数字序列
  替换文本则可以是任何字符序列,而不仅限于数字.
*/
