
//////////////////////////////////////////////////////////////////////////
//  @file     48_unique_lock.h
//  @author   Morris
//  @date     2019-05-03
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-05-03
//  -added 
//  @remark   创建多个线程、数据共享问题分析、案例代码
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

			//std::unique_lock<std::mutex> guard1(mutex1_);
			//std::unique_lock<std::mutex> guard1(mutex1_, std::try_to_lock);
			//if (guard1.owns_lock())
			//{
			//	// 拿到了锁
		   //std::unique_lock<std::mutex> gurad(mutex1_, std::defer_lock);
			//std::unique_lock<std::mutex> gurad(mutex1_);
			//std::unique_lock<std::mutex> guardn(std::move(gurad));

		   std::unique_lock<std::mutex> guard = rtn_unique_gurad();
			//std::mutex *ptx = gurad.release(); //现在你有责任自己解锁了
			//gurad.lock();  // 不用自己unlock
			//if(gurad.try_lock() == true)
			queue_.push_back(i);  // 假设这个数字i就是我们收到的命令，直接弄到消息队列中
			//else
			//	cout << "send执行，没有拿到锁，只能干点别的事情" << i << endl;

			//	// ...
			//	// 其他处理的代码
			//}
			//else
			//{
			//	// 没有拿到锁
			//	cout << "send执行，没有拿到锁，只能干点别的事情" << i << endl;
			//}
			//ptx->unlock();
            
			
        }
    }

	bool porc(int &command)
	{
		std::unique_lock<std::mutex> guard1(mutex1_, std::defer_lock);
		guard1.lock();

		//std::chrono::microseconds dura(200);
		//std::this_thread::sleep_for(dura);  // 休息一定的时长

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

namespace unique_space
{

    int main()
    {
		// 一：unique_lock取代lock_guard
		// unique_lock是个类模板，工作中，一般lock_guard(推荐使用),lock_guard取代了mutex的lock和unlock
		// unique_lock比lock_guard灵活很多，效率上差点，内存占用多点

		// 二：unique_lock的第二个参数
		// (2.1)std::adopt_lock：表示这个互斥量已经被lock了(你必须提前把这个互斥量lock，否则报异常)
		// (2.2)std::try_to_lock
		// 我们会尝试mutex的lock去锁定这个mutex，但如果没有锁成功，我们也会返回，不会阻塞在那里。
		// 用这个try_to_lock的前提是你自己不能先去lock。
		// (2.3)std::defer_lock
		// 用这个defer_lock的前提，不能直接先lock，否则会报异常
		// 初始化了一个没有加锁的mutex

		// unique_lock的成员函数
		// lock,unlock
		// try_lock:尝试给互斥量加锁，如果拿不到锁返回false，如果拿到了返回true，这个函数不阻塞
		// release:返回它所管理的mutex对象指针，并释放所有权，也就是说，这个unique_lock和mutex不再有联系
		// 如果原来的mutex处于加锁的状态，你有责任自己解锁，release返回的是原始的mutex指针
		// 也有人把锁头锁住的代码多少称为锁的粒度，粒度一般用粗细来表示
		// 1.锁住的代码少，粒度细，执行效率高
		// 2.锁住的代码多，粒度粗，执行效率低
		// 学会选择合适的粒度，是高级程序员能力和实力的体现

		// unique_lock所有权的传递
		//std::unique_lock<mutex> guard(mutex_);
		// guard拥有mutex 的所有权
		// guard可以把自己对mutex的所有权转移给其他的unique_lock对象
		// a.std::move
		// b.reutrn std::unique_lock<std::mutex>


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