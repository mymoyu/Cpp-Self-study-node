#### 程序三大原则:  不得内存泄漏, 不要写越界, 要当作小模块一样写

### ulimit -a   查看系统各类资源数目

文件描述符(简写为fd)是在文件IO中贯穿始终的类型

##### 文件描述符的概念--实质是一个整型数, 且进程优先使用当前可用范围内最小的文件描述符

但一个进程打开文件同时获取一个信息的结构体(pos), 但是两个进程打开同一个也会产生不同的两个结构体

这个结构体的"指针"会放在一个数组(存放在"被fopen()文件"的信息)中, 且有一个下标(文件描述符)

这个数组的前三个被标准流占用(即0, 1, 2)

打开的文件的信息 != 文件的信息, 准确来说, |0|1|2|3|这个数组是存放我现在fopen()的文件的结构体信息(即打开的文件的信息), 如果我FILE *fp1 = fopen(xfile, "r"), 那么xfile的结构体信息就会放入这个数组中, 且返回一个下标x1(文件描述符), 当我另一个进程也FILE *fp2 = fopen(xfile, "r"), 此时就会创造另一份xfile的结构体信息再放入数组的另一个下标x2位置, 且返回另一个下标.

当fclose(fp1), 此时下标x1的指针会将结构体信息释放, 但另一个进程所使用的x2下标内的内容不受影响, 源文件也无影响



- 不过也存在两个下标的指针指向同一个结构体的情况
- 每个结构体都有一个存放打开数目的计数器, 如果计数器不为0, 则空间不释放
- 这个数组的大小为1024, 可存放1024个结构体指针

##### 文件IO操作: open, close, read, write, lseek

```C
//date: 1,17, 利用系统调用io实现更为严谨的cp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
        //open status
        int sfd = 0;
        int dfd = 0;
        //number of reads
        int len = 0;
        //write status
        int ret = 0;
        // current position
        int pos = 0;
        char buf[BUFSIZE];

        if(argc < 3)
        {
                fprintf(stderr, "Usage %s...\n", argv[0]);
                exit(1);
        }

        sfd = open(argv[1], O_RDONLY);
        if(sfd < 0)
        {
                perror("open()");
                exit(1);
        }
    	// 0600是指文件权限
        dfd = open(argv[2], O_WRONLY|O_CREAT, O_TRUNC, 0600);
        if(dfd < 0)
        {
                close(sfd);
                perror("open()");
                exit(1);
        }
        
    	while(1)
        {
            // 每次读取的空间大小为BUFSIZE, 其占据的空间其实是栈空间
                len = read(sfd, buf, BUFSIZE);
                if(len < 0)
                {
                        perror("read()");
                        break;
                }
                //finish reading
                if(len == 0)
                {
                        break;
                }
                pos = 0;
                //this is a bug, so we need a while
                while(len > 0)
                {
                        // buf + pos,将指针移动到pos位置再写入后面的东西
                        ret = write(dfd, buf+pos, len);
                        if(ret < 0)
                        {
                                perror("write()");
                                close(dfd);
                                close(sfd);
                                exit(1);
                        }
                        pos += ret;
                        len -= ret;
                }
        }

        close(dfd);
        close(sfd);

        return 0;
}

```



##### buffer和cache的区别

buffer是写的缓冲区, cache是读的缓冲区, 都是为了解决互访的两种设备存在速率差异



NONBLOCK表示的是非阻塞, 而BLOCK表示的是阻塞



```
r -> O_RDONLY(只读)

r+ -> O_RDWR(读写)

w -> O_WRONLY(只写) | O_CREAT(无则创建) | O_TRUNC(有则清空)

w -> O_RDWR | O_CREAT | O_TRUNC
```



##### ⭐如何判断是用重载和变参实现?

传入多个参数到函数中, 如果警告是语法错误, 所有是定参, 那么说明该函数是重载实现的

而如果没有语法错误, 那么就是变参实现

###### gcc -Wall可以打印所有的警告!!!!!!!!!!!!!!!!!



#### 文件IO与标准IO的区别

文件IO: 缓冲区小, 但响应速度更快

标准IO: 会有更大的缓冲区, 所以吞吐量更大.

面试题: 如果使一个程序变快?

从两个方面回答, 响应速度和吞吐量

当对于用户而言, 整体的反应机制才是感受上变快, 提高吞吐量使用标准IO就很有必要了

注意: 标准IO和文件IO(系统调用IO)不能混用, 标准IO是存在大缓冲区的, 修改的东西很多放在缓冲区里, 使得文件里的实际pos指针没有改变, 故存在结构体不同的情况

如果想要转换, 可以使用两个函数FILE* fdopen(int fd, const char *mode)[将IO流封装成其他模式的IO], 

int fileno(FILE *stream)将IO流转换为标准IO的文件描述符

##### 混用结果

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
        putchar('a');
        write(1, "b", 1);//主要平时的话, 记得ret = write, if(ret < 0) perror();

        putchar('a');
        write(1, "b", 1);

        putchar('a');
        write(1, "b", 1);

        exit(0);
}
// 结果: bbbaaa
//解释: 由于a是用标准IO,所以没有遇到刷新的情况下, 它不会及时输出,而b是用系统调用IO,故及时输出
```



#### IO的效率问题



#### 文件共享: 多个任务共同操作一个文件或者协同完成任务

面试: 写程序删除一个文件的第10行

下面这两个函数能够截断

int truncate(const char * path, off_t length);

int ftruncate(int fd, off_t length);



#### 原子操作: 不可分割的操作   AND   程序中的重定向: dup, dup2

原子操作的作用: 解决竞争和冲突

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FNAME "/tmp/out"

int main(void)
{
        int fd;
        //save NO.1 device, it is a error, beacuse this terminal will interfere
        //int onefd = dup(1);

        //close the first, the first give fd
        //close(1);

        // if fd was originally NO.1
        fd = open(FNAME, O_WRONLY|O_CREAT|O_TRUNC, 0600);
        if(fd < 0)
        {
                perror("open()");
                exit(1);
        }

        //this isn't atomic operation, so it may cause others to preempt NO.3
        //causing him to become NO.4
        //close(1);
        //dup() using the low‐est-numbered unused file descriptor for the new descriptor
        //dup(fd);

        //this is atomic operation, because it can determine whether NO.1 is occupied,
        //or whether it was originally NO.1
        //If the file descriptor newfd was previously open,  it  is  silently
        //closed before being reused
        //If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then
        //dup2() does nothing, and returns newfd.
        dup2(fd, 1);

        //the old one must be closed
        if(fd != 1)
        {
                close(fd);
        }

        /************/
        puts("hello!");

        //restore the scene, 复原现场, 即把原先1号的结构体重新放回, 不过本人在复原时出现了错误, 原本是还原, 结果终端继续
    	//保留导致输出在终端上了, 建议重新打开该设备的方法, 否则会出现错误

        exit(0);

```



#### 同步: sync, fsync, fdatasync

文件亚数据: 文件各种信息(不包括内容, 只包括创建时间等)

sync: 涉及设备挂载

fsync(int fd), 同步文件

fdatasync: 只刷亚数据(metadata)



##### fcntl()

文件描述符的操作基本上源于这个函数, 管理文件描述符

##### ioctl();

设备相关的内容



/dev/fd/目录: 虚目录, 显示的是当前进程的文件描述符信息





#### c语言中定参, 函数参数所使用的堆栈

正常来说, 一个定义出来的参数一定是放在栈中的, 但是64位操作系统中, 函数参数是先通过寄存器存放的, 如果寄存器不够放才会放入栈中.
