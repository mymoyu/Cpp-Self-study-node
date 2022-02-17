## 网络套接字

#### 讨论: 跨主机的传输要注意的问题

1字节序问题

通常是从低地址处先出去

大端存储: 低地址处放高字节  05|00|00|00 [这块推荐去看博客]

小段存储: 低地址处放低字节  00|00|00|05|

主机字节序: host

网络字节序: network

_ to_ _ : htons(主机序转网络序), htonl, ntohs(端口网络序转主机序), ntohl(int网络序转主机序)

inet_ntop(int af, const void *src, char *dst, socklen_t size):   

convert IPv4 and IPv6 addresses from binary to text form

2 对齐问题:  

```C
struct
{
	int i;
	float f;
	char ch;
};
```

解决方法: 如果进行网络通信, 则需要告诉编译器无需对齐, 否则可能会造成结构体所占内存更大,通过定义宏的方法

3 类型长度问题: 不同系统对于类型长度的规定不同

解决方案:  int32_t, uint32_t, uint8_t[char]



##### SOCKET: 



#### 报式套接字: (UDP)

netstat -anu  查看udp的情况

被动端(先运行): 取得SOCKET    给SOCKET取得地址      收/发消息     关闭SOCKET

主动端:               取得SOCKET    给SOCKET取得地址      收/发消息     关闭SOCKET

socket();    bind();    sendto();    rcvfrom();    inet_pton();   inet_ntop();                                  setsockopt();[socket选项设置]   getsockopt();

 inet_pton()[将点分文本的IP地址转换为二进制**网络字节序**”的IP地址]

多点通讯: 广播(全网广播, 子网广播), 多播/组播

```C
/*proto.h*/
#ifndef PROTO_H__
#define PROTO_H__

#define RCVPORT "1989"

#define NAMESIZE 11

struct msg_st
{
	uint8_t name[NAMESIZE];
	int32_t math;
	int32_t chinese;
}__attribute__((packed)); // 声明无需对齐

#endif
```

```C
/*rcver.c*/  被动端
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "proto.h"

#define IPSTRSIZE 40

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	struct msg_st rbuf;
	socklen_t raddr_len;
	char ipstr[IPSTRSIZE];

	sd = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_DUP*/);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(RCVPORT)); // 约定端口
	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr); //

        if(bind(sd, (void *)&laddr/*我端地址, 地址指针类型不一致, 故需要转换*/, sizeof(laddr)/*地址长度*/) < 0)
        {
                perror("bind()");
                exit(1);
        }

        /*!!! 回传地址*/
        raddr_len = sizeof(raddr);

        while(1)
        {
                recvfrom(sd, &rbuf, sizeof(rbuf), 0, (void*)&raddr, &raddr_len); // 接>收
                /*IP addr */
                inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
                printf("---MESSAGE FROM %s:%d---\n", ipstr, ntohs(raddr.sin_port));
		printf("NAME = %s\n", rbuf.name);
		printf("MATH = %d\n", ntohl(rbuf.math));
		printf("CHINESE = %d\n", ntohl(rbuf.chinese));
        }

        close(sd);

        exit(0);
}
```

```C
/*snder.c*/   主动端
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "proto.h"

int main(int argc , char **argv)
{
	int sd;
	struct msg_st sbuf;
	struct sockaddr_in raddr;

	if(argc < 2)
	{
		fprintf(stderr, "Usage...\n");
		exit(1);
	}

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

//	bind();

	strcpy(sbuf.name, "Alan");
	sbuf.math = htonl(rand() % 100);
	sbuf.chinese = htonl(rand() % 100);

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(RCVPORT));
	inet_pton(AF_INET, argv[1], &raddr.sin_addr);

	if(sendto(sd, &sbuf, sizeof(sbuf), 0,  (void *)&raddr, sizeof(raddr)) < 0)
	{
		perror("sendto()");
		exit(1);
	}

	puts("OK!");

	close(sd);

	exit(0);
}
```



##### 升级版动态报式套接字

```C
/*proto.h*/
#ifndef PROTO_H__
#define PROTO_H__

#define RCVPORT "1989"

#define NAMESIZE 11

struct msg_st
{
	uint8_t name[NAMESIZE];
	int32_t math;
	int32_t chinese;
}__attribute__((packed)); // 声明无需对齐

#endif
```

