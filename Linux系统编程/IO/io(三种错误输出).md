#### 常用工具:

diff比较两个文件是否相同, 相同则不输出内容

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	FILE *fp;

	// tmp fire isn't in this fire now
	fp = fopen("tmp", "r");

	if(fp == NULL)
	{
		//fprintf(stderr, "fopen() failed! errno = %d\n", errno);
		//fopen() failed! errno = 2
        
        //推荐使用
		//perror("fopen()");
		//show detailed error
        
        //推荐使用
        //头文件 #include <string.h>
		fprintf(stderr, "fopen():%s\n", strerror(errno));
		exit(1);
	}

	puts("OK!");

	exit(0);
}
```

一个界面中默认打开三个流stdin, stdout, stderr(默认输入, 默认输出, 默认错误重定向)



文件是默认在结尾处有一个\n的

假设一个文件里有abcd

则实际内容为

1-> a b c d

2-> '\n''\0'



```c
//**********************************
//该文件是fgetc.c文件, 目的是获取文件大小
//**********************************
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *fp;
	int count = 0;

	if(argc < 2)
	{
		fprintf(stderr, "Usage:%s <src_file> <dest_file>\n", argv[0]);
		exit(1);
	}

	fopen(argv[1], "r");

	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

    //读取count个字符
	while(fgetc(fp) != EOF)
	{
		count++;
	}

	printf("count = %d\n", count);

	fclose(fp);

	exit(0);
}
```



```C
//**********************************
//该文件是mycp.c文件, 目的是复制文件
//**********************************

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *fps, *fpd;
	int ch;

	if(argc < 3)
	{
		fprintf(stderr, "Usage:%s <src_file> <dest_file>\n", argv[0]);
		exit(1);
	}

    //在获取的第一个文件流中打开读取口
	fps = fopen(argv[1], "r");
	if(fps == NULL)
	{
		perror("fopen()");
		exit(1);
	}

    //在获取的第二个文件流中打开写入口
	fpd = fopen(argv[2], "w");
	if(fpd == NULL)
	{
        //如果打开失败则将第一个流关闭
		fclose(fps);
		perror("fopen()");
		exit(1);
	}

	while(1)
	{
		ch = fgetc(fps);
		if(ch == EOF)
		{
			break;
		}
		fputc(ch, fpd);
	}

	//first, must close writer 
	fclose(fpd);
	fclose(fps);

	exit(0);
}
```



#### fread 和 fwrite

fread 和 fwrite的缺点就是它是整个拷贝, 而不判断边界, 如果无需拷贝的, 也会被其拷贝进去, 极易崩溃

例子: 数据量足够时,正常拷贝, fread(buf, 1, 10, fp);   10次 -> 1字节的读 读到10次即10字节读完

数据量不足够时, 假设是5个字节, fread(buf, 10, 1, fp); 1 -> 10字节的读, 后面是空的也会照常读入即读入0

```C
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

```

```C
//************************
//错误的写法, 直接读然后直接写, 会将不足的地方用0补齐
//************************
while(fread(buf, 1, BUFSIZE, fps))
{
    fwrite(buf, 1, BUFSIZE, fpd);
}


//************************
//正确的写法, 每次读的时候获取实际可读多少个字节, 然后只读该数量的字节
//************************
while((n = fread(buf, 1, BUFSIZE, fps)) > 0)
{
    fwrite(buf, 1, n, fpd);
}
```

```shell
利用fread直接读取然后写入, 由于剩余的文件可能不足BUFSIZE的大小, 故出现了这种多余读入的情况
以下是错误情况
mymoyu@ubuntu:~/learn/io/stdio$ ./mycpy_fread /etc/services /tmp/out 
mymoyu@ubuntu:~/learn/io/stdio$ diff /etc/services /tmp/out 
591a592,599
> ndelspawn	9359/udp	mandelbrot	# network mandelbrot
> git		9418/tcp			# Git Version Control System
> zope		9673/tcp			# zope server
> webmin		10000/tcp
> kamanda		10081/tcp			# amanda backup services (Kerberos)
> kamanda		10081/udp
> amandaidx	10082/tcp			# amanda backup services
> amidx
\ No newline at end of file
```

