//////////////////////////////////////////////////////////////////////////
//  @file     async_.h
//  @author   Morris
//  @date     2019-02-21
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-21
//  -added 
//  @remark   异步任务测试程序
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef ASYNCTEST_H
#define ASYNCTEST_H

#include <iostream>
#include <string>
#include <mutex>
#include <list>
#include <future>
#include <vector>

namespace async_test
{
    class A
    {
    public:
        void mypromise1(std::promise<int> &tmp, int calc)
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

        void mypromise2(std::promise<int> &tmp, int calc)
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

        void mypromise3(std::promise<int> &tmp, int calc)
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

        void result(std::future<int> &tmp1, std::future<int> &tmp2, std::future<int> &tmp3)
        {
            auto result1 = tmp1.get();
            auto result2 = tmp2.get();
            auto result3 = tmp3.get();
            std::cout << "result " << result1+result2+result3 << std::endl;
            return;
        }
    
    };

    void func()
    {
        clock_t start, end;
        start = clock();
        A a;
       
        std::promise<int> prom1, prom2, prom3;  // 声明一个对象，保存值为int类型
        std::thread t1(&A::mypromise1, &a, std::ref(prom1), 9);
        std::thread t2(&A::mypromise1, &a, std::ref(prom2), 9);
        std::thread t3(&A::mypromise2, &a, std::ref(prom3), 9);

        std::future<int> f1 = prom1.get_future();
        std::future<int> f2 = prom2.get_future();
        std::future<int> f3 = prom3.get_future();
        std::thread t4(&A::result, &a, std::ref(f1), std::ref(f2), std::ref(f3));

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        end = clock();

        double dur = (double)(end - start);
        printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));
        
       
    
    }

}


#endif