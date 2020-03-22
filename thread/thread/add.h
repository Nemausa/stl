//////////////////////////////////////////////////////////////////////////
//  @file     add.h
//  @author   Morris
//  @date     2019-02-17
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-17
//  -added 
//  @remark   多线程求和
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef ADD_H
#define ADD_H

#include <iostream>
#include <algorithm>
#include <thread>
#include <numeric>
#include <vector>
#include <functional>
using namespace std;

namespace add
{
    vector<int> vec;

    struct accumulate_block {
        void operator() (vector<int>::iterator first, vector<int>::iterator last, int &result) {
            result = std::accumulate(first, last, result);
        }

    };

    int multithreadSort(int init)
    {
        const long length = distance(vec.begin(), vec.end());
        if (length == 0) {
            return init;
        }
        unsigned long const min_per_thread = 25;//每个线程的子序列大小  
        unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;//计算线程数(向上取整)  
        unsigned long const hardware_threads = thread::hardware_concurrency();//获取PC的CPU core数目，C++库可能无法访问该信息，所以可能返回0  
        unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);//最大线程数为最大线程数和硬件core数目中取较小者(线程数超过core数目反而降低性能)  
        unsigned long const block_size = length / num_threads;//重新计算每个线程需要执行的序列大小  
        vector<thread> threads(num_threads - 1);
        vector<int> results(num_threads);//每个线程的结果将保存在results中  
        vector<int>::iterator block_start = vec.begin();
        for (size_t i = 0; i < (num_threads - 1); i++) {//这里只分配子线程的任务序列,主线程也会执行一个排序任务
            auto block_end = block_start;
            advance(block_end, block_size);
            threads[i] = thread(accumulate_block(), block_start, block_end, std::ref(results[i]));//每个子线程的子序列分配  
            block_start = block_end;//更新序列位置  
        }
        accumulate_block mainAccu;
        mainAccu(block_start, vec.end(), results[num_threads - 1]);
        std::for_each(threads.begin(), threads.end(), std::mem_fn(&thread::join));//等待子线程完成  
        return std::accumulate(results.begin(), results.end(), init);

    }

    int function() {

        for (int i = 0; i < 103; i++) {
            vec.push_back(i);
        }
        int sum = multithreadSort(50);
        cout << "Sum is ： " << sum << endl;
        system("pause");
        return 0;
    }

}





#endif