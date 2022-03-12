connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr) ); //起到的作用是绑定UDP的目标传输, 减少sendto加绑和解绑目标地址信息

并且用write和read替代sendto和recvfrom



为了保证close时, 并不会影响到之后接收未接收的数据, 而采用half-close的方法, shutdown(int sock, int howto[传递断开方式信息])

调用上述函数时，第二个参数决定断开连接的方式，其可能值如下所示。 

SHUT_RD : 断开输入流。 

SHUT_WR: 断开输出流。 

SHUT_RDWR: 同时断开1/0流。