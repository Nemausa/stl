#pragma once
#include <iostream>
using namespace std;
#include <memory>



namespace shared
{
    //shared_ptr<int> myfunc(shared_ptr<int> &ptmp)  // 如果参数为引用，则智能指针的引用计数不会增加
    //{
    //    return ptmp;
    //}

    void myfunc(shared_ptr<int> ptmp)
    {
        return;
    }

    void mydelete(int *p)  // 我们的删除器，删除整型指针用的，当智能指针引用计数为0，就会调用这个删除器来删除对象
    {
        //写一些日志
        delete p;  // 既然你提供了删除器来取代智能指针的缺省删除器，那么就有义务自己来删除所指向的对象（引用计数为0时）
    }

    template<typename T>
    shared_ptr<T> make_shared_array(size_t size)
    {
        return shared_ptr<T>(new T[size], default_delete<T[]>());
    }

    void main()
    {
    
        // 一：shared_ptr引用计数的增加和减少
        // (1.1)引用计数的增加
        // 每个shared_ptr都会记录有多少个其他的shared_ptr指向相同的对象
        //auto p6 = make_shared<int>(100); // 目前p6所指向的对象只有p6一个引用者
        //auto p7(p6); // 智能指针定义时的初始化，p7和p6指向了相同的对象，此对象目前有两个引用者

        // 在如下的情况下，所有指向这个对象的shared_ptr引用计数都会增加1
        // (a)像上边那样，我们用p6来初始化p7这个智能指针
        // (b)把智能指针当做实参往函数里传递
        //myfunc(p6);
        // (c)作为函数返回值
        //auto p8 = myfunc(p6);  // 引用计数会变成3，这是因为p8来接这个临时智能指针
        //myfunc(p6);  // 如果没有来接这个临时智能指针，则临时智能指针生命周期到了，引用计数从3恢复到2

        // (1.2)引用计数的减少
        // (a)给shared_ptr赋予新值，让该shared_ptr指向新的对象
        //p8 = make_shared<int>(200);  // p8指向新对象，计数为1，p6,p7恢复为2
        //p7 = make_shared<int>(300);  // p7指向新对象，计数为1，p6指向的对象计数恢复为1
        //p6 = make_shared<int>(400);  // p6指向新对象，计数为1，p6指向的原内存被释放

        // (b)局部的shared_ptr离开其作用域
        // 当一个shared_ptr引用计数从1变成0，则他会自动释放自己所管理（指向）的对象
        //auto p9 = make_shared<int>(100); // 只有p9指向该对象
        //auto p10 = make_shared<int>(100); 
        //p9 = p10; // 给p9赋值会让p9指向p10所指向的对象，该对象的引用计数变为2，二原来p9所指向的对象引用计数变为0，从而导致被释放。

        // 二：shared_ptr的常用操作
        // (2.1)use_count()：返回多少个智能指针指向某个对象，主要用于调式目的；
        //shared_ptr<int> myp(new int(100));
        //int icoutn = myp.use_count();
        //shared_ptr<int> myp2(myp);
        //icoutn = myp.use_count();
        //shared_ptr<int> myp3;
        //myp3 = myp2;


        // (2.2)unique():是否该智能指针独占某个对象，也就是若只有一个智能指针指向某个对象，则unique()返回true
        //shared_ptr<int> myp(new int(100));
        //shared_ptr<int> myp2(myp);
        //if(myp.unique())
        //{
        //    cout << "unique ok" << endl;
        //}
        //else
        //{
        //    cout << "nonono" << endl;
        //}
        //
        // (2.3)reset():恢复（复位/重置）的意思
        // (a)reset不带参数
        // 若pi是唯一指向该对象的指针，那么释放pi所指向的对象，并将pi置空
        // 若pi不是唯一指向该对象的执行，那么不释放pi所指向的对象，但指向该对象的引用计数会减少1，同时将pi置空
        //shared_ptr<int> pi(new int(100));
        //pi.reset();
        //if (pi == nullptr)
        //    cout << "pi被置空";

        //shared_ptr<int> pi(new int(100));
        //auto p2(pi);
        //pi.reset();

        // (b)reset()带参数(一般是new出来的指针)
        // 若pi是唯一指向该对象的智能指针，则释放pi所指向的对象，让pi指向新对象
        // 若pi不是唯一指向该对象的指针，则不释放p所指向的对象，但指向该对象的引用计数减少1，同时让pi指向新对象
        //shared_ptr<int> pi(new int(100));
        //auto p2(pi);  // pi引用计数为2
        //pi.reset(new int(1));  // 释放内存，指向新内存

        //// 空指针也可以通过reset来重新初始化
        //shared_ptr<int> p;
        //p.reset(new int(100));  // 释放p所指向的对象，让p指向新的对象，因为原来p为空，所以就等于啥也没有释放，直接指向新的对象内存。

        // (2.4)*解引用：获取pi所指向的对象
        //shared_ptr<int> pother(new int(123456));
        //cout << *pother << endl;

        // (2.5)get():考虑到有些函数（第三方函数）的参数需要的是一个内置的裸指针而不是智能指针
        // p.get()：返回p中保存的指针(裸指针),小心使用，如果智能指针释放了所指向的对象，那么返回的裸指针也就变得没有意义了。
        //shared_ptr<int> myp(new int(100));
        //int *p = myp.get();
        //*p = 45;
        // delete p;  千万不要这么干，不然系统会报告异常，产生不可预料的后果

        // (2.6)swap()：交换两个指针所指向的对象
        //shared_ptr<string> ps1(new string("I love China1"));
        //shared_ptr<string> ps2(new string("I love China2"));
        //swap(ps1, ps2);
        //ps1.swap(ps2);

        // (2.7) = nullptr
        // (a)将所指向的对象引用计数减1，若引用计数为0，则释放智能指针所指向的对象。
        // (b)将智能指针置空
        //shared_ptr<string> ps1(new string("I love China1"));
        //shared_ptr<string> ps2(ps1);
        //ps1 = nullptr;

        // (2.8)智能指针名字作为判断条件
        //shared_ptr<string> ps1(new string("I Love China"));
        //ps1 = nullptr;
        //if (ps1)
        //{
        //    cout << "ps1指向一个对象" << endl;
        //}
        //else
        //{
        //    cout << "ps1为空" << endl;
        //}

        // (2.9)指定删除器以及数组问题
        // (a)指定删除器
        // 一定时机帮我们删除所指向的对象，delete：将delete运算符号作为默认的资源析构方式。
        // 我们可以指定自己的删除器取代系统提供的默认删除器，当智能指针需要删除所指向的对象时，
        // 编译器就会调用我们自己提供的删除器来删除；
        // shared_ptr指定的删除器方法比较简单，一般只需要在参数中添加具体的删除器函数即可；       
         
         //shared_ptr<int> p(new int(100), mydelete);
         //shared_ptr<int> p2(p);
         //p2.reset();  // 剩一个引用计数，p2位nullptr
         //p.reset();  // 因为此时只有1个
         
         // 删除器可以是一个lambda表达式
        //shared_ptr<int> p2(new int(100), [](int *p) {
        //    delete p;
        //
        //});

        // 有些情况默认删除器处理不了(用shared_ptr管理动态数组)， 需要我们提供自己指定的删除器
        //shared_ptr<int> p(new int[], [](int *p) {
        //    delete[]p;
        //});

        //shared_ptr<A> pA(new A[10]); // 异常因为系统释放pA是delete，pA所指向的指针，而不是delete[]pA,这种情况下会有异常
        //shared_ptr<A> pA(new A[10], [](A *p){
        //    delete[]p;
        //});
        // 
        // 可以用default_delete来做删除器，default_delete是标准库里的模板.
        //shared_ptr<A> pA(new int[10], std::default_delete<A[]>());
        // 定义数组的时候我们在尖括号中加[]
        //shared_ptr<A[]> pA(new A[10]);
        //shared_ptr<int[]> p(new int[10]);
        //shared_ptr<int> ptArr = make_shared_array<int>(5);

        //// (b)指定删除器额外说明
        //// 计算这两个删除器指定了不同的删除器，只要他们所指向的对象类型相同，那么这两个shared_ptr也属于同一个类型
        //auto lambda1 = [](int *p){
        //    delete p;
        //};

        //auto lambda2 = [](int *p) {
        //    delete p;
        //};

        //shared_ptr<int> p1(new int(100), lambda1);
        //shared_ptr<int> p2(new int(200), lambda2);
        //p2 = p1;  //p2会先调用lambda2把自己所指向的对象释放，然后指向p1所指向的对象，p1指向的对象引用计数为2
        // 这个main执行完毕后，还会调用lambda1来释放p1,p2共同指向的对象

        // 类型相同，就代表可以放到类型元素为该对象类型的容器里来
        // make_shared:是提倡生成shared_ptr的方法，但是这种make_shared这种方法，让我们没有方法指定自己的删除器。




          return;
    }

}
