# sed

Stream Editor

常用于 Linux 中的基本的文本处理。

## 参数说明

-   -e<script>或--expression=<script> 以选项中指定的script来处理输入的文本文件。

    后文有解释

-   -f<script文件>或--file=<script文件> 以选项中指定的script文件来处理输入的文本文件。

-   -n或--quiet或--silent 仅显示script处理后的结果。

-   -i 编辑文件，上述命令只是将处理后的内容输出，但如果要写回文件，需要使用重定向或者 `-i` 选项

## 动作说明

-   a ：新增， a 的后面可以接字串，而这些字串会在新的一行出现(目前的下一行)～
-   c ：取代， c 的后面可以接字串，这些字串可以取代 n1,n2 之间的行！
-   d ：删除，因为是删除啊，所以 d 后面通常不接任何咚咚；
-   i ：插入， i 的后面可以接字串，而这些字串会在新的一行出现(目前的上一行)；
-   p ：打印，亦即将某个选择的数据印出。通常 p 会与参数 sed -n 一起运行～
-   s ：取代，可以直接进行取代的工作哩！通常这个 s 的动作可以搭配正规表示法！例如 1,20s/old/new/g 就是啦！
-   N ：把下一行的内容纳入当成缓冲区做匹配



### N

例子如下，把原文本中的偶数行纳入奇数行匹配

```bash
$ cat test.txt
This is your cat
my cat's name is betty
This is your dog
my dog's name is frank
This is your fish
my fish's name is george
This is your goat
my goat's name is adam
```

```bash
$ sed 'N;s/\n/,/' test.txt
This is your cat,my cat's name is betty
This is your dog,my dog's name is frank
This is your fish,my fish's name is george
This is your goat,my goat's name is adam
```



### a, i

append, insert

```bash
$ sed '2a hello' test.txt
This is your cat
my cat's name is betty
hello
This is your dog
my dog's name is frank
This is your fish
my fish's name is george
This is your goat
my goat's name is adam
```

la 是在第 l 行后添加

而 li 是在第 i 行前添加

```bash
$ sed '2i hello' test.txt
This is your cat
hello
my cat's name is betty
This is your dog
my dog's name is frank
This is your fish
my fish's name is george
This is your goat
my goat's name is adam
```

可以运用匹配在添加文本

```bash
$ sed "/fish/a This is my monkey, my monkey's name is wukong" test.txt
This is your cat
my cat's name is betty
This is your dog
my dog's name is frank
This is your fish
This is my monkey, my monkey's name is wukong
my fish's name is george
This is my monkey, my monkey's name is wukong
This is your goat
my goat's name is adam
```



### c

c 是替换匹配行

```bash
$ sed "2 c This is my monkey, my monkey's name is wukong" test.txt
This is your cat
This is my monkey, my monkey's name is wukong
This is your dog
my dog's name is frank
This is your fish
my fish's name is george
This is your goat
my goat's name is adam
```

```bash
$ sed "/fish/c This is my monkey, my monkey's name is wukong" test.txt
This is your cat
my cat's name is betty
This is your dog
my dog's name is frank
This is my monkey, my monkey's name is wukong
This is my monkey, my monkey's name is wukong
This is your goat
```



### d

删除匹配行

```bash
$ sed '2d' test.txt 
This is your cat
This is your dog
my dog's name is frank
This is your fish
my fish's name is george
This is your goat
my goat's name is adam
```

```bash
$ sed '2,5d' test.txt
This is your cat
my fish's name is george
This is your goat
my goat's name is adam

$ sed '3,$d' test.txt
This is your cat
my cat's name is betty

$ sed '/fish/d' test.txt
This is your cat
my cat's name is betty
This is your dog
my dog's name is frank
This is your goat
my goat's name is adam
```



### p

```bash
# 匹配fish并输出，可以看到fish的那一行被打了两遍，
# 这是因为sed处理时会把处理的信息输出
$ sed '/fish/p' test.txt
This is your cat
my cat's name is betty
This is your dog
my dog's name is frank
This is your fish
This is your fish
my fish's name is george
my fish's name is george
This is your goat
my goat's name is adam

# 使用n参数就好了
$ sed -n '/fish/p' test.txt
This is your fish
my fish's name is george

#从第一行打印到匹配fish成功的那一行
$ sed -n '1,/fish/p' test.txt
This is your cat
my cat's name is betty
This is your dog
my dog's name is frank
This is your fish
```



### s

替代匹配字符串

```bash
$ sed '1,$s/my/his/g' test.txt
This is your cat
his cat's name is betty
This is your dog
his dog's name is frank
This is your fish
his fish's name is george
This is your goat
his goat's name is adam
```



### -e

表示多点编辑

```bash
$ sed -e '$d' -e '1,2s/cat/tac/g' test.txt
This is your tac
my tac's name is betty
This is your dog
my dog's name is frank
This is your fish
my fish's name is george
This is your goat
```





---

主要参考：

1.  [https://coolshell.cn/articles/9104.html#a%E5%91%BD%E4%BB%A4%E5%92%8Ci%E5%91%BD%E4%BB%A4](https://coolshell.cn/articles/9104.html#a命令和i命令)
2.  https://www.runoob.com/linux/linux-comm-sed.html