/*
链表
优点: 插入删除元素效率高, 不需要一个连续的很大的内存
缺点: 查找某个位置的元素效率低.

尾节点: 存放最后一个有效数据的节点.
首节点:存放第一个有效数据的节点
确定一个链表需要一个参数, 即头指针.
*/
#include <stdio.h>

struct Node
{
    int data;//存储链表的数据.头节点, 即其数据类型与首节点一致, 头结点是首节点前面的那个节点, 不存放有效数据, 设置头结点的母的是为了方便对链表的操作
    struct Node * pNext;//存储地址.头指针, 即存放头结点地址的指针变量
};

int main(void)
{
    struct Node * pHead; //pHead用来存放链表表头结点的地址

    pHead = CreateList();
    TraverseList(pHead);

    return 0;
}
