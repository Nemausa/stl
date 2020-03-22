//////////////////////////////////////////////////////////////////////////
//  @file     async_.h
//  @author   Morris
//  @date     2019-02-21
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-21
//  -added 
//  @remark   异步任务
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef ASYNC_H
#define ASYNC_H

#include <iostream>
#include <string>
#include <mutex>
#include <list>
#include <future>
#include <vector>

namespace async_
{
    class A
    {
    public:
        int  mythread(int mypar)
        {
            std::cout << mypar << std::endl;
            std::cout << "mythread start thread id " << std::this_thread::get_id() << std::endl;
            std::chrono::milliseconds dura(5000);
            std::this_thread::sleep_for(dura);
            std::cout << "mythread end thread id " << std::this_thread::get_id() << std::endl;
            return 5;
        }
    };
    

    int  mythread(int mypar)
    {
        std::cout << mypar << std::endl;
        std::cout << "mythread start thread id " << std::this_thread::get_id() << std::endl;
        std::chrono::milliseconds dura(5000);
        std::this_thread::sleep_for(dura);
        std::cout << "mythread end thread id " << std::this_thread::get_id() << std::endl;
        return 5;
    }

    void mypromise(std::promise<int> &tmp, int calc)
    {
        // 做一些复杂的操作
        calc++;
        calc *= 10;
        std::chrono::milliseconds dura(5000);
        std::this_thread::sleep_for(dura);

        // 终于计算出结果
        int reuslt = calc;
        tmp.set_value(calc);  // 结果保存到了tmp对象中

        return;
    }

    void mypromise2(std::future<int> &tmp)
    {
        auto result = tmp.get();
        std::cout << "mythread2 result " << result << std::endl;
        return;
    }


    std::vector< std::packaged_task<int(int)>> vec_;
    int func()
    {
        // 一：std::async、std::future创建后台任务并返回值
        // 希望线程返回一个结果
        // std::async是个函数模板，用来启动一个异步任务，启动起来一个异步任务后，返回
        // 一个std::future对象，std::future是个类模板。
        // 什么叫启动一个异步任务，就是创建一个线程并开始执行对应线程的入口函数，它返回
        // 一个std::future对象里面就含有线程入口函数返回的结果（线程返回的结果）
        // 我们可以通过调用future对象的成员函数get()来获取结果
        // 我们通过额外想std::async传递一个参数,该参数是std::lannch类型（枚举类型）
        // 来达到一些特殊的目的

        // a)std::lunnch::deferred：线程入口函数调用被延迟到std::future或者wait函数
        // 调用时才执行；
        // 如果wait或get没有调用，线程会执行吗? 不执行
        // std::lunnch::deferred:延迟调用，并且没有创建线程，是在主线程中调用线程
        // 入口函数

        // b)std::launch::async,在调用函数的时候开始创建线程
#if 0
        A a;
        int tmppar = 12;

        std::cout << "main thread id " << std::this_thread::get_id() << std::endl;
        //std::future<int> result = std::async(mythread);
        std::future<int> result = std::async(std::launch::deferred, &A::mythread, &a, tmppar);
        std::cout << "continue...!" << std::endl;
        int def;
        def = 0;

        // 等待线程返回，并不返回结果
        //result.wait();  

        // 卡在这里等待线程执行完毕，拿到结果,只能调用一次

        std::cout << result.get() << std::endl;

        std::cout << "I love China" << std::endl;
#endif
       
        // 二：std::packaged_task：打包任务，把任务打包起来
        // 是个模板类，它的模板参数是各种可调用对象，通过std::packaged_task来把各种
        // 可调用对象包装起来，方便将来作为线程入口函数
#if 0
      

        std::cout << "main thread id " << std::this_thread::get_id() << std::endl;

        // 我们把函数通过packaged_task包装起来
        //std::packaged_task<int(int)> mypt(mythread); 

        // lambad函数
        std::packaged_task<int(int)> mypt([](int mypar)->int
        {
            std::cout << mypar << std::endl;
            std::cout << "mythread start thread id " << std::this_thread::get_id() << std::endl;
            std::chrono::milliseconds dura(5000);
            std::this_thread::sleep_for(dura);
            std::cout << "mythread end thread id " << std::this_thread::get_id() << std::endl;
            return 5;
        });

        //std::thread t1(std::ref(mypt), 1);
        //t1.join();
        //std::future<int> result = mypt.get_future();
        //std::cout << result.get() << std::endl;
        //std::cout << "I love China" << std::endl;
        vec_.push_back(std::move(mypt));
         
        std::packaged_task<int(int)> mypt2;
        auto iter = vec_.begin();
        mypt2 = std::move(*iter);  // 移动语意
        vec_.erase(iter);  // 删除第一个元素，迭代已经失效，后续代码不可以使用
        mypt2(123);
        std::future<int> result = mypt2.get_future();
        std::cout << result.get() << std::endl;
#endif

        // 三：std::promise，类模板
        // 我们能够在线程中赋值，然后在其他的线程中取出来用
        // 四：小结：到底怎么用 声明时候用
        // 我们学习这些东西的目的，并不是把他们全部用在实际的开发中
        // 相反，如果我们用最少的东西能够写出一个稳定、高效的多线程，更值得赞赏
        // 我们为了成长，必须阅读一些高手的代码，从而快速实现自己的代码积累，技术就会有
        // 个大幅度的提升，为以后的阅读大师的代码铺路。
#if 1
        std::promise<int> prom;  // 声明一个对象，保存值为int类型
        std::thread t1(mypromise, std::ref(prom), 180);
        t1.join();

        // 获取结果值
        std::future<int> ful = prom.get_future();
        //std::cout << "result= " << result.get() << std::endl;

        std::thread t2(mypromise2,std::ref(ful));
        t2.join();

        std::cout << "I love China" << std::endl;
#endif

        return 0;
    }

}


#endif