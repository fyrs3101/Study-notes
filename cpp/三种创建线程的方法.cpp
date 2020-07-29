/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-28 21:03:15
* @Modified time: 2020-07-29 12:33:22
* @Content: 创建线程的三种方法
*/


#include <iostream>
#include <thread>

using namespace std;

void func(){
	cout << "The first child thread" << endl;
}

class CA{
public:
	int num;
	CA(int _num) : num(_num) {}
	CA(const CA& ca) : num(ca.num){}

	void operator()(){
		cout << this_thread::get_id() << "The second child thread: " << num << endl;
	}

	void f(int i){
		cout << this_thread::get_id() << "The second child thread: " << i << endl;
	}
};


int main(){
	// 第一种方法，直接用函数指针
	thread t1(func);
	t1.join(); // 运行结果为 " The first child thread!"

	// 第二种方法，用函数对象
	CA th2obj(6);

	thread t2_1(th2obj); // 注意如果不加 ref() 则是以值传递
	thread t2_2{CA(8)};
	thread t2_3((CA(9)));
	thread t2_4(&CA::f, th2obj, 9); // 这种应该是算用第一种方法，只不过用的是类的成员函数

	t2_1.join();
	t2_2.join();
	t2_3.join();
	t2_4.join();

	// 第三种方法，用 lamada 函数
	thread t3([]{cout << "The third child thread!" << endl;});
	t3.join();

	return 0;
}


/*
* ubuntu 18.04.4 LTS
* gcc version 7.5.0
* 
* 运行结果为：
* The first child thread
* 140199419246336The second child thread: 6
* 140199342372608The second child thread: 8
* 140199333979904The second child thread: 9
* 140199325587200The second child thread: 9
* The third child thread!
* 
*/