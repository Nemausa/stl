//////////////////////////////////////////////////////////////////////////
//  @file     50_async.h
//  @author   Morris
//  @date     2019-06-08
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-06-08
//  -added 
//  @remark   
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef FUTURE_H
#define FUTURE_H

#include <thread>
#include <mutex>
#include <future>
#include <iostream>
#include <vector>
using namespace std;


namespace future_space
{
	//int count_ = 0;
	std::atomic<int> count_ = 0;
	class A
	{
	public:
		int mythread(int param)
		{
			cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << endl;
			std::chrono::milliseconds dura(5000);
			std::this_thread::sleep_for(dura);
			cout << "mythread() end" << "threadid = " << std::this_thread::get_id() << endl;
			return 5;
		}

	};

	int mythread(int param)
	{
		cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << endl;
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "mythread() end" << "threadid = " << std::this_thread::get_id() << endl;
		return 5;
	}
	
	void mythread2(std::future<int> &tmpf)
	{
		cout << "mythread2 id " << std::this_thread::get_id() << endl;
		auto result = tmpf.get();  // 主要是get函数的设计是个移动语义，第二次就会异常了
		cout << "mythread2 result = " << result << endl;
		return;
	}
	void func_promise(std::promise<int> &tmp, int calc)
	{
		// 做一系列复杂的操作
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		calc++;
		int result = calc;
		tmp.set_value(result); // 结果我保存到了tmp这个对象中
	}

	void add()
	{
		for (int i = 0; i < 10000000; ++i)
		{
			count_++;
		}
	}

	vector<std::packaged_task<int(int)>> task_;
	int main()
	{
		cout << "main id" << " threadid = " << std::this_thread::get_id() << endl;
		//std::future<int> result = std::async(mythread, 1);  // 流程会卡在这里
		//cout << "continue... !" << endl;

		//std::future_status status = result.wait_for(std::chrono::seconds(6));  // 等待一秒
		//if (std::future_status::timeout == status) // 我想等待一秒
		//{
		//	// 超时 线程还没有执行完
		//	cout << "超时" << endl;
		//}
		//else if (std::future_status::ready == status)
		//{
		//	// 表示线程成功返回
		//	cout << "线程成功返回" << endl;
		//}
		//else if (std::future_status::deferred == status)
		//{
		//	// 如果async的第一个参数被设置为std::launch::deferred，则条件成立
		//	cout << "线程被执行" << endl;
		//	result.get();
		//}

		// 二：std::shared_future
		//std::packaged_task<int(int)> mypt(mythread);
		//std::thread t1(std::ref(mypt), 1);
		//t1.join();
		//std::future<int> result = mypt.get_future();
		//std::shared_future<int> result_s(std::move(result));
		//std::shared_future<int> result_s(result.share());
		//std::thread t2(mythread2, std::ref(result));
		//t2.join();

		std::thread t1(add);
		std::thread t2(add);
		t1.join();
		t2.join();
		cout << count_ << endl;

		cout << "I love China" << endl;
		return 0;
	}

}

#endif