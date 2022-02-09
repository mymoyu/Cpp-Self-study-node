# include<stdio.h>

struct Student
{
    int age;
    float score;
    char c;
};

int main(void)
{
    struct Student st = {80, 66.6, 'F'};
    struct Student * pst = &st;

    pst->age = 88;//第二种方法
    /*
    pst->age 在计算机内部会被转化为(*pst).age
    */
//    st.age = 10;//第一种方法
    st.score = 66.6f;//用f的原因是, 66.6在c中默认是double类型, 故加f or F;
    printf("%d %f\n", st.age, pst->score);

    return 0;
}
