#pragma once

#include <iostream>
#include <string>
//#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <array>

using namespace std;

namespace _nmsp1
{
    //stl的组成部分：
    //容器，迭代器，算法（函数），分配器（分配内存），其他（适配器，仿函数/函数对象等等）

    //一：容器的分类 
    //vector,list,map，容器是保存数据的
    //STL中的容器分为三大类：
    //(1)顺序容器（sequence Containers)：放进去在哪里，这个元素就排在哪里。比如array,vector,deque,list,forward_list；
    //(2)关联容器（Associative Containers)：树，哈希表，元素是 键/值 对 ，特别适合做查找。你能控制插入的内容，但一般来讲你不能控制插入的位置。 set，multiset，map,multimap;
    //hash_set,hash_map,hash_multiset,hash_multimap;	 
    //(3)无序容器（Unordered Containers）：c++11里推出：元素的位置不重要，重要的是这个元素是否在这个容器里边。
    //无序容器他也属于一种关联容器；哈希表来实现；
    //unordered_set,unordered_multiset,unordered_map,unordered_multimap；
    //哈希表：蓝色块 叫 篮子（桶子）；
    //官方有一句话：c++标准并没有规定任何容器必须使用任何特定的实现手段。

   


    void func()
    {

        return;
    }
}
namespace _nmsp2
{
    //二：容器的说明和应用事项例
    //(2.1)array：是个顺序容器，其实是个数组，内存空间是连续的，大小是固定的；你刚开始申请的时候是多大，他就是多大，不能再增加他的大小了；

    void func()
    {
        //包含5个元素的数组
        array<string, 5> mystring = { "I","Love1Love2Love3Love4Love5Love6Love7","China" };
        cout << "myString.size() = " << mystring.size() << endl; //5
        mystring[0] = "It is very long~~~~~~~~~~~~~long~~~~~~~~~~~~long";
        mystring[4] = "It is very long~~~~~~~~~~~~~long~~~~~~~~~~~~long";
        cout << "sizeof(string) = " << sizeof(string) << endl;
        for (size_t i = 0; i < mystring.size(); ++i)
        {
            const char *p = mystring[i].c_str();
            cout << "-----------------begin---------------------" << endl;
            cout << "数组元素值= " << p << endl;
            printf("对象地址=%p\n", &mystring[i]);
            printf("指向的字符串地址=%p\n", p);
            cout << "-----------------end---------------------" << endl;
        }

        const char *p1 = "Love1Love2Love3Love4Love5Love6Love7";
        const char *p2 = "Love1Love2Love3Love4Love5Love6Love7";
        printf("p1地址=%p\n", p1);
        printf("p2地址=%p\n", p2);






    }
}
namespace _nmsp3
{
    //（2.2）vector
    //a)往屁股后边增加元素和从屁股删除元素都很快； push_back();
    //b)往中间插入元素可能导致很多后续的元素要执行重新构造，析构。效率会非常之低
    //c)查找速度应该不会太快；

    //vector容器内存也是挨着的， vector容器有一个 “空间”的概念，每一个空间可以装一个元素；
    //容器里有多少个元素可以用size()来看，而这个容器里有多少空间，可以 用capacity();
    //capacity()一定不会小于size();vector容器中空间的数量一定不会小于元素的数量；
    //用reverse可以预留空间，前提是你预先知道这个容器最多会容纳多少个元素；可以大量的提高程序的运行效率；


    class A
    {
    public:
        int m_i;
        A(int tmpv) :m_i(tmpv)//构造函数
        {
            cout << "A::A()构造函数执行" << endl;
        }
        A(const A& tmpA)
        {
            m_i = tmpA.m_i;
            cout << "A::A()拷贝构造函数执行" << endl;
        }
        ~A()
        {
            cout << "A::~A()析构函数执行" << endl;
        }
    };

    void func()
    {
        vector<A> myveca;
        cout << "myveca.capacity() = " << myveca.capacity() << endl;
        cout << "myveca.size() = " << myveca.size() << endl;

        myveca.reserve(10); //预留10个空间

        cout << "myveca.capacity() = " << myveca.capacity() << endl;
        cout << "myveca.size() = " << myveca.size() << endl;


        for (int i = 0; i < 5; ++i)
        {
            cout << "-----------begin-------------" << endl;
            cout << "容器插入元素之前size=" << myveca.size() << endl;
            cout << "容器插入元素之前capacity=" << myveca.capacity() << endl;

            myveca.push_back(A(i));

            cout << "容器插入元素之后size=" << myveca.size() << endl;
            cout << "容器插入元素之后capacity=" << myveca.capacity() << endl;
            cout << "-----------end---------------" << endl;
        }

        cout << "--------------------------------------------------------" << endl;
        for (int i = 0; i < 5; ++i)
        {
            printf("下标为%d的元素的地址是%p,m_i=%d\n", i, &myveca[i], myveca[i].m_i);
        }
        //printf("myveca地址是%p\n", &myveca);
        cout << "---------------------------------删除一个元素看看-----------------------" << endl;
        int icount = 0;
        for (auto pos = myveca.begin(); pos != myveca.end(); ++pos)
        {
            icount++;
            if (icount == 2)
            {
                myveca.erase(pos);
                break;
            }
        }
        for (int i = 0; i < 4; ++i)
        {
            printf("下标为%d的元素的地址是%p,m_i=%d\n", i, &myveca[i], myveca[i].m_i);
        }

        {
            cout << "---------------------------------插入一个元素看看-----------------------" << endl;
            int icount = 0;

            for (auto pos = myveca.begin(); pos != myveca.end(); ++pos)
            {
                icount++;
                if (icount == 2)
                {
                    myveca.insert(pos, A(10));
                    break;
                }
            }
        }
        for (int i = 0; i < 5; ++i)
        {
            printf("下标为%d的元素的地址是%p,m_i=%d\n", i, &myveca[i], myveca[i].m_i);
        }

    }
}



namespace run_62
{
    int main()
    {
        //_nmsp1::func();	
        //_nmsp2::func();
        _nmsp3::func();
        return 1;
    }
}



