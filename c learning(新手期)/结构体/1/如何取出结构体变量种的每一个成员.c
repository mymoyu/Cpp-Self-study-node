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

    pst->age = 88;//�ڶ��ַ���
    /*
    pst->age �ڼ�����ڲ��ᱻת��Ϊ(*pst).age
    */
//    st.age = 10;//��һ�ַ���
    st.score = 66.6f;//��f��ԭ����, 66.6��c��Ĭ����double����, �ʼ�f or F;
    printf("%d %f\n", st.age, pst->score);

    return 0;
}
