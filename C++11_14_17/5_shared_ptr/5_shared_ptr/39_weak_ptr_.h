#pragma once

#include <memory>
#include <iostream>
using namespace std;

namespace weak_ptr_
{
    void main()
    {
        // weak_ptr概述：辅助shared_ptr进行工作
        // 强 shared_ptr, 弱weak_ptr
        // weak_ptr：也是个类模板，一个智能指针，指向一个shared_ptr管理的对象，但是weak_ptr不控制所指向对象的生命周期
        // 换句话说，将weak_ptr绑定到shared_ptr上不会改变shared_ptr的引用计数（更确切的说，weak_ptr的构造和析构不会增加或减少所指向对象的的引用计数）
        // 当shared_ptr需要释放所指定的时候照常释放，不管是否有weak_ptr指向该对象
        // 控制不了所指向对象的生命周期

        // 弱引用的作用：大家可以理解成监视shared_ptr的生命周期用，是一种对shared_ptr能力的扩充。
        // weak_ptr不是一种独立的智能指针，不能用来操作所指向的资源，所以它看起来像是一个shared_ptr的助手。
        // weak_ptr能够监视它所指向的对象是否存在

        // (1.1)weak_ptr创建
        // 我们创建一个weak_ptr的时候，一般都用一个shared_ptr来初始化；
        //auto pi = make_shared<int>(100);
        //weak_ptr<int> piw(pi);  // piw弱共享屁，pi强引用计数不会改变，但是弱引用计数会从0变为1
        //// 强引用计数才能决定对象的生命周期，弱引用计数对生命周期没有影响
        //weak_ptr<int> piw2(piw);

        //// lock()：功能是检查weak_ptr所指向 的对象是否存在，如果存在，那么这个lock他就会返回一个指向该对象的shared_ptr（指向对象的强引用计数加一）
        //// 如果所指向的对象不存在，lock返回一个空的shared_ptr

        //pi.reset();   // 因为pi是唯一指向该对象的强引用指针，所以reset会释放pi所指向的对象，同时将pi置空
        //auto pi2 = piw.lock();
        //if(pi2 != nullptr)
        //{
        //
        //}
        //else
        //{

        //}

        // 总结上面的这段代码：weak_ptr能够判断所指向的对象是否存在

        // weak_ptr常用操作
        // （2.1）use_count:获取与该弱指针所共享的shared_ptr的数量，或者说获得当前所观测资源的强引用计数
        //auto pi = make_shared<int>(100);
        //auto pi2(pi);
        //weak_ptr<int> piw(pi);
        //int isc = piw.use_count();

        // (2.2)expired():是否过期，弱指针的use_count()返回0 表示该指针所指向的对象不存在了，则返回true，否则返回false
        // 换句话说，这个函数用来判断所观测的资源是否被释放
 /*       pi.reset();
        pi2.reset();
        if(piw.expired())
        {
            cout << "已经过期" << endl;
        }
*/
        // (2.3)reset()：将该弱指针置为空，不会影响指向该对象的强引用数量，但指向该对象的弱引用数量会减少1


        // （2.4）lock()
        //auto p1 = make_shared<int>(100);
        //weak_ptr<int> ptw(p1);
        //if(!ptw.expired())
        //{
        //    auto p2 = ptw.lock();

        //}

        // 尺寸问题
        // weak_ptr和shared_ptr一样大，裸指针的两倍
        // 第一个裸指针指向的是这个智能指针所指向的对象
        // 第二个裸指针指向一个很大的数据结构(控制块)，这个控制块里有：
        // 1.有所指向对象的强引用计数
        // 2.所指向对象的弱引用计数
        // 3.其他数据，比如自定义的删除器等等

        return;
    
    }


}