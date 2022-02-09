## 高级IO

man 7 signal, 第七章是原理类的

##### 补充: 有限状态机编程(编程思想, 编译原理的)

先画图, 然后哪里需要循环, 确定好n个状态, 然后根据状态编写, 使之回调到对应状态即可

```C
//*****
// relay.c
// 实现两个tty终端的读写
//*****
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
#define BUFSIZE 1024

// 四种状态
enum
{
	STATE_R = 1,
	STATE_W,
	STATE_Ex, // 异常终止态
	STATE_T   // 终止态
};

struct fsm_st
{
	int state; // 当前状态机状态
	int sfd;   // read
	int dfd;   // write
	char buf[BUFSIZE];
	int len;   // 读取的内容长度
	int pos;   // 数组的读取位置
	char *errstr; // 
};

static void fsm_driver(struct fsm_st *fsm)
{
	int ret;
	// 每个状态各司其职, 不要状态跨越
	switch(fsm->state)
	{
		case STATE_R:
		{
			fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
			if(fsm->len == 0)
			{
				fsm->state = STATE_T;
			}
			else if(fsm->len < 0)
			{
				if(errno == EAGAIN) // 读取阻塞造成的假错
					fsm->state = STATE_R;
				else
				{
					fsm->errstr = "read()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos = 0;
				fsm->state = STATE_W;
			}
			break;
		}
		case STATE_W:
		{
			ret = write(fsm->dfd, fsm->buf+fsm->pos, fsm->len);
			if(ret < 0)
			{
				if(errno == EAGAIN)
					fsm->state = STATE_W;
				else
				{
					fsm->errstr = "write()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos += ret; // 数组读取处上移动
				fsm->pos += ret;
				fsm->len -= ret;
				if(fsm->len)
					fsm->state = STATE_W;
				else
					fsm->state = STATE_R;
			}
			break;
		}
		case STATE_Ex:
		{
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;
		}
		case STATE_T:
		{
			/*do sth, as:clear*/
			break;
		}
		default:
		{
			abort();
			break;
		}
	}
}

static void relay(int fd1, int fd2)
{
	int fd1_save, fd2_save; // 存储原先状态
	struct fsm_st fsm12, fsm21;// 读1写2, 读2写1

	// 先都处理为非阻塞
	fd1_save = fcntl(fd1, F_GETFL);
	fcntl(fd1, F_SETFL, fd1_save|O_NONBLOCK);

	fd2_save = fcntl(fd2, F_GETFL);
        fcntl(fd2, F_SETFL, fd2_save|O_NONBLOCK);

	// init struct fsm_st
	fsm12.state = STATE_R;
	fsm12.sfd = fd1;
	fsm12.dfd = fd2;

	fsm21.state = STATE_R;
	fsm21.sfd = fd2;
	fsm21.dfd = fd1;
	
	while(fsm12.state != STATE_T || fsm21.state != STATE_T)
	{
		// 推状态机
		fsm_driver(&fsm12);
		fsm_driver(&fsm21);
	}

	// 恢复优先状态
	fcntl(fd1, F_SETFL, fd1_save);
	fcntl(fd2, F_SETFL, fd2_save);
}

int main(void)
{
	int fd1, fd2;

	fd1 = open(TTY1, O_RDWR);
	if(fd1 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd1, "TTY1\n", 5);

	fd2 = open(TTY2, O_RDWR|O_NONBLOCK);
	if(fd2 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd2, "TTY2\n", 5);

	relay(fd1, fd2);
	close(fd2);
	close(fd1);

	exit(0);
}
```



#### 非阻塞IO

##### 数据中继原理解析(自己看书再学习)

类似于中间人收取你的访问, 然后中间人把访问发过去, 收到的东西自己获取, 再发给你

利用这个就可以做负载均衡, 类似于对外是一个服务器, 但实际处理是由多台服务器处理

##### 简单流程: 自然流程是结构化的

##### 复杂流程: 自然流程不是结构化的



#### IO多路转接 [chronous I/O multiplexing]

监视任务, 当发送监视结果才推动下一步

select();[是以事件为单位组织文件描述符, 阻塞实现]        poll();[以文件描述符为单位组织事件, 阻塞实现]

epoll();[更高效率的poll()]



###### select使用实例[请与第一个例子做对比和补充]:

