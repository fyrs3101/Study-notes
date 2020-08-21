/*
* @Author: Luoxin
* @Email: luoxin9712@163.com
* @Created  time: 2020-07-30 18:44:41
* @Modified time: 2020-07-31 00:30:29
* @Content: packaged_task
* 			①可以包装任何可调用对象（即callableobj.cpp）
*			②	模板声明如下：
* 				template< class R, class ...Args > 
*				class packaged_task< fn(Args...)>;
*			③通过 packaged_task 包装后，可以通过 thread 或 仿函数 来启动
*			④std::packaged_task 对象是异步 Provider，
*			  它在某一时刻通过调用被包装的任务来设置共享状态的值。
*			⑤std::future 对象是一个异步返回对象，通过它可以获得共享状态的值，
* 			  当然在必要的时候需要等待共享状态标志变为 ready.
*			⑥多数情况推荐使用 async 开启异步任务
*
*/


#include <iostream>     // std::cout
#include <utility>      // std::move
#include <future>       // std::packaged_task, std::future
#include <thread>       // std::thread
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
using namespace std;


queue<packaged_task<int(int)> >q;
std::vector<int> v; // 用于存储各个阶乘的值
mutex mu; // 用于入队出队的数据同步
condition_variable cond; // 用于数据同步

// 阶乘函数
int factorial(int N) {
	int res=1;
	for(int i=N; i>1; --i) {
		res *= i;
	}
	return res;
}

// 主要看这段代码
void out_func(int N){
	unique_lock<mutex> locker(mu); // 上锁
	cond.wait(locker, [&](){return (!q.empty());});

	// 一系列的相关操作
	packaged_task<int(int)> t = move(q.front());
	future<int> fu1 = t.get_future();
	t(N);
	// thread(move(t), N).join(); // 与上一行同样启动

	int value=fu1.get();
	v.push_back(value);

	q.pop();
	locker.unlock();
}

void in_func(){
	unique_lock<mutex> locker(mu);

	packaged_task<int(int)> t(factorial);
	q.push(move(t));

	locker.unlock();
	cond.notify_one();
}

int main ()
{
	std::vector<thread> v1, v2;
    for(int i=10; i>1; --i) {
    	v1.push_back(thread(in_func));
    	v2.push_back(thread(out_func, i));
    }
    for(int i=0; i<v2.size(); ++i) {
    	v1[i].join();
    	v2[i].join();
    }
    for(auto x:v) {
    	cout << x << endl;
    }
    return 0;
}
/*
* ubuntu 18.04.4 LTS
* gcc version 7.5.0
* 
* 运行结果为：
* 3628800
* 40320
* 362880
* 5040
* 720
* 120
* 24
* 6
* 2
*/
