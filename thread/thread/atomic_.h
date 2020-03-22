//////////////////////////////////////////////////////////////////////////
//  @file     atomic_.h
//  @author   Morris
//  @date     2019-02-23
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-23
//  -added 
//  @remark   
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef AOTMIC_H
#define ATOMIC_H

#include <iostream>
#include <thread>
#include <future>
#include <mutex>

const int A = 1UL << 0;


namespace atomic_
{

    int mythread(int mypar)
    {
        std::cout << "mythread start threadid" << std::this_thread::get_id() << std::endl;
        std::chrono::milliseconds dura(5000);
        std::this_thread::sleep_for(dura);  // 休息一定的时长
        std::cout << "mythread end threadid " << std::this_thread::get_id() << std::endl;

        return 5;
    }

    void myfuture(std::shared_future<int> &tmp)
    {
        auto result = tmp.get(); // get函数设计是一个移动语义
        std::cout << "mythread2 result " << result << std::endl;
        return;
    }

    std::atomic<int> g_count = 0;  // 定义一个全局变量
    std::atomic<bool> g_ifend = false;
    void end()
    {
        std::chrono::microseconds dura(1000);
        while (false == g_ifend)
        {
            // 线程没有要求退出，所以本线程可以干中间想干的事情
            std::cout << "threadid " << std::this_thread::get_id() << " 运行中... " << std::endl;
            std::this_thread::sleep_for(dura);
        }

        std::cout << "thread id " << std::this_thread::get_id() << std::endl;
    }
    void write()
    {
        for (int i = 0; i < 1000000; i++)
        {
            g_count++; // 对应的操作是原子操作（不会被打断）
        }
    }

    int main()
    {
        // 一:std::future成员函数get转移数据
        // std::shared_future:也是个类模板。get()函数复制数据
        
        
        std::cout << "main thread id " << std::this_thread::get_id() << std::endl;
#if 0
        
        std::future<int> result = std::async(std::launch::deferred, mythread);
        std::cout << "continue...!" << std::endl;

        //std::cout << result.get() << std::endl;
        // 枚举类型

        std::future_status status = result.wait_for(std::chrono::seconds(6));
        if (std::future_status::timeout == status)   // 超时：表示线程还没有执行完
        {
            std::cout << "线程还没有执行完" << std::endl;

        }
        else if (std::future_status::ready == status)
        {
            std::cout << "线程成功执行成功返回" << std::endl;
            std::cout << result.get() << std::endl;
        }
        else if (std::future_status::deferred == status)
        {
            // 如果async的第一个参数设置为std::async::deferred，本条件成立
            std::cout << "线程被延迟执行" << std::endl;
            std::cout << result.get() << std::endl;
        }
#endif
   
#if 0
        std::packaged_task<int(int)> mypt(mythread);
        std::thread t1(std::ref(mypt), 1);
        t1.join();

        //std::future<int> result = mypt.get_future();
        //bool ifcanget = result.valid();  // 判断是否是有效值
        //std::shared_future<int> result_share(std::move(result));
        //std::shared_future<int> result_share(result.share());

        // 通过get_future返回值直接构造
        std::shared_future<int> result_share(mypt.get_future());

        std::thread t2(myfuture, std::ref(result_share));
        t2.join();
        std::cout << "I love China" << std::endl;
#endif
        // 三：原子操作
        // 3.1）原子操作概念引出
        // 互斥量：多线程编程中保护共享数据：锁 操作共享数据，开锁
        // 有两个线程，对一个变量进行操作，这个线程读，一个线程写。
        // 大家可以把原子操作理解成：不需要用互斥量加锁技术的多线程并发编程方式
        // 原子操作：在多线程中不会被打断的执行程序片段 效率上比互斥量更高 
        // 互斥量的加锁是针对一个代码段，而原子操作针对是一个变量，而不是一个代码段

        // 原子操作一般是指“不可分割的操作”,也就是说这种操作状态要么是完成的，要么是没有完成
        // 不可能出现中间状态
        // std::atomic来代表原子操作，是个类模板，这个东西用来封装某个值
       // 心得：一般用于计数或者统计(累计发送了多少个数据包，累计接受了多少个数据包)

        std::thread t1(end);
        std::thread t2(end);
       
        std::chrono::microseconds dura(5000);
        std::this_thread::sleep_for(dura);
        g_ifend = true;  // 对原子操作写操作,让线程自行结束

        t1.join();
        t2.join();
        //std::cout << "两个线程执行完毕结果是 " << g_count << std::endl;
       
        return 0;
    
    }


}


#endif
