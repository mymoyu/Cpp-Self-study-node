# include <stdio.h>

int main(void)
{
    int * p; //p是变量的名字, int * 表示p变量存放的是int类型变量的地址
             //int * p; 不表示定义了一个名字叫*p的变量
             //int * p;应该这样理解: p是变量名, p变量的数据类型是 int *类型
             //        所谓int * 类型 实际就是存放int变量地址的类型
             // 因为是int*, 故只能p = &整型变量的值
    int i = 3;
    int j;

    p = &i; //&i叫i的地址(或叫指针), p存放i的地址, p指向i
        /*
           1. p保持了i的地址, 因此p指向i
           2. p不是i, i也不是p, 更准确的说: 修改p的值不影响i的值, 修改i的值也不会影响p的值
           3. 如果一个指针变量指向了某个普通变量, 则
               *指针变量  就完全等同于 普通变量
           例子:
                如果p是个指针变量, 并且p存放了普通变量i的地址
                则p指向了普通变量
                *p 就完全等同于
                或者说: 在所有出现 *p 的地方都可以替换成i
                        在所有出现 i 的地方都可以替换成*p

            *p 就是以p的内容(i的地址)为地址的变量
        */
        //p 指向i  *p就会获取i的值  而p 获取i的地址
    j = *p; //等价于 j = i;
    printf("i = %d, j = %d\n", i, j);

    return 0;
}
/*
    地址
	    内存单元的编号
		从零开始的非负整数
		范围: 4G [0 -- 4G - 1]

    指针就是地址, 地址就是指针
    地址就是内存单元的编号
    指针是存在地址的变量
    指针和指针变量是两个不同的概念
    但是要注意: 通常我们叙述时会把指针变量简称为指针, 实际它们含义并不一样
	指针的本质就是一个操作受限的非负整数, 只可以相减
*/
