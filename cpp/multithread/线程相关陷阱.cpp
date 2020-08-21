/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-29 10:36:47
* @Modified time: 2020-07-29 12:04:40
* @Content: 线程相关的常见陷阱
*/


#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <thread>

using namespace std;

// 用 detach() 的时候，不推荐用 引用，不可以用指针
// 用 detach() 的时候，创建线程的同时，构造临时对象的方法传递参数是可行的

// 若传递 int 这种简单类型参数，建议都是值传递
// 如果传递类对象，避免隐式类型转换。

void func(const int& i, char* str){
	cout << "Thread: " << i << " " << &i << endl;
	cout << "Thread: " << str << " " << &str << endl;
}

int main(){
	int num = 2;
	int &_num = num;
	char str[] = "This is a test";
	cout << "Main: " << _num << " " << &_num << endl;
	cout << "Main: " << str << " " << &str << endl;
	thread t(func, _num, str);
	t.detach();

	return 0;
}

/*
* Ubuntu 18.04.4
* gcc 7.5.0
* 运行结果如下
* Main: 2 0x7ffe9dd072c4
* Main: This is a test 0x7ffe9dd072d9
* Thread: Thread: 2 0x55bfcc42c290
* Thread: n�ʿU 0x7f1c560cad80
* Thread: n�ʿU 0x7f1c560cad80
* 显然 main 中的两个变量地址与 thread 中完全不一样
* 并且 thread 中的字符串出现乱码，说明出现了野指针
* 至于为什么子线程打印了两次，这一点存疑，暂未得到解答
*/