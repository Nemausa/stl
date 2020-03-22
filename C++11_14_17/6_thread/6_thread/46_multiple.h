
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

#ifndef MULITIPLE_H
#define MULITIPLE_H

#include <iostream>
using namespace std;
#include <thread>
#include <vector>
#include <list>
#include <string>
#include <map>

vector<int> g_v = { 1,2,3 };

class MA
{
public:
    // 把收到的消息放入到一个队列
    void send()
    {
        for (int i = 0; i < 100000; ++i)
        {
            cout << "push  " << i << endl;
            queue_.push_back(i);  // 假设这个数字i就是我们收到的命令，直接弄到消息队列中
        }
    }

    void receive()
    {
        for (int i = 0; i < 100000; ++i)
        {
            if(!queue_.empty())
            {
                int command = queue_.front();
                queue_.pop_front();  // 移除第一个元素，不返回
            }
            else
            {
                cout << "队列为空" << i<< endl;
            }
        }
    }
private:
    list<int> queue_;  // 容器，专门用于代表玩家发送的命令
};

namespace mulitiple
{

    void myprint(int i)
    {
        cout << "线程执行了 id="<<this_thread::get_id()<< "gv的值= "<<g_v[0]<<g_v[1]<<g_v[2] << endl;
        return;
    }

    int main()
    {
        // 一：创建和等待多个线程
        vector<thread> threads;
        // 创建10个线程
        // a)多个线程的执行顺序是乱的，跟操作的系统内部的运行调度机制有关
        // b)主线程等待所有的子线程结束，最后主线程结束，老师推荐join的写法，更容易写成稳定的程序
        // c)把线程放入到容器中管理，看起来像个thread数组，这对我么一次性创建大量的线程并对大量的线程方便管理。
        //for (int i = 0; i < 10; ++i)
        //    threads.push_back(thread(myprint, i));
        //
        //for (auto iter = threads.begin(); iter != threads.end(); ++iter)
        //    iter->join();

        // 二：数据共享问题
        // (2.1)只读数据：是安全稳定的，不需要什么特别的处理，直接读就可以了
        // (2.2)有读有写：要特别处理，最简单的处理，读的时候不能写，写的时候不能读了。
        // (2.3)其他案例
        // 数据共享 订票问题

        // 三：共享数据的保护案例代码
        // 网络服务器，有两个线程，一个线程收集玩家的命令，另一个线程从队列中取出玩家发送的命令

        MA obj;
        std::thread send_thread(&MA::send, &obj);  // 第二个参数是引用
        std::thread receive_thread(&MA::receive, &obj);
        send_thread.join();
        receive_thread.join();



        cout << "I Love China" << endl;
        return 0;
    }

}



#endif