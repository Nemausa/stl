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

#ifndef ASYNC_H
#define ASYNC_H

#include <thread>
#include <mutex>
#include <future>
#include <iostream>
#include <vector>
using namespace std;


namespace async_space
{
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

	void func_promise(std::promise<int> &tmp, int calc)
	{
		// 做一系列复杂的操作
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		calc++;
		int result = calc;
		tmp.set_value(result); // 结果我保存到了tmp这个对象中
	}

	vector<std::packaged_task<int(int)>> task_;
	int main()
	{
		// 一：std::async,std::future创建后台任务并返回值
		// 希望线程返回一个结果
		// std::async 是一个函数模板，用来启动一个异步任务，启动起来一个异步任务后，它返回一个std::future对象，std::future是个类模板
		// 什么叫"启动一个异步任务",就自动创建一个线程并开始执行对应的线程入口函数,它返回std::future对象，
		// 这个std::future对象里面就含有线程入口函数所返回的结果(线程返回的结果)，我们可以通过调用future对象的成员函数get来获取结果；
		// 下列程序是通过std::future对象的get成员函数等待线程执行结束并返回结果
		// 这个get()函数很牛，不拿到结果誓不罢休，但是只能调用一次。
		// 我们通过额外向std::async()传递一个参数，该参数是std::launch类型(枚举类型)，来达到一些特殊的目的
		// a.std::launch::deferred::表示线程入口函数调用被延迟到std::suture的wait()或者get()函数调用时才执行；
		// b.std::launch::deferred::延迟调用，并且没有创建新线程，是在主线程中调用
		
		//A a;
		//int tmp = 12;
		//cout << "mian " << "threadid = " << std::this_thread::get_id() << endl;
		////std::future<int> result = std::async(&A::mythread, &a, tmp);
		//std::future<int> result = std::async(std::launch::deferred,&A::mythread, &a, tmp);
		//cout << "continue..." << endl;
		//int def = 0;
		//cout << result.get() << endl;  // 卡在这里等待mythread执行完毕，拿到结果

		//cout << "I love China" << endl;
		//return 0;

		// std::packaged_task：打包任务，把任务装起来，是个类模板，它的参数是各种可调用对象，
		// 通过std::packaged_task来把各种可调用对象包装起来，方便将来作为线程入口函数调用
		//cout << "mian " << "threadid = " << std::this_thread::get_id() << endl;
		//std::packaged_task<int(int)>mypt(mythread);  // 我们把函数通过packaged_task包装起来
		//std::thread t1(std::ref(mypt), 1);  // 线程直接开始执行，第二个参数作为线程入口函数的参数
		//t1.join(); // 等待线程执行完毕
		//std::future<int> result = mypt.get_future();
		//cout << result.get() << endl;
		//cout << "I love China" << endl;

		// 调用lambda表达式
		/*std::packaged_task<int(int)> mypt([](int para) {
			cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << endl;
			std::chrono::milliseconds dura(5000);
			std::this_thread::sleep_for(dura);
			cout << "mythread() end" << "threadid = " << std::this_thread::get_id() << endl;
			return 5;

		});*/
		//std::thread t1(std::ref(mypt), 1);  // 线程直接开始执行，第二个参数作为线程入口函数的参数
		//t1.join(); // 等待线程执行完毕
		//std::future<int> result = mypt.get_future();
		//cout << result.get() << endl;
		//cout << "I love China" << endl;
		//task_.push_back(std::move(mypt));  // 存入容器，这里用了移动语义，mypt变空
		//auto iter = task_.begin();
		//std::packaged_task<int(int)> mypt2 = std::move(*iter);
		//task_.erase(iter);  // 删除一个元素，迭代已经失效，后续代码不能使用了
		//mypt2(123);
		//std::future<int> result = mypt2.get_future();
		//cout << result.get() << endl;


		// 三：std::promise，类模板
		// 我们能在某个线程中给它赋值，然后我们可以在其他的线程，把这个值取取出用
		std::promise<int> prom; // 声明一个std::promise对象，保存值类型为int
		std::thread t1(func_promise, std::ref(prom), 180);
		t1.join();

		// 获取结果值
		std::future<int> fu = prom.get_future(); // promise和future绑定，用来获取线程返回值
		auto result = fu.get();
		cout << "result = " << result << endl;

		return 0;
	}

}

#endif