#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string>
#include <memory>
using namespace  std;

class A
{
public:
    A()
    {
        cout << "A()构造函数" << endl;
    }

    ~A()
    {
        cout << "~A()析构函数" << endl;
    }

};

void myfunc(shared_ptr<int> ptmp)
{
    return;
}


namespace shared_ptr_
{
    
    void main()
    {
#if 0

        // 一：new/delete(关键字/运算符)探秘
        // sizeof(关键字/运算符),不是函数
        // mallco free(这样用于C语言编程中)new/delete用于C++编程：这两对都用于动态的在堆中分配/释放内存
        // new/delete比mallco/free干的事情更多
        //A *pa = new A();  // 构造函数被调用
        //delete pa;  // 析构函数被调用

        // new/delete具备对堆上所分配内存进行初始化/释放（反初始化）的能力，而这些能力是malloc/free所不具备的。
        // (1.2)operator new 和 operator delete():函数
        //int *pi = new int;
        //delete pi;
        // new干了两件事情：(a)分配内存(通过operator new()来分配内存) (b)调用构造函数初始化内存
        // delete也干了两个事情：(a)调用析构函数 (b)释放内存(调用operator delete()释放内存)

        // (1.3)基本new如何记录分配的内存大小供delete使用
        // 不同的编译器new内部有不同的实现方式；
        //int *p = new int;  // 4个字节
        //delete p;  // 删除的时候，编译器怎么知道要回收4个字节，new内部有记录机制，记录了分配多少内存

        //(1.4)申请和释放一个数组
        // A *pA = new A();  // 泄漏1一个字节
        //A *pA = new A[2](); // 这里泄漏的是6个字节，而不是2个字节，多出来的4个字节是干啥的。
        //int *p = new int[2]; // int 数组，有2个元素，泄漏8字节，没有多出来4个字节
        // 疑问：为什么动态类型A分配内存对象多出来4个字节，而给内置类型int动态分配内存对象数组时并没有多出来4个字节。
        // 用来记录需要析构多少次

        // new[] 应该使用delete[]释放
        //int *p = new int[3];

        //delete p;  //没有用[]，似乎也可以直接释放p这个int数组，没有发生内存泄漏
        //delete[]p;  // 这种释放才是规范的，没有任何问题

        //(1.5)为什么new/delete new[]/delete[]要配对使用
        // 内置类型比如int不用调用析构杉树，所以new[]的时候没有多分配4个字节。
        // 结论：如果一个对象，使用new[]来分配内存,却单独使用delete(而不是delete[])来
        // 释放内存，那么对象应该满足的几个条件
        // 对象的类型要么是内置类型或者无自定义的析构函数的类类型。
        // 如果没有析构函数，则不用记录需要析构多少次
        // A *pA = new A[2]();  // 如果么有析构函数，这里就分配2个字节
        // delete pA;  // 为什么字节一提供析构函数，不用delete[]来释放new[]出来的内存就报异常呢?
        // (a)调用一次析构函数而不是2次，至少是表示有内存泄漏
        // (b)调用operator delete（pA)释放内存


        // 二：智能指针综述
        // new/delete的写法要非常的小心，防止早早的释放，也防止忘记释放，总之用好不容易
        // p 裸指针：直接使用new返回的指针，这种指针强大灵活，但是开发者全程负责维护，一个不小心很容易出错，一旦用错后果严重
        // 智能指针：解决裸指针可能代码的各种问题
        // 智能指针就理解成"裸指针"精心包装，给裸指针外边包了一层，包装后为我们带来了优点
        // 最突出的优点：智能指针能够"自动释放所指向的对象内存",大家再也不用担心自己new出来的内存忘记释放了
        // 建议优选智能指针。使用智能指针的程序更容易编写和调试
        // C++标准库有四种智能指针 auto_ptr  unique_ptr shared_ptr weak_ptr
        // 帮助我们进行动态分配对象（new出来的对象)的生命周期的管理，能够有效防止内存泄漏
        // 目前auto_ptr已经完全被unique_ptr取代，不要使用auto_ptr，C++表中中反对使用auto_ptr(弃用)
        // 这三种智能指针都是类模板,我们可以将new或得的地址赋给他们
        // shared_ptr:共享式指针，多个指针指向同一个对象，最后一个指针被销毁时，这个对象会被释放。
        // weak_ptr是辅助shared_ptr工作的。
        // unique_ptr:独占式指针，同一个时间，只有一个指针指向该对象。
        // 当然该对象的所有权还是可以移交出去的
        // 你忘记delete的时候，智能指针帮助你delete，或者说你压根就不用再需要自己delete，智能指针的本分。


        // shared_ptr基础
        // 共享所有权 不是被一个shared_ptr拥有，而是被多个shared_ptr之间互相协作；shared_ptr有额外开销；
        // 工作原理：引用计数，每个shared_ptr的拷贝都指向相同的内存，所以只有租后一个指
        // 向该内存对象的shared_ptr才会去析构所指向的对象。
        // 最后一个指向该内存独享的shared_ptr在什么情况下回释放对象(shared_ptr所指向的对象呢？）
        // (a)这个shared_ptr析构的时候；
        // (b)这个shared_ptr指向其他的对象时；
        // 有点类似垃圾回收机制 我们从此不用担心何时delete
        // 格式：shared_ptr<指向的类型>智能指针名

        // (3.1)常规初始化(shared_ptr和new配合)
        // shared_ptr<int> pi; // 指向int的智能指针，名字为pi，但目前指向为空，空指针，nullptr
        //shared_ptr<int> pi(new int(100));
        //shared_ptr<int> pi2 = new int(100);  // 不行，这个智能指针是explicit，不可以隐式类型转换，必须用直接初始化。
        // 裸指针可以初始化shared_ptr，但不推荐。智能指针和 裸指针不能穿插使用；
        // int *pi = new int;
        // shared_ptr<int> p1(pi);

        // (3.2)make_share函数：标准库里的函数模板，安全，高效的分配和使用shared_ptr；
        // 它能够在动态内存中分配并初始化一个对象，然后返回指向此对象的shared_ptr
        shared_ptr<int> p2 = make_shared<int>(100);  // 这个shared_ptr指向一个值为100的整型内存，有点类似int *p = new int(100)
        shared_ptr<string> p3 = make_shared<string>(5, 'a'); // 5个字符a生成的字符串
                                                             // 类似于string mystr(5, 'a')

        shared_ptr<int> p4 = make_shared<int>(); // p4指向一个int，int里面保存的值为0（值初始化）
        p4 = make_shared<int>(100);  // p4指向一个新int，int里面保存的是100，p4首先释放刚才指向为0的内存，然后指向值为100的内存

        auto p5 = make_shared<string>(5, 'a');  // 用auto比较简单
#endif
       


    }

}