```C
// 四种状态
enum
{
        STATE_R = 1,
        STATE_W,
        STATE_AUTO,// 分割线, 一旦处于这个状态之下就自动推动
        STATE_Ex, // 异常终止态
        STATE_T   // 终止态
};

static void relay(int fd1, int fd2)
{
        int fd1_save, fd2_save; // 存储原先状态
        struct fsm_st fsm12, fsm21;// 读1写2, 读2写1
        fd_set rset, wset;

        // 先都处理为非阻塞
        fd1_save = fcntl(fd1, F_GETFL);
        fcntl(fd1, F_SETFL, fd1_save|O_NONBLOCK);

        fd2_save = fcntl(fd2, F_GETFL);
        fcntl(fd2, F_SETFL, fd2_save|O_NONBLOCK);

        // init struct fsm_st
        fsm12.state = STATE_R;
        fsm12.sfd = fd1;
        fsm12.dfd = fd2;

        fsm21.state = STATE_R;
        fsm21.sfd = fd2;
        fsm21.dfd = fd1;

        while(fsm12.state != STATE_T || fsm21.state != STATE_T)
        {
                // 布置监视任务
                FD_ZERO(&rset);
                FD_ZERO(&wset);

            	// 存放入事件描述符
                if(fsm12.state == STATE_R)
                        FD_SET(fsm12.sfd, &rset);
                if(fsm12.state == STATE_W)
                        FD_SET(fsm12.dfd, &wset);
                if(fsm21.state == STATE_R)
                        FD_SET(fsm21.sfd, &rset);
                if(fsm21.state == STATE_W)
                        FD_SET(fsm21.dfd, &wset);

                // 监视,     一旦出错, rset和wset的内容就会被清空
                // 如果不是得终止的状态, 才推动状态机
                if(fsm12.state < STATE_AUTO || fsm21.state < STATE_AUTO)
                {
                    	 // 第一个参数是监视文件描述符中最大的一个+1
                        if(select(max(fd1, fd2)+1, &rset, &wset, NULL, NULL) < 0)
                        {
                                if(errno == EINTR) // 出现假错
                                        continue;
                                perror("select()");
                                exit(1);
                        }
                }

                // 查看监视结果
                // 推状态机, 大于STATE_AUTO自动推动状态
                if(FD_ISSET(fd1, &rset) || FD_ISSET(fd2, &wset) || fsm12.state > STATE_AUTO)
                        fsm_driver(&fsm12);
                if(FD_ISSET(fd2, &rset) || FD_ISSET(fd1, &wset) || fsm21.state > STATE_AUTO)
                        fsm_driver(&fsm21);
        }

        // 恢复优先状态
        fcntl(fd1, F_SETFL, fd1_save);
        fcntl(fd2, F_SETFL, fd2_save);
}

```



###### poll(); 使用实例

```C
// 此处用详细版本, 主要改动的内容还是在relay这个函数里
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>

#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
#define BUFSIZE 1024

// 四种状态
enum
{
	STATE_R = 1,
	STATE_W,
	STATE_AUTO,// 分割线, 一旦处于这个状态之下就自动推动
	STATE_Ex, // 异常终止态
	STATE_T   // 终止态
};

struct fsm_st
{
	int state; // 当前状态机状态
	int sfd;   // read
	int dfd;   // write
	char buf[BUFSIZE];
	int len;   // 读取的内容长度
	int pos;   // 数组的读取位置
	char *errstr; // 
};

static void fsm_driver(struct fsm_st *fsm)
{
	int ret;
	// 每个状态各司其职, 不要状态跨越
	switch(fsm->state)
	{
		case STATE_R:
		{
			fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
			if(fsm->len == 0)
			{
				fsm->state = STATE_T;
			}
			else if(fsm->len < 0)
			{
				if(errno == EAGAIN) // 读取阻塞造成的假错
					fsm->state = STATE_R;
				else
				{
					fsm->errstr = "read()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos = 0;
				fsm->state = STATE_W;
			}
			break;
		}
		case STATE_W:
		{
			ret = write(fsm->dfd, fsm->buf+fsm->pos, fsm->len);
			if(ret < 0)
			{
				if(errno == EAGAIN)
					fsm->state = STATE_W;
				else
				{
					fsm->errstr = "write()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos += ret; // 数组读取处上移动
				fsm->pos += ret;
				fsm->len -= ret;
				if(fsm->len)
					fsm->state = STATE_W;
				else
					fsm->state = STATE_R;
			}
			break;
		}
		case STATE_Ex:
		{
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;
		}
		case STATE_T:
		{
			/*do sth, as:clear*/
			break;
		}
		default:
		{
			abort();
			break;
		}
	}
}

static int max(int a, int b)
{
	return a > b?a : b;
}

static void relay(int fd1, int fd2)
{
	int fd1_save, fd2_save; // 存储原先状态
	struct fsm_st fsm12, fsm21;// 读1写2, 读2写1
	struct pollfd pfd[2]; // 监视的文件描述符集合

	// 先都处理为非阻塞
	fd1_save = fcntl(fd1, F_GETFL);
	fcntl(fd1, F_SETFL, fd1_save|O_NONBLOCK);

	fd2_save = fcntl(fd2, F_GETFL);
        fcntl(fd2, F_SETFL, fd2_save|O_NONBLOCK);

	// init struct fsm_st
	fsm12.state = STATE_R;
	fsm12.sfd = fd1;
	fsm12.dfd = fd2;

	fsm21.state = STATE_R;
	fsm21.sfd = fd2;
	fsm21.dfd = fd1;
	
	
        pfd[0].fd = fd1;
        pfd[1].fd = fd2;

	while(fsm12.state != STATE_T || fsm21.state != STATE_T)
	{
		// 布置监视任务
		pfd[0].events = 0; // 清零位图

		if(fsm12.state == STATE_R)
			pfd[0].events |= POLLIN; // 位或上可读
		if(fsm21.state == STATE_W)
			pfd[0].events |= POLLOUT; // 位或上可写

		pfd[1].events = 0;
		if(fsm12.state == STATE_R)
			pfd[1].events |= POLLIN;
		if(fsm21.state == STATE_W)
			pfd[1].events |= POLLOUT;

		// 监视
		// 如果不是得终止的状态, 才推动状态机
		if(fsm12.state < STATE_AUTO || fsm21.state < STATE_AUTO)
		{
			// -1, 表示无等待time, 直到所监视的文件描述符产生事件一直阻塞
			while(poll(pfd, 2, -1) < 0)
			{
				if(errno == EINTR) // 出现假错
					continue;
				perror("poll()");
				exit(1);
			}
		}

		// 查看监视结果
		// 推状态机, 大于STATE_AUTO自动推动状态
		// 1 can read, 2 can write
		if(pfd[0].revents & POLLIN || pfd[1].revents & POLLOUT || fsm12.state > STATE_AUTO)
			fsm_driver(&fsm12);
		// 2 can read, 1 can write
		if(pfd[1].revents & POLLIN || pfd[0].revents & POLLOUT || fsm21.state > STATE_AUTO)
			fsm_driver(&fsm21);
	}

	// 恢复优先状态
	fcntl(fd1, F_SETFL, fd1_save);
	fcntl(fd2, F_SETFL, fd2_save);
}

int main(void)
{
	int fd1, fd2;

	fd1 = open(TTY1, O_RDWR);
	if(fd1 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd1, "TTY1\n", 5);

	fd2 = open(TTY2, O_RDWR|O_NONBLOCK);
	if(fd2 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd2, "TTY2\n", 5);

	relay(fd1, fd2);
	close(fd2);
	close(fd1);

	exit(0);
}
```



