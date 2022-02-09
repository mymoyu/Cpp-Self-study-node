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

    InputStudent(&st);//对结构体变量输入
    OutputStudent(st);//对结构体变量输出

    return 0;
}

void OutputStudent(struct Student ss)//耗费内存太大, 如果用指针只需要4个字节
{
    printf("%d %c %s\n", ss.age, ss.sex, ss.name);
}

void InputStudent(struct Student * pstu) //pstu只占四个字节
{
    pstu->age = 10;
    strcpy(pstu->name, "张三"); //不能写成 stu.name = "张三";
    (*pstu).sex = 'F';
}

/*
//本函数无法修改主函数第14行
void InputStudent(struct Stdent stu)
{
    stu.age = 10;
    strcpy(stu.name, "张三"); //不能写成 stu.name = "张三";
    stu.sex = 'F';
}
*/
