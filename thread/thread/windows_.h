
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

#ifndef WINDOWS_H
#define WINDOWS_H

#include <mutex>
#include <iostream>
#include <thread>
#include <list>
using namespace std;
#include <windows.h>

//#define __WINDOWSJQ_




namespace windows_
{

    //本类用于自动释放windows下的临界区，防止发生思锁，类似于C++11 lock_guard
    class CWinLock // RAII类 Resouce acquistion is initialization 资源获取即初始化
                   // 智能指针，容器都属于RAII类
    {
    public:
        CWinLock(CRITICAL_SECTION *pCritmp)
        {
            m_pCritical = pCritmp;
            EnterCriticalSection(m_pCritical);
        }
        ~CWinLock()
        {
            LeaveCriticalSection(m_pCritical);
        }
    private:
        CRITICAL_SECTION *m_pCritical;

    };

    class A
    {
    public:
        void input()
        {
            for (int i = 0; i < 100000; i++)
            {
                std::cout << "插入数据：" << i << std::endl;
                
#ifdef __WINDOWSJQ_
               // EnterCriticalSection(&my_winsec);
                //EnterCriticalSection(&my_winsec);
                CWinLock wlock(&my_winsec);
                list_.push_back(i);
               // LeaveCriticalSection(&my_winsec);
               // LeaveCriticalSection(&my_winsec);
#else
                //mutex1_.lock();
                //lock_guard<recursive_mutex> guard1(mutex1_);
                std::chrono::milliseconds timeout(100);

               // if(mutex1_.try_lock_for(timeout))
                if(mutex1_.try_lock_until(chrono::steady_clock::now() +timeout))
                {
                    // 在这100毫秒之内拿到锁
                    list_.push_back(i);
                    mutex1_.unlock();
                }
                else
                {
                    std::chrono::milliseconds sleeptime(100);
                    std::this_thread::sleep_for(sleeptime);
                }

                
#endif
                

            }
        }

        bool output_proc(int &command)
        {
#ifdef __WINDOWSJQ_
            EnterCriticalSection(&my_winsec);

            if (!list_.empty())
            {
                int command = list_.front();
                list_.pop_front();
                LeaveCriticalSection(&my_winsec);
                return true;
            }
            LeaveCriticalSection(&my_winsec);


#else
            mutex1_.lock();
           
            if (!list_.empty())
            {
                int command = list_.front();
                list_.pop_front();
                mutex1_.unlock();
                return true;
            }
            mutex1_.unlock();
#endif     

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
        A()
        {
#ifdef __WINDOWSJQ_
            InitializeCriticalSection(&my_winsec);  // 临界区要先初始化
#endif // __WINDOWSJQ_

        }
    private:
        std::list<int> list_;
        //std::mutex mutex1_;
        //std::recursive_mutex mutex1_;
        std::timed_mutex mutex1_;
        std::mutex mutex2_;

#ifdef __WINDOWSJQ_
        CRITICAL_SECTION my_winsec; // windows的临界区，非常类似于C++11中的mutex
#endif
    };

    void main()
    {
        // 在C++11中不允许mutex lock多次
        // recursive_mutex递归的独占互斥量,允许同一个线程，同一个互斥量多次被lock
        // timed_mutex和recursive_timed_mutex,
        // try_lock_for() ：等待一段时间 如果拿到锁或者超过等待时间，流程走下来
        // try_lock_until() :参数是一个未来的时间点，在这个未来的时间

        A obj;
        std::thread input_thread(&A::input, &obj);
        std::thread output_thread(&A::output, &obj);
        input_thread.join();
        output_thread.join();

        std::cout << "线程结束" << std::endl;
    }

}


#endif