vim -p *	-	同时打开多个文件

ctrl+pg up/pg dn 或者:n 可以切页



输入空行(ctrl+d), 如果是在win环境下则用ctrl+z



vscode的ssh连接问题

我们在VM中安装好Ubuntu 虚拟机后，经常需要使用Xshell、ssh等工具进行远程连接，方便我们在两个操作系统中进行文件的复制与移动，但是有时候会出现无法连接的问题，原因可能是Ubuntu中默认关闭了SSH 服务，即没有启用22号端口。

- netstat -ntlp|grep 22 查看是否开启22端口
- 最后的解决方法在设置里加入"remote.SSH.useLocalServer": true,