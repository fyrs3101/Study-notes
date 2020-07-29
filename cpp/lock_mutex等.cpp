/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-29 21:20:48
* @Modified time: 2020-07-29 23:07:19
* @Content:  锁
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

mutex th_mu;

// 此为第一种，使用 mu.lock() 和 mu.unlock() 来实现，不推荐！！
void th1_func(string msg, int id) {
	th_mu.lock();
	cout << msg << id << endl;
	th_mu.unlock();
}

// 此为第二种，使用 lock_guard<mutex> guard(mu);
// 利用 guard 对象析构时来解锁
// 但资源 cout 并未完全在 mu 的保护下
// 因为 cout 是全局变量，其他线程仍然可以在不加锁的情况下使用 cout
void th2_func(string msg, int id) {
	lock_guard<mutex> guard(th_mu);
	cout << msg << id << endl;
}

void helper() {
	for(int i=0; i<100; ++i){
		th2_func("Hello world: ", i);
	}
}

// 此为优化后的第二种，即讲资源与互斥量绑定了
class Logfile {
private:
	mutex m_mutex;
	ofstream f;
public:
	Logfile() {
		f.open("test.txt", ios::app);
	}
	void s1(string id, int value) {
		lock_guard<mutex> locker(m_mutex); // 加锁
		f << "From " << id << ": " << value << endl;
	}
	void s2(string id, int value) {
		lock_guard<mutex> locker(m_mutex); // 加锁
		f << "From " << id << ": " << value << endl;
	}
};
// t2 线程的函数
void func1(Logfile& log) {
	for (int i=0; i>-1000; --i) {
		log.s1(string("t2"), i);
	}
}
// t3 线程的函数
void func2(Logfile& log) {
	for (int i=0; i<1000; ++i) {
		log.s2(string("t3"), i);
	}
}

// 关于死锁
// 在涉及两个以上的锁的时候，如果用的是 lock_guard，应该注意上锁的顺序应该相同
// 或者，使用 lock(mu1, mu2);	
// lock_guard<mutex> locker(mu1, adopt_lock);
// lock_guard<mutex> locker2(mu2, adopt_lock);
// 此时，两个线程中对于 locker 和 locker2 的顺序就可以颠倒

int main() {
	// 第一种，用 mu.lock() 和 mu.unlock() 太简单，不进行代码测试了

	// 以下为第二种方法的测试
	thread t1(helper);
	for(int i=0; i<100; ++i) {
		cout << "Main: " << i << endl;
	}
	t1.join();
	// 显然第二种方法，也存在问题，cout为全局变量 

	// 以下为优化后的第二种方法，即要将资源与互斥量绑定
	Logfile log;
	thread t2(func1, ref(log));
	thread t3(func2, ref(log));
	t2.join();
	t3.join();
	// 此时可以看到输出结果有序，说明互斥量没问题
	// 但是如果将第 50 or 54 行代码注释掉，结果就会产生混乱
	// 说明不能在互斥量保护之后使用共享资源
	// 另外该互斥量锁定了 f，仅仅时是限制了其他线程对 f 的访问
	// 如果另外一个线程执行 ofstream mf; mf.open("test.txt", ios::app)
	// 则仍可对 test.txt 进行写入，并不矛盾


	return 0;
}

/*
* 输出结果略
*/