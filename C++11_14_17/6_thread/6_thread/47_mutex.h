
//////////////////////////////////////////////////////////////////////////
//  @file     46_mulitiple.h
//  @author   Morris
//  @date     2019-03-30
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-30
//  -added 
//  @remark   创建多个线程、数据共享问题分析、案例代码
//  @note
//////////////////////////////////////////////////////////////////////////
 
#ifndef MUTEX_H
#define MUTEX_H

#include <iostream>
using namespace std;
#include <thread>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <mutex>


class MXA
{
public:
    // 把收到的消息放入到一个队列
    void send()
    {
        for (int i = 0; i < 100000; ++i)
        {
            cout << "push  " << i << endl;

			std::lock_guard<std::mutex> guard1(mutex1_);
			std::lock_guard<std::mutex> guard2(mutex2_);
			//mutex_.lock();
            queue_.push_back(i);  // 假设这个数字i就是我们收到的命令，直接弄到消息队列中
			//mutex_.unlock();
        }
    }

	bool porc(int &command)
	{
		//std::lock_guard<std::mutex> guard1(mutex1_);
		//std::lock_guard<std::mutex> guard2(mutex2_);
		std::lock(mutex1_, mutex2_);
		std::lock_guard<std::mutex> guard1(mutex1_, std::adopt_lock);
		std::lock_guard<std::mutex> guard2(mutex2_, std::adopt_lock);
		
		//mutex_.lock();
		if (!queue_.empty())
		{
			int command = queue_.front();
			queue_.pop_front();  // 移除第一个元素，不返回
			/*mutex1_.unlock();
			mutex2_.unlock();*/
			return true;
		}
		/*mutex1_.unlock();
		mutex2_.unlock();*/

		return false;
	}
    void receive()
    {
		int command(0);
        for (int i = 0; i < 100000; ++i)
        {
			bool result = porc(command);
			if (result == true)
			{
				
			}
            else
            {
                cout << "队列为空" << i<< endl;
            }
        }
    }
private:
    list<int> queue_;  // 容器，专门用于代表玩家发送的命令
	mutex mutex1_;
	mutex mutex2_;
};

namespace mutex_space
{

    int main()
    {
		// 保护共享数据，操作是用代码吧共享数据锁住，其他操作共享数据的线程必须等待解锁。
		// 一：互斥量(mutex)的基本概念
		// 互斥量是个类对象，理解成一把锁，多个线程尝试用lock成员函数来加锁这把锁头，只有一个线程能锁定成功(成功的标注是lock函数返回)
		// 如果没有锁成功，那么流程卡在lock这里不断去尝试锁这把锁头
		// 互斥量使用要小心，保护数据不能多也不能少，少了没有达到保护效果，多了影响效率。
		
		// 二：互斥量的用法
		// (2.1)lock,unlock,先lock操作共享数据，再unlock
		// lock和unlock要成对使用，有lock必然要有unlock，每调用一次lock，必然应该调用一次unlock

		// (2.2)std::lock_guard类模板：直接取代lock和unlock，也就是说使用lock_gurad,不能再使用lock，unlock

		// 三：死锁
		// 张三：站在北京等李四 不挪窝
		// 李四：站在深圳等张三 不挪窝
		// C++中，比如我有两把锁(死锁这个问题是由两个锁头也就是两个互斥量才能产生)，金锁，银锁
		// (1)线程A执行的时候，这个线程先锁金锁，把金锁lock成功后，再去锁银锁。。。
		// 出现上下文切换
		// (2)线程B执行了，这个线程先锁银锁，因为银锁还没有被锁，所以银锁会lock成功，线程B要去锁金锁
		// 此时此刻，死锁就产生了
		// (3)线程A拿不到银锁，流程走不下去
	    // (4)线程B拿不到金锁，流程走不下去

		// std::lock()函数模板
		// 能力：一次锁住两个或者两个以上的互斥量
		// 它不存这种因为多个线程中，锁的顺序问题导致死锁的风险
		// 如果互斥量中有一个没有锁住，它就在那里等着，等所有互斥量都锁住，它才能往下走。
		// 如果只锁一个，另一个没有锁成功，则它立即释放另一个锁

		// std::adopt_lock:起一个标记作用，就是表示这个互斥量已经被lock了，不需要再构造函数里面在对mutex对象进行lock了

		MXA obj;
		thread send_thread(&MXA::send, &obj);
		thread recevie_thread(&MXA::receive, &obj);
		send_thread.join();
		recevie_thread.join();


        cout << "I Love China" << endl;
        return 0;
    }

}



#endif