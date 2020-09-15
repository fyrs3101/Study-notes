# linux 系统基本命令

## 文件管理、文本处理

<u>（一些基础的、掌握了的就没写进来）</u>

- which

  查看命令的绝对路径

  -a 选项显示全部

  ```bash
  $ which find
  /usr/bin/find
  ```

- whereis

  不仅能查询出命令还能查询出 ubuntu 资料库里记载的文件

  ```bash
  $ whereis find
  find: /usr/bin/find /usr/share/man/man1/find.1.gz /usr/share/info/find.info.gz
  ```

- locate

  直接加上要查询的文件名即可，也是从资料库中进行查询，但有时会发生刚安装完的软件查询不到的现象

  ```bash
  $ locate find
  # 结果太多了，略
  ```

- find

  `$ find  <path>  -option [ -print] `

  选项特别多，这里只列举部分

  | 选项             | 说明                                                         |
  | ---------------- | ------------------------------------------------------------ |
  | -amin n          | 在过去 n 分钟内被读取过的                                    |
  | -anewer file     | 比文件 file 更晚被读取过的文件                               |
  | -atime -n        | 在最近 n 天内被读取过的文件，改为 +n 是 n 天之前（后面同理） |
  | -cmin -n         | 在过去 n 分钟内被修改过的                                    |
  | ipath p, -path p | 路径名称符合 p 的文件，ipath 会忽略大小写                    |
  | -type c          | 文件类型是 c 的文件                                          |
  | -size -n         | 文件大小小于 n 的文件，b, c, w, k, M, G                      |
  | -name “name”     | 文件名称符合 name 的文件，iname 会忽略大小写，注意加引号，不然会报问题 |
  | -empty           | 空文件                                                       |

  ```bash
  $ find . -name "*.c"
  ```
  
- 压缩、解压缩

  - gzip

    压缩后的扩展名为 .gz

    提供 1-9 级压缩比，压缩效果从 1-9 依次递增

    -d 解压缩

    ```bash
    $ gzip filename
    $ gzip -1 filename
    $ gzip -d filename.gz
    ```

  - zcat

    不用将 .gz 的压缩文件解压就能查看里面的内容

    ```bash
    $ zcat filename.gz
    ```

  - bzip2

    压缩后的扩展名为 .bz2

    选项之类的与 gzip 一致

    ```bash
    $ bzip2 filename
    $ bzip2 -1 filename
    $ bzip2 -d filename.bz2
    ```

  - bzcat

    与 zcat 也相应一致

  - tar

    | 选项 | 说明                                                         |
    | ---- | ------------------------------------------------------------ |
    | -c   | 创建新的打包文件                                             |
    | -x   | 将 .tar 文件解包                                             |
    | -z   | 用 gzip 命令进行压缩或者解压缩                               |
    | -j   | 用 bzip2 命令进行压缩或者解压缩                              |
    | -t   | 查看一个打包文件里的文件目录                                 |
    | -f   | 使用文件或设备（基本必选）                                   |
    | -k   | 如果在还原时有相同文件则不进行覆盖                           |
    | -v   | 在打包或者解包解压后将文件详细清单显示出来                   |
    | -N   | 在此选项后加日期，如果文件日期比-Ｎ选项后面加的日期还要新才会被加进压缩包中 |



## 磁盘管理

- 查看磁盘空间

  - 查看磁盘空间利用大小

      ```bash
      $ df -h
      ```

      -h:human 缩写，以易读方式显示结果，即带单位比如 M/G

  - 查看当前目录所占空间大小

      ```bash
      $ du -sh
      ```

      -h 人性化显示

      -s 递归整个目录大小
    
  - 查看当前目录下所有子文件夹排序后的大小
  
      ```bash
      $ du -sh 'ls' | sort
      ```
  
      

## 进程管理

- 查询进程

    - 查看正在运行的进程信息

      ```bash
      $ ps -ef
      ```

      后面可接管道符  | grep 进一步缩小范围

    - 查询进程 id

      ```bash
      $ pgrep -l re
      ```

      查找进程名中含有 re 的进程

    - 显示进程信息，并实时更新

      ```bash
      $ top
      ```

    - 查看端口占用情况（注意不是进程id)

      ```bash
      $ lsof -i:3306
      ```

    - 查看指定进程 id 打开的文件

      ```bash
      $ lsof -p 6789
      ```

    - 查询指定目录下被进程开启的文件（使用 +d 递归目录）

      ```bash
      $ lsof +d mydir/
      ```

-   终止进程

  杀死指定 PID 的进程

  ```bash
  $ kill PID
  ```

  可加 -9 等选项
  
  

- 进程监控

    ```bash
    $ top
    ```

    进入交互界面后，再输入以下任意字母，注意大小写

    P：根据CPU使用百分比大小进行排序。

    M：根据驻留内存大小进行排序。

    i：使top不显示任何闲置或者僵死进程。



- 分析进程栈

    ```bash
    $pmap PID
    ```



## 性能监控

- 监控 CPU

  1. 查看 cpu 使用率

     ```bash
     $ sar -u 1 2
     ```

     后面两个参数表示监控的频率，比如例子中的1和2，表示每秒采样一次，总共采样2次

  2. 查看 cpu 平均负载

     ```bash
     $ sar -q 1 2
     ```

     sar指定-q后，就能查看运行队列中的进程数、系统上的进程大小、平均负载等；

- 查询内存

  1. 查看内存使用状况 sar指定-r之后，可查看内存使用状况

     - ```bash
       $ sar -r 1 2
       ```

  2. 查看内存使用量

     ```bash
     $ free -m
     ```

- 查询页面交换

  ```bash
  $ sar -W 1 3
  ```

- 查询硬盘使用情况

  - 查看磁盘空间利用情况

      ```bash
      $df -h
      ```
      
  - 查询当前目录下空间使用情况

      ```bash
      $du -sh
      ```

      -h是人性化显示 s是递归整个目录的大小
      
  - 查看该目录下所有文件夹的排序后的大小

      ```bash
      for i in `ls`; do du -sh $i; done | sort
      或者
      du -sh `ls`
      ```


-   watch
-   vmstat



## 网络工具

-   查询网络服务和端口

    netstat

    所有端口 -a

    所有tcp端口 -at

    所有有监听的服务状态 -l

    查询端口 `netstat -antp | grep 6789`

-   lsof

-   网络路由

    查看路由状态

    ```bash
    $ route -n
    ```

    发送 ping 包到地址 ip

    ```bash
    $ ping IP
    ```

    探测前往地址IP的路由路径

    ```bash
    $traceroute IP
    ```

    DNS查询，寻找域名domain对应的IP:

    ```bash
    $host domain
    ```

    反向DNS查询:

    ```bash
    $host IP
    ```