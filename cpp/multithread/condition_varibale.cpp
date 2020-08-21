/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-30 09:29:50
* @Modified time: 2020-07-30 11:09:41
* @Content: 条件变量
*			只能搭配 unique_lock 使用，因为要自定义开关锁
*/


#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

deque<int> q;
mutex mu; 
condition_variable cond;
bool sign=false; // 为第 43 行测试所用

void func1() {
	int count=10;
	while (count>0) {
		unique_lock<mutex> locker(mu); // 上锁
		q.push_front(count);
		cout << "t1 push a value to queue: " << count << endl;
		locker.unlock(); // 解锁
		cond.notify_one(); // 此处只能激活一个线程，如果需要激活多个则要 cond.notify_all()
		this_thread::sleep_for(chrono::seconds(1)); // 此处代码对程序没影响，只是让线程休眠 1s
		--count;
	}
}

void func2() {
	int data=0;
	while (data!=1) {
		unique_lock<mutex> locker2(mu);
		// 此处 wait 不断的对互斥量进行加减锁
		cond.wait(locker2, [](){return !q.empty();}); // 等待 func1 的通知，以及条件为 true； 
		// cond.wait(locker, [](){return sign;}); // 如果执行此行，则将一直等待
		data = q.back();
		q.pop_back();
		locker2.unlock();
		cout << "t2 got a value from t1: " << data << endl;
	}
}

int main(int argc, char const *argv[])
{
	thread t1(func1);
	thread t2(func2);

	t2.join();
	t1.join();
	return 0;
}

