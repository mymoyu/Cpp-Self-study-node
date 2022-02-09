### shift + K可以直接调用man

#### make加宏

如果想要make的同时写入 可以创建一个makefile文件(来完成加宏)

然后CFLAGS+=-D_FILE_OFFSET_BITS=64, 就可以实现off_t为64bit

而如果需要手动链接则LDFLAGS+=lcrypt, 这个好像多少有点问题, 可能还是得手动gcc

```c
#include <stdio.h>

int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);

//On  some  architectures, both off_t and long are 32-bit types, but defining _FILE_OFFSET_BITS with the value 64 (before including any header files) will turn off_t into a 64-bit type.
```



#### 文件位置指针的操作(fseek(), ftell(), rewind() )

```
文件位置指针其实在输入过程中会不断往后移动, 这就以为着
    
fp = fopen();
fputc(fp) 10次
fgetc(); 

是读不了我输入的内容的, 除非我fclose(), 在fopen()才能使得指针回到文件初始位置

于是我们加上一句fseek(fp, -10, SEEK_CUR);即可回到文件的初始位置
```

故我们需要一个文件位置指针的操作

```C
fp = fopen(argv[1], "r");
if(fp == NULL)
{
    perror("fopen()");
    exit(1);
}

//SEEK_SET文件首, SEEK_END文件尾巴
fseek(fp, 0, SEEK_END);

// ftell show file size, 搭配前面的seek使用
printf("%ld\n", ftell(fp));

```

下载时可以用fseek()这种产生空洞文件, 先占据磁盘, 这个文件里面都是0, 分块写入



标准终端输出内容是得遇到'\n'才会刷新缓冲区

如果我们写出printf("Before"); while(1); printf("After"); 由于我们没有遇到'\n', 所以我们的缓冲区不会刷新, 因此没有输出内容

而当我们写出printf("Before\n"); while(1); printf("After\n");时, 由于遇到'\n'所以刷新了缓冲区, 输出了Before



fflush(FILE *stream) 刷新指定的流, 如果要全部刷新, 那么直接fflush()即可

```c
/*
 *缓冲区的作用: 大多数情况下是好事, 合并系统调用
 *
 *行缓冲: 换行时候刷新, 满了的时候刷新, 强制刷新(标准输出是这样)
 *
 *全缓冲: 满了的时候刷新, 强制刷新(默认, 只要不是终端设备)
 *
 *无缓冲: 如stderr(需要立即输出的内容)
 *setvbuf
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        int i;

        printf("Before while()");
        //fflush(NULL) is OK
        fflush(stdout);

        while(1);

        printf("After while()\n");

        exit(0);
}
```



delimiter character即空格, 回车之类的

判断异常条件时, 写<0之类的, 可以把意外的情况一起囊括



### 所有参数都必须要初始化!!!!!!!!!!!!!!!!!



```C
// getline的使用
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
        FILE *fp;
        // this is NULL, beacuse the point needs to be initialized.
        char *linebuf = NULL;
        // this is zero(very important, but Segmentation fault (core dumped)
        size_t linesize;

        if(argc < 2)
        {
                fprintf(stderr, "Usage: %s <src_file> <>", argv[0]);
                exit(1);
        }

        fp = fopen(argv[1], "r");
        if(fp == NULL)
        {
                perror("fopen()");
                exit(1);
        }

        while(1)
        {
                if(getline(&linebuf, &linesize, fp) < 0)
                {
                        break;
                }
                printf("%ld\n", strlen(linebuf));
                printf("%ld\n", linesize);
        }

        fclose(fp);

        exit(0);
}
```



#### 封装一个getline函数(作业)

```C
ssize_t mygetline(char **lineptr, size_t *n, FILE* stream)
{
        // get a null line
        char *buf = *lineptr;
        // get the str status
        ssize_t stats = 0;
        // the char num
        ssize_t cnum = 0;

        if(buf == NULL || *n <= 60)
        {
            //注意, 这里需要先对父指针malloc, 否则会出现段错误, 推测原因: 原先的指针必须指向一块             //空间, 而后继指针只能进行改动空间
                *lineptr = malloc(60);
                buf = *lineptr;
                *n = 60;
        }

        // read line by line 
        while((stats = fgetc(stream)) != '\n')
        {
                //read the end return -1
                if(stats == EOF)
                {
                        return -1;
                }
                else if(cnum < *n - 2) // leave two spaces
                {
                        //stats is one of them
                        *(buf+cnum++) = stats;
                }
                else
                {
                        *n+=60;
                        buf = realloc(buf, *n);
                        *(buf+cnum++) = stats;
                }
        }
        *(buf+cnum++) = '\n';
        *(buf+cnum) = '\0';
        return cnum;
}

```



#### 临时文件

所需条件:

1. 如何不冲突
2. 及时销毁
