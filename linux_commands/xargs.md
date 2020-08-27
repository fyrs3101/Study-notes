# xargs

由于很多命令不支持 `|` 管道来传递参数，而日常工作中又有这个必要，所以就有了 xargs 命令。`xargs` 一般是和管道一起使用。



```bash
$ ls *.cpp | xargs wc
```

显示每个 cpp 文件的统计信息



-   `-p`

    交互模式，终端上显示将要执行的命令，xargs 等待我们输入 y 或者 n 来相应

-   `-I`

    ```bash
    $ cat test.txt
    hello.c
    hello.cpp
    hi.c
    hi.cpp
    ```

    ```bash
    $ cat test.txt | xargs -I % touch %
    $ ls
    hello.c hello.cpp hi.c hi.cpp
    ```

    `-I` 定义了替换字符串，在命令行中出现任何替换字符串的位置，都会插入我们提供给 xargs 的值，`%` 也可以为其他自定义的内容。

    

---

似乎也就这些值得说了，其他都是一些应用而已