```c
/*rcver.c*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "proto.h"

#define IPSTRSIZE 40

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	struct msg_st rbuf;
	socklen_t raddr_len;
	char ipstr[IPSTRSIZE];

	sd = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_DUP*/);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(RCVPORT)); // 约定端口
	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr); //

        if(bind(sd, (void *)&laddr/*我端地址, 地址指针类型不一致, 故需要转换*/, sizeof(laddr)/*地址长度*/) < 0)
        {
                perror("bind()");
                exit(1);
        }

        /*!!! 回传地址*/
        raddr_len = sizeof(raddr);

        while(1)
        {
                recvfrom(sd, &rbuf, sizeof(rbuf), 0, (void*)&raddr, &raddr_len); // 接>收
                /*IP addr */
                inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
                printf("---MESSAGE FROM %s:%d---\n", ipstr, ntohs(raddr.sin_port));
		printf("NAME = %s\n", rbuf.name);
		printf("MATH = %d\n", ntohl(rbuf.math));
		printf("CHINESE = %d\n", ntohl(rbuf.chinese));
        }

        close(sd);

        exit(0);
}
```

```C
/*snder.c*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "proto.h"

int main(int argc , char **argv)
{
	int sd;
	struct msg_st sbuf;
	struct sockaddr_in raddr;

	if(argc < 2)
	{
		fprintf(stderr, "Usage...\n");
		exit(1);
	}

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

//	bind();

	strcpy(sbuf.name, "Alan");
	sbuf.math = htonl(rand() % 100);
	sbuf.chinese = htonl(rand() % 100);

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(RCVPORT));
	inet_pton(AF_INET, argv[1], &raddr.sin_addr);

	if(sendto(sd, &sbuf, sizeof(sbuf), 0,  (void *)&raddr, sizeof(raddr)) < 0)
	{
		perror("sendto()");
		exit(1);
	}

	puts("OK!");

	close(sd);

	exit(0);
}
```

##### 广播实例

```C
/*proto.h*/
#ifndef PROTO_H__
#define PROTO_H__

#define RCVPORT "1989"

#define NAMESIZE 11

struct msg_st
{
	uint8_t name[NAMESIZE];
	int32_t math;
	int32_t chinese;
}__attribute__((packed)); // 声明无需对齐

#endif
```

```C
/*snder.c*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "proto.h"

int main(int argc , char **argv)
{
	int sd;
	struct msg_st sbuf;
	struct sockaddr_in raddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	int val = 1;
	// 打开广播选项
	if(setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0)
	{
		perror("setsockopt()");
		exit(1);
	}

	strcpy(sbuf.name, "Alan");
	sbuf.math = htonl(rand() % 100);
	sbuf.chinese = htonl(rand() % 100);

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(RCVPORT));
	// 全网广播则默认为255.255.255.255
	inet_pton(AF_INET, "255.255.255.255", &raddr.sin_addr);

	if(sendto(sd, &sbuf, sizeof(sbuf), 0, (void *)&raddr, sizeof(raddr)) < 0)
	{
		perror("sendto()");
		exit(1);
	}

	puts("OK!");

	close(sd);

	exit(0);
}
```

```C
/*rcver.c*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "proto.h"

#define IPSTRSIZE 40

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	struct msg_st rbuf;
	socklen_t raddr_len;
	char ipstr[IPSTRSIZE];

	sd = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_DUP*/);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	int val = 1;
	if(setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0)
	{
		perror("setsockopt()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(RCVPORT)); // 约定端口
	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr); //

        if(bind(sd, (void *)&laddr/*我端地址, 地址指针类型不一致, 故需要转换*/, sizeof(laddr)/*地址长度*/) < 0)
        {
                perror("bind()");
                exit(1);
        }

        /*!!! 回传地址*/
        raddr_len = sizeof(raddr);

        while(1)
        {
                recvfrom(sd, &rbuf, sizeof(rbuf), 0, (void*)&raddr, &raddr_len); // 接>收
                /*IP addr */
                inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
                printf("---MESSAGE FROM %s:%d---\n", ipstr, ntohs(raddr.sin_port));
		printf("NAME = %s\n", rbuf.name);
		printf("MATH = %d\n", ntohl(rbuf.math));
		printf("CHINESE = %d\n", ntohl(rbuf.chinese));
        }

        close(sd);

        exit(0);
}
```

##### 组播(由于是组内通信, 所以需要有一个规定的ip地址)

ip ad sh 获取网卡索引号

乌班图用户需要开启ens33网卡  : sudo ifconfig ens33 up

