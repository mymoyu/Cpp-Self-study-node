# include <stdio.h>

int main(void)
{
//	printf("haha!\n");// \n表示换行(第一类)

//	int i = 10;

//	printf("%d\n", i);(第二类)

	int j = 3;
	int k = 5;
//	printf("%d %d\n", j, k);//OK
//	printf("%d\n", j, k); //error 输出控制符与输出参数的格式不匹配
	printf("i = %d, j = %d\n", j, k);/*if "%d%d\n", input:35;
									 if"%d %d/n", input:3 5; those are ugly.   
	                                 "i = %d, j = %d\n" this is right.    */

	return 0;
}
/*printf 四种用法
1. printf("字符串\n");
2. printf("输出控制符", 输出参数);
3. printf("输出控制符1 输出控制符2.....", 输出参数1, 输出参数2, ......);
4. printf("输出控制符 非输出控制符", 输出参数);
输出控制符包含:
%d                --  int
%ld               --  long int
%c                --  char
%f                --  float
%lf               --  double
%x(or %X或者%#X)  --  int OR long int OR short int
%o                --  同上
%s                --字符串
*/
//为何需要输出控制符,理由:为了指定二进制代码以什么格式输出.