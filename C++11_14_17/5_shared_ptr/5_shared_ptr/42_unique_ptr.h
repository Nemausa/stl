#pragma once

#include <iostream>
using namespace std;
#include <memory>
#include <string>

namespace unique2
{

    unique_ptr<string> tuniqp()
    {
        unique_ptr<string> ptr(new string("I love China"));
        return ptr;
    }

    void mydelete(string *p)
    {
        delete p;
        p = nullptr;
    }



    void main()
    {
        //unique_ptr<string> ps;
        //ps = tuniqp();  // 可以用ps来接，则临时对象直接构造在ps里，如果不接，则临时对象会被释放，同时释放所指向的内存

        // 指定删除器 delete：默认删除器
        // (a)指定删除器
        // 格式：unique_ptr<指向的对象，删除器> 智能指针变量名
        // 删除器，可调用对象，比如函数，类重载()
        // a.1
        // typedef void(*fp)(string *);  // 定义一个函数指针类型，类型名为fp
        //unique_ptr<string, fp> ps1(new string("I love China"), mydelete);

        // a.2
        //using fp2 = void(*)(string*);  // 用using来定义一个函数指针类型
        //unique_ptr<string, fp2> ps2(new string("I love China"), mydelete);

        // a.3
        //typedef decltype(mydelete)* fp3;  // 这里多个*，因为decltype返回的是void(string*)
        // 加*表示函数指针类型，现在fp3应该 void *(string*)
        //unique_ptr<string, fp3> ps3(new string("I love China"), mydelete);

        // a.4
        //unique_ptr<string, decltype(mydelete)*> ps4(new string("I love China"), mydelete);

        // a.5 用lambad表示
        // 所以decltype(mydella) = class {...} 理解成一个class
        //auto mydella = [](string *p){
        //    delete p;
        //    p = nullptr;
        //};
        //unique_ptr<string, decltype(mydella)> ps5(new string("I love China"), mydella);

        // b指定删除器额外说明
        // shared_ptr：计算两个删除器不一样，只要他们所指向的对象相同，那么两个shared_ptr也属于同一个类型
        // unqiue_ptr不一样，指定unqiue_ptr中的删除器会影响unique_ptr的类型，所以从灵活性来讲，shared_ptr更加好
        // shared_ptr删除器不同，可以放到同一个容器里，unique_ptr则不行

        
        // 三：尺寸问题：通常情况下unqiue_ptr尺寸跟裸指针一样，如果增加了自己的删除器，尺寸可能增加也可能不增加
        // a)如果是lambda表达式这种删除器，尺寸么有变化
        // b)定义一个函数作为删除器
        typedef void(*fp)(string *);  // 定义一个函数指针类型，类型名为fp
        unique_ptr<string, fp> ps1(new string("I love China"), mydelete);
        int ilen = sizeof(ps1);  // 尺寸发生了变化，变成了8字节

        // 增加字节对效率有影响，所以自定义删除器要慎用
        // shared_ptr,不管你指定什么删除器，shared_ptr的尺寸都是裸指针的两倍


        // 四：智能指针的总结
        // 4.1）智能指针背后的设计思想
        // 智能指针的主要目的：帮助我们释放内存，以防止我们忘记释放内存造成内存泄漏

        // 4.2)auto_ptr为什么被废弃
        // 不能在容易中保存，也不能在函数中返回auto_ptr
        auto_ptr<string> ps(new string("I lvoe China"));
        auto_ptr<string> ps2(ps); // ps2指向字符串，ps变成空，防止ps1和ps2析构一个string两次
        // 用ps（你没有意识到ps已经空了），代码会崩溃
        // 这个也是auto_ptr用法上的缺陷

        // 4.3)智能指针的选择
        // 如果程序要使用多个指向同一个对象的指针，应该选择shared_ptr
        // 如果程序不需要多个指向同一个对象的指针，应该首选unique_ptr





        return;
    }

}