# c语言学习小问题

## scanf函数

#### scanf函数本身

```c
scanf("%d", &temp);
```
一定要注意取地址符**&**（已多次忘记添加了），至于指针变量不用&，无须赘述。

#### scanf函数与gets函数混用

问题最早出于浙大 pta 平台 浙大版*《C语言程序设计（第3版）》*题目集 习题9-4 查找书籍 

先简单介绍两者区别：

>   **结束标记不同**。输入字符串时，*gets()*遇到**回车**才会结束；而*scanf()*或*cin>>*遇到**空格、回车、Tab**结束，但在缓冲区中还留着这些结束符，此后如果使用gets()想去获取下一行字符串，**它碰到的却是前面遗留下来的回车(或者回车之前还有空格等空白符)**，那么这次gets()就直接失效了。所以就出现了常碰到的第一个字符串变成空白字符串的现象。

故而，解决办法有以下两种：

+   用

```c
while(getchar()!='\n');
```

​		来处理掉缓冲区里的回车换行符，然后再gets()就正常了。

+   如果很明确地就知道缓冲区还留着这么个回车换行符，那就直接读入吧： 

```c
scanf("\n");
```

​		或者用

```c
getchar();
```

​		读入一个字符，然后接着gets()也就不会有问题了。



## 数组

#### 一维数组

声明数组形参

```c
void function(int * array, int n);//此处注意形参的样子，也可写为int array[]
int main()
{
    int array[6];
    ...
    function(array, 6);//此处注意实参的样子
    ...
}
void function(int * array, int n)//只有在函数原型或函数定义头中才能用array[]替换*array
{
    ...
}
```

>   以上摘自《c prime plus（第六版）》p 291

#### 二维数组及多维数组

​	可以将int array\[2][3]理解为数组array中有2个元素，其中每个元素本身都是一个内含3个int变量类型值的数组，由此可以自行想象出其中各元素存储顺序。

```c
void function(int arr[][8], int rows);//第二个维度的值必须声明
int main()
{
    int arr[6][8];
    ...
    function(arr, 6);
    ...
    return 0;
}
void function(int arr[][8], int rows)//也可声明为arr[6][8]，只不过6将被忽略
{
    ...
}
```

第二维度必须声明的原因，可从上面二维数组中各元素的存储情况理解。

同理：

```c
int function(int arr[][6][8][9], int rows);//只能省略最左边方括号中的值
```

第一队方括号只用于表明这是一个指针，而其他方括号则用于描述指针所指向的数据对象的类型。

以下声明与上面的等价

```c
int function(int (*arr)[6][8][9]);//arr指向一个6*8*9的int数组
```

ps1:以下摘自《c prime plus（第六版）》p-309

```c
typedef int arr4[4];//arr4是一个内含4个int的数组
typedef arr4 arr3x4[3];//arr3x4是一个内含3个arr4的数组
int sum2(arr3x4 ar, int rows);//与下面的声明相同
int sum2(int ar[3][4], int rows);//与下面的声明相同
int sum2(int ar[][4], int rows);//标准形式
```

ps2:以下摘自《c prime plus（第六版）》p-304

```c
int (*pr)[2];//pr指向一个内含两个int类型值的数组
int * pz[2];//pz是一个内含两个指针元素的数组，每个元素都指向int的指针
```

个人理解为，前者相当于 `int a[2];pr=&a;` 即数组首地址的指针

```c
#include<stdio.h>
int main(void)
{
	int (* pr)[2];
	int a[2] = {1,2};
	pr = &a;
	printf("%d %d\n", **pr, **pr+1);
	return 0;
}//输出结果为1 2
```

后者即为两个int变量地址，所构成的数组，自己稍微演示了一下，如下

```c
#include<stdio.h>
int main(void)
{
	int a[2] = {1, 2}, b[2] = {3, 4};
	int * pr[2];
	pr[0] = a;
	pr[1] = b;
	printf("%d %d %d %d\n", pr[0][0], pr[0][1], pr[1][0], pr[1][1]);
	return 0;
}//输出结果为1 2 3 4
```

**以上数组内容几乎均来自于《c prime plus》一书，如果不懂可仔细研读**

*其实还有如何动态给多维数组分配内存，及二维数组指针问题，待以后用到时再仔细看*

## sizeof是操作符，不是函数

虽然知道了，也没什么作用￣ω￣=

注意用 `printf` 输出 `sizeof(int)` 时，用 `%lu` 或者 `%zu`

测试环境为 gcc 7.5.0

即：

```c
printf("%lu\n", sizeof(int));
printf("%zu\n", sizeof(int));
```



## 字符串

```c
char str3[4] = "abcd";//会造成数组越界，要注意字符串后有'\0',实际只能录入3个字符
```

前面在scanf函数处已出现过gets()函数，但由于其不安全性，可用fgets()替代。

首先先介绍一下fputs()与puts()的不同之处吧：

 puts()函数会在待输出字符串末尾添加一个换行符

fputs()函数则不会，即前者在输出完成后，光标会移至下一行，而后者输出完成后，光标紧随其后。

再说说fgets()函数吧，fgets()读到一个**换行符**时，会把它**存储在字符串中**，即在后来打印字符串的时候，遇到换行符，也会打印出来，即**光标会移至下一行**。这一点与get()函数不同。

好了，开始放代码了，去吧，皮卡丘！

~~~c
#include<stdio.h>

int main()
{
	char words[10];
	int i;

	puts("please enter:");
	while(fgets(words, 10, stdin)!=NULL && words[0]!='\n')//==NULL意为读到文件结尾
	{
		i=0;
		while(words[i]!='\n' && words[i]!='\0')
			i++;
		if(words[i]=='\n')
			words[i]='\0';
		else//如果删除下面三行，则每次都会读入9个字符，在输出时也会9个9个的输出，而且是完全输出
			while(getchar()!='\n')
				continue;
		puts(words);
	}
	puts("done.");

	return 0;
}
~~~

该程序的运行结果如下（**粗体**为输入的字符）：

>   please enter:
>   **1234567890**
>   123456789
>   **hello world!**
>   hello wor
>   **I love you!**
>   I love yo
>   **me too!**
>   me too!
>
>   done.
>   Press any key to continue

可见，该程序只打印每次输入的前9个字符，当输入不足9个时，则会全部输出。

好了，现在再详细说明**fgets()和gets()的区别**

+   fgets()函数第二个参数指明了读入字符的最大数量，如果该参数值为n，则将读入n-1个字符，或者读到遇到的第一个换行符为止。
+   如果fgets()读到一个换行符，会把它存储在字符串中，而gets()则会丢弃换行符
+   fgets()第三个参数指明要读入的文件。如果读入键盘的输入的数据，则以stdin作为参数

前文已提到，fgets()会读入一个换行符，那么可用以下代码**处理掉换行符**

```c
while (words[i] != '\n')
    i++;
words[i] = '\0';
```

如果输入字符多于要读入的字符，则**可用一下代码丢弃**

```c
while (getchar() != '\n')
    continue;
```

其实上面两段代码在上一个程序中均有所体现。