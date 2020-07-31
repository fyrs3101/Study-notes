/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-31 07:12:56
* @Modified time: 2020-07-31 08:49:47
* @Content: 时间限制，
*			thread: sleep_for, sleep_until
*			unique_lock: try_lock_for, try_lock_until
*			condition_variable: wait_for, wait_until
*			future: wait_for, wait_until
*			注意在 unique_lock 中要使用 timed_mutex 才行
*			另外timed_mutex对象也可以使用try_lock_for 和 try_lock_until
*/


#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

void func(int N){
	return;
}

std::timed_mutex mtx;

// unique_lock
void fireworks () {
	std::unique_lock<std::timed_mutex> lck(mtx,std::defer_lock);
	// waiting to get a lock: each thread prints "-" every 200ms:
	while (!lck.try_lock_for(std::chrono::milliseconds(200))) {
		std::cout << "-";
	}
	// got a lock! - wait for 1s, then this thread prints "*"
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "*\n";
}

int main(int argc, char const *argv[])
{
	// thread
	std::thread t1(func, 6);
	std::this_thread::sleep_for(chrono::milliseconds(3));
	chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::milliseconds(4);
	std::this_thread::sleep_until(tp);
	t1.join();

	// unique_lock
	// 本来此处是要建立新线程，在此懒一下
	fireworks();

	// conditioin_variable
	std::mutex mu2;
	std::unique_lock<std::mutex> locker2(mu2);
	std::condition_variable cond;
	cond.wait_for(locker2, chrono::milliseconds(3));
	cond.wait_until(locker2, tp);

	// future
	std::promise<int> p;
	std::future<int> f = p.get_future();
	f.wait_for(chrono::milliseconds(3));
	f.wait_until(tp);


	return 0;
}