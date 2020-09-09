/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-30 11:25:36
* @Modified time: 2020-09-09 13:42:02
* @Content:  promise
*			 future 是主线程得到子线程(函数)返回的值
* 			 promise 是子线程(函数)得到主线程所传递的值
* 			 另外需要注意的是:
* 			 future 不可复制,只可移动,故而在传递参数以及接收参数的时候,都要用引用
*			 promise 可以复制,故可以直接值传递
*			 shared_future 用于多个需要future的时候
*/


#include <iostream>
#include <future>
#include <mutex>
#include <unistd.h>

using namespace std;

// 形参类型声明也要根据实参的类型而定, future or shared_future ?
int factorial(shared_future<int> f) {
	int res=1;

	int N=f.get();
	for (int i=N; i>1; --i) {
		res *= i;
	}

	sleep(1);
	cout << "Result is : " << res << endl;

	return res;
}

int main() {
	int x=0;

	promise<int> p;
	future<int> f=p.get_future();
	// future<int> fu = async(launch::async, factorial, ref(f));
	// 使用上面一行语句时，要将第 24 行的函数形参改为 future<int>& f

	shared_future<int> sf = move(f);
	future<int> fu1 = async(launch::async, factorial, sf);
	future<int> fu2 = async(launch::async, factorial, sf);
	future<int> fu3 = async(launch::async, factorial, sf);

	p.set_value(6);
	x= fu1.get();
	cout << "x's value is : " << x << endl;
	return 0;
}

/*
* ubuntu 18.04.4 LTS
* gcc version 7.5.0
* 
* 运行结果为：
* Result is : 720
* Result is : 720
* x's value is : 720
* Result is : 720
* 
* 由该程序运行结果可以看出,主程序会等待那几个 future 执行完毕
*/