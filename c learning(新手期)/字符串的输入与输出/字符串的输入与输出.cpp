/*
  记住[数字], 这里面的数字代表的是数组元素的个数
*/
# include <stdio.h>
int main(void)
{
    char str[10];  //str是string的缩写, 即字符串

    printf("请输入字符串：");
    scanf("%s", str);  /*输入参数是已经定义好的“字符数组名”, 不用加&, 因为在C语言中数组名就代表该数组的起始地址*/

    printf("输出结果：%s\n", str);

    return 0;
}
/*
输出结果:
请输入字符串：不在沉默中爆发就在沉默中灭亡
输出结果：不在沉默中爆发就在沉默中灭亡
Press any key to continue

BUT  你输入的语句有空格,后面的就无法输出.
此时输出结果为:
请输入字符串：不在沉默中爆发 就在沉默中灭亡
输出结果：不在沉默中爆发
Press any key to continue

这种情况可以这样:
# include <stdio.h>
int main(void)
{
    char str1[10], str2[10];

    printf("请输入字符串：");
    scanf("%s %s", str1, str2);

    printf("输出结果：%s %s\n", str1, str2);  //%s间要加空格

    return 0;
}
*/