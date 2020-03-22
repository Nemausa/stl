
//////////////////////////////////////////////////////////////////////////
//  @file     48_unique_lock.h
//  @author   Morris
//  @date     2019-06-04
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-06-04
//  -added 
//  @remark   
//  @note
//////////////////////////////////////////////////////////////////////////
 
#ifndef UNIQUE_LCOK
#define UNIQUE_LCOK

#include <iostream>
using namespace std;
#include <thread>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <mutex>


class UA
{
public:

	std::unique_lock<std::mutex> rtn_unique_gurad()
	{
		std::unique_lock <std::mutex> tmpgurad(mutex1_);
		return tmpgurad;  // 从函数返回一个局部的unique_lock对象是可以的，三章十四届讲过移动构造函数
		// 返回这种局部对象会导致系统生成临时unique_lock对象，并调用unique_lock的移动构造函数
	}

    // 把收到的消息放入到一个队列
    void send()
    {
        for (int i = 0; i < 100000; ++i)
        {
           cout << "push  " << i << endl;
		   std::unique_lock<std::mutex> guard = rtn_unique_gurad();
			queue_.push_back(i);  // 假设这个数字i就是我们收到的命令，直接弄到消息队列中
			condition_.notify_one(); // 我们尝试把wait唤醒
        }
    }

	bool porc(int &command)
	{
		std::unique_lock<std::mutex> guard1(mutex1_, std::defer_lock);
		guard1.lock();
		if (!queue_.empty())
		{
			command = queue_.front();
			queue_.pop_front();  // 移除第一个元素，不返回
			
			return true;
		}
		

		return false;
	}
    void receive()
    {
		int command(0);
		while (true)
		{
			// wait()用来等待一个东西
			// 如果第二个参数lambda表达式返回值是false，那么wait将解锁互斥量，并堵塞到本行
			// 堵塞到什么时候为止呢？堵塞到其他线程调用notify_one()成员函数为止
			// 如果没有第二个参数，就跟返回false一样，堵塞本行

			// 其他线程用notify_one()将本wait的状态唤醒后，wait就开始干活
			// a 不断的尝试获取互斥量锁，如果获取不到就卡在那里等着获取
			// b 如果wait有第二个参数，就判断这个表达式，如果为false，则对互斥量解锁，如果为true，则执行下去
			std::unique_lock<std::mutex> guard1(mutex1_);
			condition_.wait(guard1, [this] {
				if (!queue_.empty())
					return true;
				return false;
			});

			command = queue_.front();
			queue_.pop_front();
			guard1.unlock();


		}
    }
private:
    list<int> queue_;  // 容器，专门用于代表玩家发送的命令
	mutex mutex1_;
	mutex mutex2_;
	std::condition_variable condition_;
};

namespace unique_space
{

    int main()
    {
		// 一：条件变量std::condition_variable,wait(), notify_one();
		// 线程A：等待一个条件满足
		// 线程B: 专门往消息队列中扔数据
		// std::condition_varibale实际上是一个类，是一个和条件相关的一个类，说白了就是等待一个条件达成。
		// 这个类是需要和互斥量来配合工作的，用的时候我们要生成这个类的对象。


		UA obj;
		thread send_thread(&UA::send, &obj);
		thread recevie_thread(&UA::receive, &obj);
		send_thread.join();
		recevie_thread.join();


        cout << "I Love China" << endl;
        return 0;
    }

}



#endif