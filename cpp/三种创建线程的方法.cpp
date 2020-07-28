/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-28 21:03:15
* @Modified time: 2020-07-28 22:12:22
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

	t2_1.join();
	t2_2.join();
	t2_3.join();

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
* 140537257912064The second child thread: 6
* 140537249519360The second child thread: 8
* 140537168393984The second child thread: 9
* The third child thread!
* 
*/