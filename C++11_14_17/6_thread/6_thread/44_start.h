﻿#pragma once
#include <thread>
#include <iostream>
using namespace std;

void myprint()
{
    cout << "我的线程开始执行了" << endl;
}

class TA
{
public:
    int &i_;
    TA(int &i) :i_(i) 
    {
        cout << "构造函数执行" << endl;
    }
    TA(const TA &ta):i_(ta.i_)
    {
        cout << "拷贝构造函数" << endl;
    }
    ~TA()
    {
        cout << "析构函数" << endl;
    }
    void operator()()
    {
        cout << "i_的值为"<< i_ << endl;  // 产生不可预料的结果
    }
};
namespace start_
{
    int main()
    {
        // 一：范例演示线程运行的开始和结束
        // 程序运行起来，生成一个进程，该进程所属的主线程开始自动运行；
        // 主线程从main()开始执行，那么我们自己创的线程，也需要一个函数开始运行，一旦这个函数运行完毕，就代表我们这个线程运行结束。
        // 整个进程是否执行完毕的标志是主线程是否执行完，如果主线程执行完了，就代表整个进程执行完毕了
        // 此时，一般情况下：如果其他子线程没有执行完毕，那么子线程也会被操作系统强行终止
        // 所以，一般情况下，我们得到一个结论：如果大家想保持子线程的运行状态，那么大家就要让主线程一直保持运行，不要让主线程运行完毕。


        // a)包含一个头文件thread
        // b)初始函数
        // c)main中写代码
        // 大家明确一点：有两个线程在跑，相当于整个程序的执行有两条线在同时走，所以可以同时干两个事，即使一条线被堵住了，另外一条线还是可以可以通行的。这就是多线程
        // (1.1)thread：是标准库里面的类
        
        // (1.2)join()：加入/汇合，说白了就是阻塞，阻塞主线程，让主线程等待子线程执行挖泥巴，然后子线程和主线程汇合。然后主线程再往下走
        // 通常情况下如果主线程执行完毕，但子线程没有执行完毕，这种程序员是不合格的，程序也是不稳定的。
        // 一个书写良好的程序，应该是主线程等待子线程执行完毕后，自己才能退出。
        
        // (1.3)detach()：传统的多线程程序主线程要等待子线程执行完毕，然后自己在退出；
        // detach:分离，也就是主线程不和子线程汇合，主线程执行你的，不必等待我子线程运行结束
        // 为什么引入detach：我们创建了多个子线程，让主线程逐个等待子线程结束，这种编程方法不太好，所以引入了detach
        // 一旦detach之后，与这个主线程关联的thread对象就会失去与这个主线程的关联，此时子线程就会驻留在后台运行
        // 这个子线程就相当于被C++运行时库接管，当这个线程完毕后，由运行时库负责清理该线程的相关资源。
        // detach使线程失去了我们自己的控制。

        // (1.4)joinable():判断是否可以使用join或者detach的；返回true或者false
        //thread obj(myprint);  // 创建了线程，线程的入口是myprint  (2)myprint线程开始执行
        //if (obj.joinable())
        //    cout << "joinable:true" << endl;
        //obj.join();  // 主线程阻塞到这里等待myprint执行完毕，当子线程执行完毕，这个join执行完毕，主线程继续往下走。
        //obj.detach();  // 一旦调用detach，就不能再用join，否则系统报告异常
        //if (obj.joinable())
        //    cout << "joinable:true" << endl;
        //else
        //    cout << "joinable:false" << endl;


        // 二：其他创建线程的手法
        // (2.1)用类对象(可调用对象)以及一个问题范例
        // 大家可能还有一个疑问：一旦detach，那我主线程执行结束了，我这里用的ta这个对象还在吗？(对象不在了)
        // 这个对象实际上是被赋值到线程中去了，所以执行完主线程后，ta会被销毁，但是复制的TA对象依旧在的。
        // 所以，只要这个TA对象里面没有指针，引用那么就不会产生问题。
        //int i = 6;
        //TA ta(i);
        //thread obj(ta);
        //obj.join();
        //obj.detach();

        // (2.2)用lambda表达式
         /*     auto mylambda = [] {
            cout << "thread start" << endl;
        };

        thread obj4(mylambda);
        obj4.join();*/
        return 0;
    }


}
