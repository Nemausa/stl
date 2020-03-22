//////////////////////////////////////////////////////////////////////////
//  @file     condition_pro.h
//  @author   Morris
//  @date     2019-02-27
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-27
//  -added 
//  @remark   条件变量
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef CONDITION_PRO_H
#define CONDITION_PRO_H


#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <list>
#include <atomic>
using namespace std;

namespace condition_pro
{
    atomic<int> atm;
    class A
    {
    public:
        A()
        {
            // auto atm2 = atm;// 操作是不允许的，编译器肯定把拷贝构造函数干掉
            // load()：以远在方式读atomic对象的值
            atomic<int> atm2(atm.load());
            auto atm3(atm2.load());

            atm2.store(12);

        }
        void input()
        {
            //for (int i = 0; i < 100000; i++)
            //{


            //    std::unique_lock<std::mutex> guard1(mutex1_);
            //    std::cout << "插入数据：" << i << std::endl;
            //    list_.push_back(i);
            //    condition_.notify_one();  //尝试把wait线程唤醒，执行完这行 通知一个线程
            //}
            for (int i = 0; i < 100000; i++)
            {
                atm++;
                //atm = atm + 1;
            }
        }

        bool output_proc(int &command)
        {
            std::unique_lock<std::mutex> guard1(mutex1_);

            if (!list_.empty())
            {
                int command = list_.front();
                list_.pop_front();

                return true;
            }


            return false;
        }

        void output()
        {
            //int command = 0;
            //while (true)
            //{
            //    // 如果第二个参数返回true,那么wait直接返回
            //    // 如果第二个参数lambda表达式返回值false，那么wait将解锁互斥量，并堵塞本行，
            //    // 直到有线程调用notify_one()为止
            //    // 如果wait没有第二个参数，那么跟返回true一样
            //    // 当其他线程用notiy_one将本wait（原来睡着/堵塞)的状态唤醒后，wait开始恢复干活
            //    // a)wait不断的尝试重新获取互斥量锁，如果获取不到，那么流程卡在wait这里等着获取
            //    // 如果获取得到，那么就继续执行
            //    // b)上锁
            //    std::unique_lock<std::mutex> guard1(mutex1_);
            //    condition_.wait(guard1, [this]()->bool {
            //        if (!list_.empty())
            //            return true;
            //        return false;
            //    });

            //    // 流程只要能走到这里来，这个互斥锁一定是锁着的
            //    command = list_.front();
            //    list_.pop_front();
            //    std::cout << "取出一个元素" << command << " 线程id" << std::this_thread::get_id() << std::endl;
            //    guard1.unlock();  // 因为unique_lock的灵活性，可以随时的解锁，以免锁住太长时间


            //}

            while (true)
            {
                cout << atm << endl;  // 读atm是个原子操作，但是整个一行代码并不是原子操作
            }
        }
    private:
        std::list<int> list_;
        std::mutex mutex1_;
        std::mutex mutex2_;
        std::condition_variable condition_;
    };

    void main()
    {
        // 虚假唤醒：wait重要有第二个参数，判断公共数据是否存在
        // 线程池
        // 场景设想
        // 服务器程序-》客户端 每来一个客户端，就创建一个新线程为客户提供服务
        // a)网络游戏 20000个玩家不能每个都创建线程，此程序写法在这种场景行不通
        // b)程序的稳定性：编写代码中，偶尔创建一个线程这种代码，这种写法让人不安
        // 线程池：把一堆线程弄到一起，统一管理，这种统一管理调度，循环利用线程的方式叫线程池。
        // 2.2实现方式
        // 在程序启动时，一次性创建好一定的线程，程序代码更稳定。
        // 线程创建的数量
        // 线程开的数量的极限问题  2000个线程基本是极限，再创建线程就崩溃
        // 创建数量的建议
        // a)采用某些技术开发程序，接口提供商建议你，创建数量关于cpu 的建议
        // b)创建多线程完成业务，一个线程等于一条执行通路

        // C++多线程总结


        A obj;
        std::thread input_thread(&A::input, &obj);
        std::thread output_thread(&A::output, &obj);
        std::thread output_thread2(&A::input, &obj);

        input_thread.join();
        output_thread.join();
        output_thread2.join();

        std::cout << "线程结束" << std::endl;
    }

}

#endif
