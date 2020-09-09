/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-29 21:20:48
* @Modified time: 2020-09-08 21:27:19
* @Content:  锁 
* 			 ① mu.lock(), mu.unlock(),
* 			 ② lock_guard<mutex> locker(mu), 
*			 ③ lock(mu1, mu2)
*			   lock_guard<mutex> locker1(mu1, adopt_lock)
*			   lock_guard<mutex> locker2(mu2, adopt_lock)
* 			 ④ unique_lock<mutex> locker(mu) 
*			   用 locker.lock() locker.unlock() 锁住想同步的部分
*				以下对 unique_lock 传入的参数进行讨论
*				在std::unique_lock类的对象在构造时接受一个互斥量作为参数，对该互斥量进行上锁操作。
*				接受一个互斥量和std::defer_lock作为参数，则不对该互斥量进行上锁。
*				接受一个互斥量和std::try_to_lock作为参数，则尝试对互斥量上锁，上锁失败时不会阻塞线程。
*				接受一个互斥量和std::adopt_lock作为参数，则假定当前线程已经拥有互斥量的所有权。
* 			_____________________________________________________
*				lock_guard 和 unique_lock 的异同：
*					都不可以复制，但unique_lock可以移动
* 					即可以用 unique_lock<mutex> locker2 = move(locker)
*					但 unique_lock 消耗更多资源
* 					**unique_lock 可以自由地开锁关锁，而 lock_guard 则只在构造和析构时开关锁
*			 		most of the time std::lock_guard is enough.
*  			____________________________________________________
*				另外，谈到了 call_once 配合 once_flag 使用
*				once_flad fg1;
*				call_once(fg1, func) 后面还可以接 func 所需要的参数
*				使用场景在于，使不论多少线程调用，call_once 所绑定的fg1只执行一次
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

// 此为优化后的第二种，即将资源与互斥量绑定了
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
// 注意 lock_guard 多了一个参数 adopt_lock
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
	// 但是如果将第 70 or 74 行代码注释掉，结果就会产生混乱
	// 说明不能在互斥量保护之后使用共享资源
	// 另外该互斥量锁定了 f，仅仅是限制了其他线程对 f 的访问
	// 如果另外一个线程执行 ofstream mf; mf.open("test.txt", ios::app)
	// 则仍可对 test.txt 进行写入，并不矛盾


	return 0;
}

/*
* 输出结果略
*/