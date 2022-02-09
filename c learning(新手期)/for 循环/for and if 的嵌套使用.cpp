# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;

/*	for (i=1; i<4; ++i)
	{	printf("AAAA\n");
	    printf("BBBB\n");
	}
Êä³ö½á¹û:	   
AAAA
BBBB
AAAA
BBBB
AAAA
BBBB
Press any key to continue
*/	
	for(i= 3; i <= 10; ++i)
	{
		if(i % 3 == 0)
			sum = sum + i;
		printf("sum = %d\n", sum);
	}


	return 0;
}
