# include <stdio.h>

int main (void)
{
	if (3 > 2)//表达式1
		printf("AAAA\n");//语句A
	else if (3 > 1)//表达式2
		printf("BBBB\n");//语句B
	else
		printf("CCCC\n");

	return 0;
}
/*
      在Vc++6.0中的输出结果是:
------------------------------
AAAA
Press any key to continue
------------------------------
    总结:
	即便表达式1和2都成立,也只能执行语句A
*/
