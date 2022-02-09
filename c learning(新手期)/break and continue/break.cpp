/*  break
     break如果用于循环是用来终止循环
	 break如果用于switch,则是用于终止switch
	 break不能直接用于if,除非if属于循环内部的一个子句
*/
# include<stdio.h>

int main(void)
{
	int i;

/*
	switch (2)
	{
	case 2:
		printf("HAHA!\n");
		break;
	}//OK!!!!
*/

//	if (3 > 2)
//		break;  //break不能直接用于if,除非if属于循环内部的一个子句
	for (i=0; i<3; ++i )
	{
		if(3 > 2)
			break;//break如果是终止if,那么下面这个语句会输出三次,但如果是终止for则输出0次.
		printf("heihei!!\n");//输出0次,说明终止的是for;
	}

	return 0;
}