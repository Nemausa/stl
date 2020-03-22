#pragma once

#include <iostream>
using namespace std;
#include <memory>
#include <string>

namespace unique
{
    auto myfunc()
    {
        return unique_ptr<string>(new string("I Love Chian"));
    }

    void main()
    {
        // 一：unique_ptr概述
        // 独占式的概念（专属所有权）：同一时刻只有一个unique_ptr指针指向这个对象
        // 这个unique_ptr被销毁时，它所指向的对象也被销毁

        // (1.1)常规初始化
        //unique_ptr<int> pi;  // 可以指向int对象的一个空智能指针
        //unique_ptr<int> pi2(new int(100));

        // (2.1)make_unique函数
        // C++11中没有，C++14才有的，不支持指定删除器，如果不指定删除器，则优先使用，更高的性能。
        //unique_ptr<int> p1 = make_unique<int>(100);
        //auto p2 = make_unique<int>(200);

        // unique_ptr的常规操作
        // (2.1)不支持的操作
        //unique_ptr<string> ps1(new string("I Love China"));
        // unique_ptr<string> ps2(ps1);  // 该智能指针不支持拷贝操作（定义时初始化）
        // unique_ptr<string> ps3 = ps1;  // 不支持拷贝操作 和赋值

        // (2.2)移动语义
        //unique_ptr<string> ps1(new string("I Love China"));
        //unique_ptr<string> ps2 = std::move(ps1);  // 移动后ps1为空，ps2指向原来的对象

        // (2.3)release():放弃 对这个指针的控制权(切断了智能指针和所指向对象之间的联系)
        // 返回裸指针，将该智能指针置空。返回的这个裸指我们可以手工delete，也可以用来初始化另外一个智能指针，或者给另外一个智能指针赋值。
        /*unique_ptr<string> ps1(new string("I Love China"));
        unique_ptr<string> ps2(ps1.release());
        if(ps1 == nullptr)
        {
            cout << "ps1被置空" << endl;
        }*/

        // (2.4)reset()
        // 不带参数的情况：释放智能指针所指向的对象，并将智能指针置空。
        unique_ptr<string> ps1(new string("I Love China"));
        ps1.reset();
        if(nullptr == ps1)
        {
            cout << "ps1被置空" << endl;
        }

        // 带参数的情况：释放智能指针所指向的对象，并让该智能指针指向新的对象
        unique_ptr<string> ps2(new string("I Love China"));
        ps1.reset(ps2.release);  // reset释放ps1指向的对象内存， 让ps1指向ps2所指向的内存，同时ps2被置空

        // (2.5)=nullptr：释放智能指针所指向的对象，并将智能指针置空
        ps1 = nullptr;  // 释放ps1指向的对象，并将ps1置空

        // (2.6)指向一个数组
        unique_ptr<int[]> ptarray(new int[10]);  // 主要这里的数组要跟上[]

        // (2.7)get()：返回智能指针的裸指针
        string *ps = ps1.get();
        *ps = "This is a test!";
        delete ps;  // 不可以，否则产生不可预料的后果

        // (2.8)*解引用：获取该智能指针所指向的对象，可以直接操作
        unique_ptr<string> ps2(new string("I Love China"));
        *ps2 = "This is a test!";

        unique_ptr<int[]> pt2(new int[10]);  // 对于定的内容是数组，是没有*解引用运算符的
        
        // (2.9) swap():交换两个智能指针所指向的对象
        // (2.10)智能指针名字作为判断条件
        // (2.11)转换成shared_ptr类型：如果unique_ptr为右值，就可以将它赋值给shared_ptr
        // 因为shared_ptr包含一个显示构造函数，可用于将右值unqiue_ptr转换成shared_ptr。

        shared_ptr<string> pss1 = myfunc();  // 这里会创建控制块
        unique_ptr<string> ps2(new string("I Love China"));
        shared_ptr<string> pss2 = std::move(ps2);



    
    }

}