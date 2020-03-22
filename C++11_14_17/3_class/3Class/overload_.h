﻿#pragma once
#include <iostream>
using namespace std;
#include "time.h"

namespace overload_
{

    int main()
    {
        // 一：重载运算符
        // 说白了，我们要重载一个成员函数，这个成员函数名"operator =="，在这个成员函数体里面，我们需要写一些比较逻辑。
        // 重载运算符，本质上是一个函数，整个函数的正式名字：operator关键字 接 运算符
        // 既然重载运算符本质上是一个函数，那么会有返回类型和参数列表
        // 有一些运算符，我们不自己写该运算符的重载，那么系统会自动给我们生成一个。比如赋值运算符


        // 二：拷贝赋值运算符
        Time t;  // 调用了Time::Time构造函数
        Time t2 = t;  // 拷贝构造
        Time t5 = { t };  // 拷贝构造

        Time t6; // 调用了Time::Time()构造函数
        t6 = t5;  // 这个赋值运算符，既没有调用构造函数，也没有调用拷贝构造函数。
        // 系统会调用一个拷贝赋值运算符

        // 我们可以自己重载赋值运算符，如果我们自己不重载，编译器也会为我们生成一个。
        // 编译器生成的赋值运算符重载比较粗糙。一般就是将 非static成员赋值非赋值运算符左侧的对应成员中。
        // 如果这个成员是个类对象的话，可能还是调用这个类的拷贝赋值运算符。
        // 为了精确控制Time类的赋值动作，我们往往会自己来虫子啊赋值运算符。
        // 重载赋值运算符：有返回类型和参数列表，我们这里的参数就表示运算符的运算对象，

        // 三：析构函数：相对于构造函数。系统在销毁的时候，会自动调用析构函数。
        // 如果我么自己不写自己的析构函数，编译器也会生成一个默认的析构函数，默认析构函
        // 数的函数体为空，表示默认析构函数没有干什么有意义的事情。
        // 析构函数也类的成员函数，它的名字是由~接类名构成，没有返回值，不接受任何参数，
        // 不能被重载，所以一个给定的类，只有唯一的一个析构函数

        // 函数重载：就是系统运行函数名字相同，但是这些同名函数的参数个数或者参数类型不同，系统运行这同名函数同时存在。
        // 当我们调用这些函数的时候，系统根据调用这个函数是我们提供的参数类型，参数个数，就能区别出你到底想调用哪个函数。

        // 构造函数的成员初始化：干了两个事，函数体之前和函数体之中
        // 析构函数的成员销毁：干了两个事，函数体和函数体之后
        // 成员变量的初始化和销毁时问题，先定义的先初始化，销毁时先定义的后销毁

        // new和delete对象 new对象的时候，系统调用了Time类的构造函数
        Time *newTime = new Time;  // 调用不带参数的构造函数
        Time *newTime6 = new Time();  // 调用不带参数的构造函数
        // 但是大家注意，我们new出来的对象，必须自己释放，否则就会造成内存泄漏。
        // 在这个程序运行的某个时刻，我们一定要用delete把对象占用的内存释放掉。
        delete newTime;
        delete newTime6;

        // 你什么时候delete，系统就会在什么时候调用类的析构函数。


        return 0;
    }
}