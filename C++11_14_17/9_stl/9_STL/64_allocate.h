#pragma once

#include <iostream>
#include <queue>
#include <forward_list>
#include <map>
#include <unordered_set>
using namespace std;
namespace allocate_64
{
    //一：分配器概述：和容器紧密关联，一起使用	
    //每次malloc()，都浪费大量内存。
    //确切的说：内存分配器,扮演内存池的角色，通过大量减少对malloc()的调用，来节省内存，甚至还有一定的分配效率的提高；
    //经过测试，allocator这个c++标准库提供的缺省的内存分配器压根就没有采用内存池的工作机制。估计底层原封不动的调用了malloc()；




    void func1()
    {
        //vector<int,
        //list<int> mylist;
        //list<int, std::allocator<int> > mylist;
        //typename = _Alloc = allocator<....> 一个分配器

        list<int> mylist; //双向链表，内存不要求挨着；
        mylist.push_back(10);
        mylist.push_back(20);
        mylist.push_back(36);
        for (auto iter = mylist.begin(); iter != mylist.end(); ++iter)
        {
            cout << *iter << endl;
            int *p = &(*iter);
            printf("%p\n", p);
        }
        mylist.pop_back(); //干掉36
                           //int *psuibian = new int(100);

        return;
    }

    //二：分配器的使用
    //allocator分配器，是个类模板，我们写代码时极少会直接用到这个allocator这种容器的分配器；
    //但从语法上来讲，allocator分配器是能够被直接编码使用的
    void func2()
    {
        //list<int,
        allocator<int> aalloc; //定义一个aalloc对象，为类型为int的对象分配内存
        int *p = aalloc.allocate(3);  //allocate()是分配器中的重要函数，用来分配一段原始的未构造的内存。
                                      //这段内存能保存3个类型为int的对象（12字节）；
        int *q = p;
        *q = 1; q++;
        *q = 2; q++;
        *q = 3;

        aalloc.deallocate(p, 3); //deallocate()也是分配器中的重要函数，用于释放内存，你需要记住分配了几个对象，释放时要释放正确数量的对象；

    }

    //三：其他的分配器及原理说
    //linux GNU c++(gcc,g++)

    //四：自定义分配器（自己写分配器），代码繁琐，并不好写；



    void func3()
    {
        list <int, allocator<int>> mylist1;
        list <double, allocator<double>> mylist2;

    }


    int main()
    {
        func1();	
        func2();
        func3();
        return 1;
    }
}

   