#### 其他读写函数

readv();           writev();          [多碎片地址操作读写]





#### 存储映射IO(内存映射)

mmap(); [把某块内存映射到当前进程空间]

munmap(); [解除映射, 类似于free的功能]

```c
//mmap的实现, 计算该文件有多少个a字符
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	struct stat statres;
	char *str;
	int i;
	int count = 0;

	if(argc < 2)
	{
		fprintf(stderr, "Usage...\n");
		exit(1);
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

	if(fstat(fd, &statres) < 0)
	{
		perror("fstat()");
		exit(1);
	}

	// 第一个参数是地址值, 填空表示自动寻找适合的地址空间
	str = mmap(NULL, statres.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if(str == MAP_FAILED)
	{
		perror("mmap()");
		exit(1);
	}
	close(fd); // 空间映射完毕, 关闭文件流

	for(i = 0; i < statres.st_size; ++i)
	{
		if(str[i] == 'a')
			count++;
	}

	printf("%d\n", count);

	munmap(str, statres.st_size);

	return 0;
}
```



##### 共享内存实例

```C
#define MEMSIZE 1024

int main(void)
{
    int pid;
    char *ptr;

    ptr = mmap(NULL, MEMSIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap()");
        exit(1);
    }

    pid = fork();
    if(pid < 0)
    {
        perror("fork()");
        munmap(ptr, MEMSIZE);
        exit(1);
    }

    if(pid == 0) // child write
    {
        strcpy(ptr, "Hello!");
        munmap(ptr, MEMSIZE);
        exit(0);
    }
    else    // parent read
    {
        wait(NULL);
        puts(ptr);
        munmap(ptr, MEMSIZE);
        exit(0);
    }

    exit(0);
}
```



#### 文件锁(防止读写的块发生冲突)

fcntl();    [非阻塞的io操作]

lockf();

flock();

```C
static void func_add(void)
{
    FILE *fp; // 文件流
    int fd; // 文件描述符
    char linebuf[LINESIZE];
    fp = fopen(FNAME, "r+");
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    
    fd = fileno(fp); // 去除file流中的文件描述符
    if(fd < 0)
    {
        perror("fileno()");
        exit(1);
    }
    
    // 上文件锁
    lockf(fd, F_LOCK, 0); // 第三个参数[锁的文件长度]如果为0时, 则是有多长锁多长
    fgets(linebuf, LINESIZE, fp);
    fseek(fp, 0, SEEK_SET);
    sleep(1);
    fprintf(fp, "%d\n", atoi(linebuf)+1); // 文件流是全缓冲模式, 而不是行缓冲
    fflush(fp); // 故此处需要加上fflush, 刷新
    // 解锁
    lockf(fd, F_ULOCK, 0);
    fclose(fp); // 最后关闭文件流, 是因为关闭操作会把锁破坏掉
    
    return ;
}
```

