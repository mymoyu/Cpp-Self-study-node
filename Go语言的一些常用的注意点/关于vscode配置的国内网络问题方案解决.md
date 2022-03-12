由于国内网络的问题, 如果想要安装go依赖的工具, 大概率会全军覆没

有两个方法可以解决

1. 开启vpn, 不过对于没有的同学会比较麻烦
2. 设置go proxy

```
go env -w GO111MODULE=on
go env -w GOPROXY=https://goproxy.io,direct
```

