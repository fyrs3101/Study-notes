/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-30 17:41:21
* @Modified time: 2020-07-30 19:04:18
* @Content: 创建线程的方法,同样适用于 async
*/


#include <iostream>
#include <thread>

using namespace std;

class A {
public:
	int m;
	A(int _m) : m(_m) {}
	A(const A& a) : m(a.m) {}
	void f(int x, char c) {}
	void operator()(int x) {}	
};

void foo(int N){}

int main(){
	A a(9);
	thread t1(a, 6); // 传递 a 的拷贝给子线程
	thread t2(ref(a), 6); // 传递 a 的引用给子线程
	thread t3(move(a), 6); // a 在主线程中将不再有效,前提是有自己的移动构造函数
	// 说明一下 move ,查阅资料发现, move 在没有定义移动构造函数的对象中, 会使用默认的拷贝构造函数
	thread t4((A(99)), 99); // 传递临时创建的 A 对象给子线程 也可以使用 thread t4{A(99), 99}; 

	thread t5(foo, 6); // 普通函数指针
	thread t6([](int x){return;}, 6); // lamada 函数

	thread t7(&A::f, a, 8, 'w'); // 传递 a 的拷贝的成员函数给子线程
	thread t8(&A::f, &a, 8, 'w'); // 传递 a 的地址的成员函数给子线程

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();

	// 对于 async(a, 6); 的创建也跟上面几种方法一样

	return 0;
}