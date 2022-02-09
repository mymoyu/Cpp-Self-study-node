# include <stdio.h>

int main(void)
{
	int i = 5;
	int j = 6;
	int t;

	t = i;
	i = j;
	j = t;

	printf("i = %d, j = %d\n", i, j);

	return 0;
}