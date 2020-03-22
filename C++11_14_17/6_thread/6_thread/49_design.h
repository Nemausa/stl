#pragma once
#include <iostream>
#include <thread>
#include <mutex>
using namespace  std;


std::mutex resource_mutex;
std::once_flag g_flag;

class Single
{

	static void Create()
	{
		instance_ = new Single();
		static CGarhuishou cl;
	}
private:
	Single() {}
	~Single() {}
private:
	static Single *instance_;
public:
	static Single *GetInstance()
	{
		//// 提高效率
		//if (instance_ == NULL)  // 双重检查 如果条件不成立，则肯定表示instance_已经被new 过了。
		//{
		//	std::unique_lock<std::mutex> mymutex(resource_mutex); // 自动加锁
		//	if (instance_ == NULL)
		//	{
		//		instance_ = new Single();
		//		static CGarhuishou cl;
		//	}
		//}
		
		std::call_once(g_flag, Create);// 两个线程同时执行到这里，其中一个线程就要等待另外一个线程执行完毕
		return instance_;
	}

	class CGarhuishou
	{
	public:
		~CGarhuishou()
		{
			if (Single::instance_)
			{
				delete instance_;
				instance_ = NULL;
			}
				
		}
		
	};
};

 Single *Single::instance_ = NULL;

 void mythread()
 {
	 cout << "线程开始执行了" << endl;
	 Single *p_a = Single::GetInstance();
 }

namespace design
{

	int main()
	{

		// 设计模式大概谈
		// “设计模式”：代码的一些写法（这些写法跟常规的写法不怎么一样）：程序灵活，维护起来方便，但是别人接管、阅读代码
		// 用“设计模式”理念写出来的代码很晦涩；《head first》


		// 二：单例设计模式
		// 单例设计模式使用频率比较高
		// 单例：在整个项目中，有某个或者某些特殊的类，属于该类的对象，我只能创建1个，多了我创建不了。
		// 单例类；
		Single *a = Single::GetInstance();

		// 三：单例设计模式共享数据问题分析、解决
		// 面临的问题：需要在我们自己创建的线程（而不是主线程）中创建单例类，这种线程可能不止一个。
		// 我们可能会面临GetInstance这种成员函数需要互斥
		std::thread t1(mythread);
		std::thread t2(mythread);
		t1.join();
		t2.join();

		// std::call_once:C++11引入的函数，该函数的第二个参数是一个函数名
		// call_once功能保证函数只被调用一次
		// call_once具备互斥量这种能力，而且效率上，比互斥量消耗的资源更少
		// call_once需要与一个标记结合使用，这个表示std::once_flag;其实once_flag是一个结构
		// call_once就是通过这个标记来决定对应的函数是否执行，调用这个call_once就把这个标记设置为已调用状态；
		// 后续再次调用call_once，只要这个once_flag被设置为“已调用状态”，那么对应的函数就不会再执行了
		

	}
}