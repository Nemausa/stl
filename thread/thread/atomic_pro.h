//////////////////////////////////////////////////////////////////////////
//  @file     atomic_pro.h
//  @author   Morris
//  @date     2019-02-25
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-25
//  -added 
//  @remark   atomic深入谈
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef ATOMIC_PRO_H
#define ATOMIC_PRO_H
#include <thread>
#include <future>
#include <iostream>
using namespace std;

namespace atomic_pro
{
    std::atomic<int> g_count = 0;
    int mythread()
    {
        for (int i = 0; i < 1000000; ++i)
        {
            ++g_count;
        }
        return 1;
    }

    int myfuture()
    {
        cout << "thread start threadid " << this_thread::get_id() << endl;
        return 1;
    }

    int main()
    {
        // 一般原子操作针对++，--，+=，&=，|= ~=，其他的可能不支持
    /*    thread t1(mythread);
        thread t2(mythread);
        t1.join();
        t2.join();*/

        // std::async参数详述，async用来创建异步任务
        cout << "main start threadid " << this_thread::get_id() << endl;
       
        std::future<int> result = std::async(std::launch::deferred, myfuture); 
        cout << result.get() << endl;

        // std::thread()如果系统资源紧张，那么创建线程可能失败，那么执行std::thread时整个程序可能崩溃
        // std::async我们一般不叫创建一个线程，而叫他创建一个异步任务
        // std::async和std::thread最明显的不同，就是async有时候并不创建新线程。
        // a)如果你用std::launch::deferred来调用async会怎么样
        // deferred延迟调用，并且不创建新线程，延迟到future对象调用wait或get时候才执行
        // 如果么有调用wait或者get，则不会执行
        // b)std::launch::async强制这个异步任务创建新线程，这意味着系统必须给我创建新的线程来执行
        // c)std::launch::async|std::launch::deferred
        // 这里意味着async可能创建新线程并立即执行，或者没有创建线程并延迟调用result.get才开始执行入口函数，两者取其一
        // d)不带参数 默认值应该是c，和C的效果一直，系统会自行决定是异步（创建新线程）还是同步（不创建新线程）运行的方式
        // 自行决定：系统如果决定异步还是同步呢
        // std::aync一般不会报异常，如果系统资源紧张就不会创建新线程
        // 经验:一个程序里线程数量不宜超过100-200，时间片。

        // std::async不确定性问题解决
        // 不加额外参数的std::async调用，让系统自行决定是否创建新线程
        // 问题的焦点在于异步任务有没有被推迟执行呢
        // std::wait_for函数

#if 0

        std::future<int> result = std::async(std::launch::deferred, mythread);
        std::cout << "continue...!" << std::endl;

        //std::cout << result.get() << std::endl;
        // 枚举类型

        std::future_status status = result.wait_for(std::chrono::seconds(0));
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
            // 系统资源紧张
            std::cout << "线程被延迟执行" << std::endl;
            std::cout << result.get() << std::endl;
        }
#endif

        return 0;
    }
}



#endif