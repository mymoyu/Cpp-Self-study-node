# include<stdio.h>
# include<string.h>

struct Student
{
    int age;
    char sex;
    char name[100];
};

void InputStudent(struct Student *pstu);
void OutputStudent(struct Student ss);

int main(void)
{
    struct Student st;

    InputStudent(&st);//�Խṹ���������
    OutputStudent(st);//�Խṹ��������

    return 0;
}

void OutputStudent(struct Student ss)//�ķ��ڴ�̫��, �����ָ��ֻ��Ҫ4���ֽ�
{
    printf("%d %c %s\n", ss.age, ss.sex, ss.name);
}

void InputStudent(struct Student * pstu) //pstuֻռ�ĸ��ֽ�
{
    pstu->age = 10;
    strcpy(pstu->name, "����"); //����д�� stu.name = "����";
    (*pstu).sex = 'F';
}

/*
//�������޷��޸���������14��
void InputStudent(struct Stdent stu)
{
    stu.age = 10;
    strcpy(stu.name, "����"); //����д�� stu.name = "����";
    stu.sex = 'F';
}
*/
