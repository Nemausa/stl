//////////////////////////////////////////////////////////////////////////
//  @file     condition_.h
//  @author   Morris
//  @date     2019-02-20
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-20
//  -added 
//  @remark   条件变量
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef CONDITION_H
#define CONDITION_H


#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <list>

namespace condition_
{
    class A
    {
    public:
        void input()
        {
            for (int i = 0; i < 100000; i++)
            {
                

                std::unique_lock<std::mutex> guard1(mutex1_);
                std::cout << "插入数据：" << i << std::endl;
                list_.push_back(i);
                condition_.notify_one();  //尝试把wait线程唤醒，执行完这行 通知一个线程
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
            int command = 0;
            while (true)
            {
                // 如果第二个参数返回true,那么wait直接返回
                // 如果第二个参数lambda表达式返回值false，那么wait将解锁互斥量，并堵塞本行，
                // 直到有线程调用notify_one()为止
                // 如果wait没有第二个参数，那么跟返回true一样
                // 当其他线程用notiy_one将本wait（原来睡着/堵塞)的状态唤醒后，wait开始恢复干活
                // a)wait不断的尝试重新获取互斥量锁，如果获取不到，那么流程卡在wait这里等着获取
                // 如果获取得到，那么就继续执行
                // b)上锁
                std::unique_lock<std::mutex> guard1(mutex1_);
                condition_.wait(guard1, [this]()->bool{
                    if (!list_.empty())
                        return true;
                    return false;
                });

                // 流程只要能走到这里来，这个互斥锁一定是锁着的
                command = list_.front();
                list_.pop_front();
                std::cout << "取出一个元素" << command<< " 线程id" << std::this_thread::get_id() << std::endl;
                guard1.unlock();  // 因为unique_lock的灵活性，可以随时的解锁，以免锁住太长时间

                
            }
        }
    private:
        std::list<int> list_;
        std::mutex mutex1_;
        std::mutex mutex2_;
        std::condition_variable condition_;
    };

    void func()
    {
        // 一:条件变量std::condition_variable、wati()、notify_one()
        // 线程A：等待一个条件满足
        // 线程B：专门往消息队列中扔消息(数据)
        // std::condition_variable实际上是一个类，是一个和条件相关的一个类，说白了就是
        // 等待一个条件达成。这个类需要和互斥量来配合工作，用的时候生成这个类的对象。

        // 二：上述代码深入思考
        // 三：notify_all
        A obj;
        std::thread input_thread(&A::input, &obj);
        std::thread output_thread(&A::output, &obj);
        std::thread output_thread2(&A::output, &obj);

        input_thread.join();
        output_thread.join();
        output_thread2.join();

        std::cout << "线程结束" << std::endl;
    }

}

#endif
