# 同时依赖 babassl 和 openssl 静态库的 demo 


本仓库是文章 《BabaSSL 与其他 openssl 版本库共存方案》中的代码仓库，可以结合文章的例子运行和调试，学习链接器的链接原理，相信你对链接器的理解会更加深刻。

build.sh 依赖 openssl-1.0.2 和 BabaSSL 的源码和静态库，需要自己手动去 clone 这两个仓库下来，自行编译，并修改 build.sh 中的路径为你机器上的路径。

## openssl 编译参考

```
# git clone git@github.com:openssl/openssl.git

# cd openssl

# git checkout OpenSSL_1_0_2u

# ./config --debug

# make -j4
```

## BabaSSL 编译参考

```
# git clone git@github.com:BabaSSL/BabaSSL.git

# cd BabaSSL

# git checkout OpenSSL_1_0_2u

# ./config --debug

# make -j4
```

开启 symbol-prefix 功能，比如在所有导出符号前加前缀 `BABA_` ：

```
# ./config --debug --symbol-prefix=BABA_

# make -j4
```
