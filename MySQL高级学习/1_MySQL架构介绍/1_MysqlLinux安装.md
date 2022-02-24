Ubuntu系统下如果使用apt-get安装, 要注意此时的密码是随机生成的, 如果按照看具体博客

##### 查看mysql密码和用户(如果随机生成的密码可以用这个命令看下具体的用户名和密码)

sudo cat /etc/mysql/debian.cnf 



#####  登录mysql

mysql -u debian-sys-maint -p



##### 设置开机自启动

update-rc.d mysql defaults

-移除-

update-rc.d mysql remove



##### 安装可视化工具workbench(如果有网络问题建议到官网下载)

sudo apt-get install mysql-workbench



##### 查看安装目录

ps -ef|grep mysql

##### 目录解析

|       路径        |           解释            |               备注               |
| :---------------: | :-----------------------: | :------------------------------: |
|  /var/lib/mysql/  | mysql数据库文件的存放路径 | /var/lib/mysql/atguigu.cloud.pid |
| /usr/share/mysql  |       配置文件目录        |    mysql.server命令及配置文件    |
|      usr/bin      |       相关命令目录        |    mysqladmin mysqldump等命令    |
| /etc/init.d/mysql |       启停相关脚本        |                                  |



##### 关于mysql无法插入中文的解决方案

 首先在mysql终端中输入:

```mysql
mysql> show variables like 'character%';
```

```apl
sudo gedit /etc/mysql/mysql.conf.d/mysqld.cnf

// 往里面添加
character-set-server = utf8

//*************************
[mysqld]
#
# * Basic Settings
#
user		= mysql
pid-file	= /var/run/mysqld/mysqld.pid
socket		= /var/run/mysqld/mysqld.sock
port		= 3306
basedir		= /usr
datadir		= /var/lib/mysql
tmpdir		= /tmp
lc-messages-dir	= /usr/share/mysql

#secure_file_priv= ''
skip-external-locking
character-set-server = utf8			# 添加到这里
//*************************
```

##### 然后再修改一个文件

```
sudo gedit /etc/mysql/conf.d/mysql.cnf
```

##### 往里面添加

```
[mysql]
default-character-set = utf8
```

##### 最后重启mysql

```
sudo service mysql restart
```