```C
/*proto.h*/
#ifndef PROTO_H__
#define PROTO_H__

#define MGROUP  "224.2.2.2"
#define RCVPORT "1989"

#define NAMESIZE 11

struct msg_st
{
	uint8_t name[NAMESIZE];
	int32_t math;
	int32_t chinese;
}__attribute__((packed)); // 声明无需对齐

#endif
```

```C
/*rcver.c*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>

#include "proto.h"

#define IPSTRSIZE 40

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	struct msg_st rbuf;
	socklen_t raddr_len;
	char ipstr[IPSTRSIZE];

	sd = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_DUP*/);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	struct ip_mreqn mreq;

	inet_pton(AF_INET, MGROUP, &mreq.imr_multiaddr);
	inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address);
	mreq.imr_ifindex = if_nametoindex("ens33");

	if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
	{
		perror("setsockopt()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(RCVPORT)); // 约定端口
	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

    if(bind(sd, (void *)&laddr/*我端地址, 地址指针类型不一致, 故需要转换*/, sizeof(laddr)/*地址长度*/) < 0)
    {
        perror("bind()");
        exit(1);
    }

    /*!!! 回传地址*/
    raddr_len = sizeof(raddr);

    while(1)
    {
        recvfrom(sd, &rbuf, sizeof(rbuf), 0, (void*)&raddr, &raddr_len); // 接>收
        /*IP addr */
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
        printf("---MESSAGE FROM %s:%d---\n", ipstr, ntohs(raddr.sin_port));
        printf("NAME = %s\n", rbuf.name);
        printf("MATH = %d\n", ntohl(rbuf.math));
        printf("CHINESE = %d\n", ntohl(rbuf.chinese));
    }

    close(sd);

    exit(0);
}
```

```C
/*snder.c*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <net/if.h>

#include "proto.h"

int main(int argc , char **argv)
{
	int sd;
	struct msg_st sbuf;
	struct sockaddr_in raddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	struct ip_mreqn mreq;

	inet_pton(AF_INET, MGROUP, &mreq.imr_multiaddr); // 把多播组地址转换为网络字节序
	inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address); // ip地址的合法接口
	mreq.imr_ifindex = if_nametoindex("ens33");// 获取ens33网卡索引号

	// 打开广播选项
	if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &mreq, sizeof(mreq)) < 0)
	{
		perror("setsockopt()");
		exit(1);
	}

	strcpy(sbuf.name, "Alan");
	sbuf.math = htonl(rand() % 100);
	sbuf.chinese = htonl(rand() % 100);

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(RCVPORT));
	// 全网广播则默认为255.255.255.255
	inet_pton(AF_INET, MGROUP, &raddr.sin_addr);

	if(sendto(sd, &sbuf, sizeof(sbuf), 0, (void *)&raddr, sizeof(raddr)) < 0)
	{
		perror("sendto()");
		exit(1);
	}

	puts("OK!");

	close(sd);

	exit(0);
}
```



##### 停等式流控 [确保能够收到内容]

ACK: 确认字符

收data -> 发ack -> 输出 -> 收data  [一个循环]

data包是由编号的, 如果反复收到同一个包(ack发送失败) 则重新发送ack, 丢掉重复发来的包

ack也需要编号, 防止ack延迟送达的情况



#### 流式套接字: (TCP)

netstat -ant  查看tcp的情况

recv(点对点), send() 

收一个ack返回n个包, 不同于之前的收一个发一个, 这样就是滑动窗口

三次握手:C -> [SYN 我C的编号从n开始] S

S -> [发送ack(我知道了你的编号), 同时SYN里写到我S是从编号m开始] C

C -> [ACK 我知道S你的编号了] S

接下来就可以进行通信了

完成前两次握手叫半连接状态, 故S端有一个半连接池.

半连接洪水: 每次连接都停在第二次连接, 第三次握手让C端不发送

半连接洪水的解决方案: C端的ip和port+我端(S端)的ip和port以及sort(每隔1s就会生成一次)做成一个cookie, 在每次第二次握手时发送我方的cookie, 而第三次握手时C端也要发相同的cookie, 当然我会对这个cookie进行校验, 那这样就可以删除半连接池

sort如果不相符, 那么会拿上一个时间的sort进行校验, 如果都不符合, 那么cookie过期, 重发即可

四次挥手: C -> [我要关闭了哦] S,  S -> [我知道你要关闭了, 我也要关闭了] C

C -> [我知道你要关闭了, 我也知道你知道(我要关闭了)] S,

S - > [我知道你知道了(我要关闭了)] C 

注意此处是两个通道, C->S 和 S -> C

