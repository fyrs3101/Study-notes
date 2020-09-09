/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-30 11:11:56
* @Modified time: 2020-09-09 13:41:42
* @Content: 
*	 future<int> fu = async(func, args*)
*	 注意 std::async 传递参数与 std::thread 基本一致
*	 也可以用函数指针，类对象，lamada 函数作为参数
*	 《CPP-Concurrency-In-Action-2ed-2019》 chapter4 4.2 中有相关代码
*	 ------------------------------------------------
* 	 可以在第一个参数前再加一个参数 launch::async 或者 launch::deferred
*	 ①前者创建新线程，后者则在主线程完成，默认为前者
*	 ②使用前者的话，会立即执行，即使不调用future.get() 也会执行task
*	   而后者，只有在 future.get() 时才会执行task
*	   个人理解为，执行入口不一样（？）
*	 ③两者要注意参数的类型，是值传递还是引用传递！！注意参数随主线程而变化
*	   另外前者因为要调用子线程，故而会产生一定消耗，在此期间引用传递也需要注意
*	 ④两者的 future.get() 都会阻塞主线程，直到等待调用的子线程（函数）执行完成
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <unistd.h>

using namespace std;

int factorial(int& N) {
	int res = 0;
	for (int i=N; i>=1; --i) {
		res += i;
		++N;
	}
	cout << this_thread::get_id() << " Result is : " << res << endl;
	N = res;
	sleep(2);
	return N;
}

int main(int argc, char const *argv[])
{
	int N=100;
	cout << this_thread::get_id() << endl; // 测试是否在同一个线程 第①条
	
	future<int> fu = async(launch::async, factorial, ref(N)); 
	// 注意如果此处将 ref(N) 改为 N，则程序会报错
	// 如果将第 27 行的函数形参改为 int N，则无论第 44 行的 N 是 ref(N) 还是 N，都将是值传递
	sleep(2); // 与上面那个 sleep 一起测试执行入口 第②条
	for(int i=0; i<100; ++i) {
		N += 1;
	} // 这上面三行只是为了测试传递参数的问题 第③条
	cout << "N's value is: " << N << endl;
	fu.get(); // 注释掉第 45 行，执行后，上下两句 cout 有时间差，验证了 第④条
	// fu.get() 返回的是函数的返回值，可以作为右值
	cout << "-N's value is: " << -N << endl;

	return 0;
}

/*
* ubuntu 18.04.4 LTS
* gcc version 7.5.0
* 
* 运行结果为：
* 139949699372864
* 139949681170176 Result is : 5050
* N's value is: 5150
* -N's value is: -5150
* 
* 该程序运行结果不重要，在于修改相关代码后，比较输出值的差异
*/