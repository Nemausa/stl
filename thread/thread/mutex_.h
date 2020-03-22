//////////////////////////////////////////////////////////////////////////
//  @file     mutex_.h
//  @author   Morris
//  @date     2019-02-19
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-19
//  -added 
//  @remark   线程加锁
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef MUTEX_H
#define MUTEX_H

#include <mutex>
#include <iostream>
#include <thread>
#include <list>

namespace mutex_
{
    class A
    {
    public:
        void input()
        {
            for (int i = 0; i < 100000; i++)
            {
                std::cout << "插入数据：" << i << std::endl;
               // mutex1_.lock();
               //std::lock_guard<mutex> guard1(mutex1_);
                //std::lock(mutex1_, mutex2_);

                //std::lock_guard<mutex> guard1(mutex1_, std::adopt_lock);
               // std::lock_guard<mutex> guard2(mutex2_, std::adopt_lock);
                std::unique_lock<mutex> guard1(mutex1_, std::try_to_lock);
                if(guard1.owns_lock())
                {
                    list_.push_back(i);

                }
                else
                {
                    std::cout << "等待的时候干点别的事情" << std::endl;
                }


                //mutex1_.unlock();
                //mutex2_.unlock();

            }
        }

        bool output_proc(int &command)
        {
            //mutex1_.lock();
            //std::lock_guard<mutex> guard1(mutex1_);
            //std::lock(mutex1_, mutex2_);
            //std::lock_guard<mutex> guard1(mutex1_, std::adopt_lock);
            //std::lock_guard<mutex> guard2(mutex2_, std::adopt_lock);

            std::unique_lock<mutex> guard1(mutex1_, std::try_to_lock);

            std::chrono::milliseconds dura(2000);
            std::this_thread::sleep_for(dura);
            if(!list_.empty())
            {
                int command = list_.front();
                list_.pop_front();
                //mutex1_.unlock();
                //mutex2_.unlock();

                return true;
            }
            //mutex1_.unlock();
            //mutex2_.unlock();

            return false;
        }

        void output()
        {
            int command = 0;
            for (int i = 0; i < 100000; i++)
            {
                bool result = output_proc(command);
                if (true == result)
                {
                    std::cout << "取出了一个元素" << std::endl;
                }
                else
                {
                    std::cout << "消息队里为空" << std::endl;
                }
                
            }
        }
    private:
        std::list<int> list_;
        std::mutex mutex1_;
        std::mutex mutex2_;
    
    };

    void func()
    {
        A obj;
        std::thread input_thread(&A::input, &obj);
        std::thread output_thread(&A::output, &obj);
        input_thread.join();
        output_thread.join();

        std::cout << "线程结束" << std::endl;
    }

}
// 一: unique_lock取代lock_guard
// unique_lock是个类模板，工作上一般lock_guard（推荐使用）；lock_gurad取代mutex
//的lock和unlock；
// unique_lock比lock_guard灵活很多；效率上差点，内存上多占用多一点。
// 二:unique_lock的第二个参数

// (2.1)std::adopt_lock：表示这个互斥量已经被lock了（你必须要把互斥量提前lock，否则会报异常）
// 不希望unique_lock的构造函数中lock这个mutex。
// 用这个adopt_lock的前提是，你需要自己先把mutex先lock上；

// (2.2)std::try_to_lock
// 我们会尝试用mutex的lock()去锁定这个mutex，但如果没有锁成功，我们也会立即返回，
//并不会阻塞在哪里
// 用这个try_to_lock的前提是不能直接先去lock。

// (2.3)std::defer_lock
// 用这个defer_lock的前提是 你不能自己先去lock，否则会报异常
// defer_lock的意思是没有给mutex加锁，初始化一个没有加锁的mutex。
// 我们借着defer_lock的话题，来介绍unique_lock的重要成员函数。

// 三：unqiue_lock的成员函数
// (3.1) lock(), 加锁
// (3.2) unlock(), 解锁
// (3.3) try_lock()尝试给互斥量加锁，如果拿不到锁，则返回false，如果拿到锁了，返回true，
// 这个函数不阻塞；
// (3.4) release()，返回所管理的mutex对象指针，并释放所有权；也就是说，这个unique_lock
// 和mutex不再有关系。
// 严格区分unlock和release的区别，不要混淆。
// 为如果原来mutex对象处于加锁状态，你有责任接管过来并负责解锁。release返回原始mutex指针
// 为什么有时候需要unlock()；因为你lock锁住的代码段越少，执行越快，整个程序运行效率越高。
// 有人把锁头锁住的代码多少称为锁的粒度 粒度一般用粗细描述；
// a)锁住的代码少，这个粒度叫细，执行效率高；
// b)锁住的代码多，粒度叫粗，执行效率低；
// 要学会尽量选择合适粒度的代码进行保护，粒度太细可能漏掉共享数据保护，粒度太粗影响效率。
// 选择合适的粒度，是高级程序员的能力和实力的体现

// 四: unique_lock所有权的传递
// std::unique_lock<std::mutex> guard1(mutex1_);   所有权概念
// guard1拥有mutex1_的所有权
// guard1可以把自己对mutex的所有权转移给其他的unique_lock对象；
// 所以，unique_lock对象这个所有权是属于可以移动，但是不能复制

// a) std::move
// b) return std::unique_lcok(std::mutex)

#endif