/*  break
     break�������ѭ����������ֹѭ��
	 break�������switch,����������ֹswitch
	 break����ֱ������if,����if����ѭ���ڲ���һ���Ӿ�
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
//		break;  //break����ֱ������if,����if����ѭ���ڲ���һ���Ӿ�
	for (i=0; i<3; ++i )
	{
		if(3 > 2)
			break;//break�������ֹif,��ô������������������,���������ֹfor�����0��.
		printf("heihei!!\n");//���0��,˵����ֹ����for;
	}

	return 0;
}