/*
  c = getchar()   字符的输入

  putchar()       字符的输出.
*/
#include <stdio.h>

/* copy input to output; 1st version */
int main(void)
{
    int c;

    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }

    return 0;
}
// !=为不等于号.
