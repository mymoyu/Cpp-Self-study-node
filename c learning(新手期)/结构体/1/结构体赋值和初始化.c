# include <stdio.h>

struct student
{
    int age;
    float score;
    char sex;
};

int main(void)
{
    struct Student st = {80, 66.6, 'F'};//��ʼ��,���帳ֵ
    struct Student st2;//�������ֻ�ܵ�����ֵ;
    st2.age = 10;
    st2.score  = 88;
    st2.stx = 'F';
}