```C
/*proto.h*/
#ifndef PROTO_H__
#define PROTO_H__

#define SERVERPORT "1989"

#define FMT_STAMP "%lld\r\n" 
//时戳格式

#endif
```

```C
/*client.c  客户端*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "proto.h"

int main(int argc, char **argv)
{
	int sd;
	struct sockaddr_in raddr;
	FILE *fp;
	long long stamp;

	if(argc < 2)
	{
		fprintf(stderr, "socket(): %s <src_addr>", argv[0]);
		exit(1);
	}

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	//bind();
	
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(SERVERPORT)); // htons转换端口
	inet_pton(AF_INET, argv[1], &raddr.sin_addr);

	if(connect(sd, (void *)&raddr, sizeof(raddr)) < 0) // 发起连接
	{
		perror("connect()");
		exit(1);
	}

	fp = fdopen(sd, "r+"); // 转化成流操作
	if(fp == NULL)
	{
		perror("fdopen()");
		exit(1);
	}

	if(fscanf(fp, FMT_STAMP, &stamp) < 1)
	{
		fprintf(stderr, "Bad format!\n");
	}
	else {
		fprintf(stderr, "stamp = %lld\n", stamp);
	}
	fclose(fp);

	// 正常操作
	//recv();
	//close();

	exit(0);
}
```

```C
/*server.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "proto.h"

#define IPSTRSIZE 40
#define BUFSIZE   1024

static void server_job(int sd)
{
	int len;
	char buf[BUFSIZE];

	len = sprintf(buf, FMT_STAMP, (long long)time(NULL)); // 获取时戳

	if(send(sd, buf, len, 0) < 0)
	{
		perror("send()");
		exit(1);
	}
}

int main(void)
{
	int pid;
	int sd, newsd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddr_len;
	char ipstr[IPSTRSIZE];

	sd = socket(AF_INET, SOCK_STREAM, 0/*默认为IPPROTO_TCP, IPPROTO_SCTP*/);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	// 当当前端口被占用时, 会强制占用
	int val = 1;
	if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0)
	{
		perror("setsockopt()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(SERVERPORT));
	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

	// bind a name to a socket
	if(bind(sd, (void *)&laddr, sizeof(laddr)) < 0)
	{
		perror("bind()");
		exit(1);
	}

	if(listen(sd, 200) < 0) // 能连接的c端数目
	{
		perror("listen()");
		exit(1);
	}

	raddr_len = sizeof(raddr);

	while(1)
	{
		newsd = accept(sd, (void *)&raddr, &raddr_len); // 接收连接
		if(newsd < 0)
		{
			perror("accept()");
			exit(1);
		}

		pid = fork();
		if(pid < 0)
		{
			perror("fork()");
			exit(1);
		}
		
        // 此处实现并发
		if(pid == 0) // 子进程执行的任务
		{
			close(sd); // 子进程无需使用到sd
			inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
			printf("Client:%s:%d\n", ipstr, ntohs(raddr.sin_port));
			server_job(newsd); // 由该函数执行send
			close(newsd);
			exit(0);
		}
		close(newsd); // 关闭掉无需使用的连接文件
	}
	close(sd);

	exit(0);
}
```



##### http图片获取

```C
/*webdl.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
	int sd;
	int len;
	struct sockaddr_in raddr;
	FILE *fp;
	long long stamp;
	char rbuf[BUFSIZE];

	if(argc < 2)
	{
		fprintf(stderr, "socket(): %s <src_addr>\n", argv[0]);
		exit(1);
	}

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	//bind();
	
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(80); // htons转换端口, http默认端口
	inet_pton(AF_INET, argv[1], &raddr.sin_addr);

	if(connect(sd, (void *)&raddr, sizeof(raddr)) < 0) // 发起连接
	{
		perror("connect()");
		exit(1);
	}

	fp = fdopen(sd, "r+"); // 转化成流操作
	if(fp == NULL)
	{
		perror("fdopen()");
		exit(1);
	}

    // 获取该图
	fprintf(fp, "GET /home/mymoyu/嘉然虎年图_3.jpg\r\n\r\n"/*apache的文件结束复活是双换行*/);
	fflush(fp); // 刷新

	while(1)
	{
        // 读取来自网页的文件流
		len = fread(rbuf, 1, BUFSIZE, fp);
		if(len <= 0)
		{
			break;
		}
		fwrite(rbuf, 1, len, stdout);
	}

	fclose(fp);

	exit(0);
}
```



##### 链接测试命令

nc 127.0.0.1 1989               telnet 127.0.0.1 1989(这两个都能用的)

