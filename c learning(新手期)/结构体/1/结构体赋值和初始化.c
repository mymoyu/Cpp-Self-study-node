# include <stdio.h>

struct student
{
    int age;
    float score;
    char sex;
};

int main(void)
{
    struct Student st = {80, 66.6, 'F'};//初始化,整体赋值
    struct Student st2;//定义完就只能单个赋值;
    st2.age = 10;
    st2.score  = 88;
    st2.stx = 'F';
}
