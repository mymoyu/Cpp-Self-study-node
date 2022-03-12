#### (1) 请说明TCP/IP的4层协议栈，并说明TCP和UDP套接字经过的层级结构差异。 

链路层 -> IP层 -> TCP层 -> 应用层

​					   \ -> UDP层 -> 应用层

#### (2) 请说出TCP/IP协议栈中链路层和IP层的作用，并给出二者关系。

链路层提供物理连接, IP层让传输数据向目标传输, IP层辅助链路层能够正确的传输数据到目标

####  (3) 为何需要把TCP/IP协议栈分成4层(或7层) ?结合开放式系统回答。 

引导更多人去遵守规范, 让不同的设备都可以互联, 设计成开放式系统, 则可以规范更多人的行为, 少做一些为了互联而浪费的无用功

#### (4) 客户端调用connect函数向服务器端发送连接请求。 服务器端调用哪个函数后，客户端可 以调用connect函数?

服务器调用listen函数的时候才可

#### (5) 什么时候创建连接请求等待队列?它有何作用?与accept有什么关系? 

当服务器受理不过来时, 就可以创建请求等待队列, 将暂时无法处理的连接存放到请求等待队列中, listen建立完连接后有accpet专门来受理请求等待队列中待处理的客户端连接请求

#### (6) 客户端中为何不需要调用bind函数分配地址?如果不调用bind函数，那何时、如何向套 接字分配E地址和端口号?

因为客户端是由操作系统或者说是由内核来分配IP地址和端口(在调用connect函数时), 

#### (7) 把第1章的helloJServer-c和hello-server-win-C改成迭代服务器端，并利用客户端测试更改是否准确

```c
/*serve*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
void error_handing(char *message);

#define BUF_SIZE 1024

int main(int argc, char **argv)
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    int str_len, i;

    char message[] = "Hello World!";

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handing("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1])); // 指定端口

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1 )
        error_handing("bind() error");

    if(listen(serv_sock, 5) == -1)
        error_handing("listen() error");
    
    clnt_addr_size = sizeof(clnt_addr);
    for (i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1)
            error_handing("accept() error");
    
        while ((str_len=read(clnt_sock, message, BUF_SIZE)) != 0)
        {
            write(clnt_sock, message, str_len);
        }
        close(clnt_sock);
    }
    
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
        error_handing("accept() error");
    
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);

    exit(0);
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

```c
/*client*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

#define BUF_SIZE 1024
void error_handing(char *message);

int main(int argc, char **argv)
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    int str_len;

    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s <IP> <Port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if(sock == -1)
        error_handing("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handing("connect() error!");
    else 
        puts("Connected..........");

    while(1)
    {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        write(sock, message, strlen(message));
        str_len = read(sock, message, sizeof(message) - 1);
        if(str_len == -1)
            error_handing("read() error!");
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }
    close(sock);

    exit(0);
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

