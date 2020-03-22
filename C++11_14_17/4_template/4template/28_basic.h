﻿//////////////////////////////////////////////////////////////////////////
//  @file     basic.h
//  @author   Morris
//  @date     2019-03-18
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-18
//  -added 
//  @remark   模板的定义 调用
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include <vector>


namespace basic
{
    template<typename T>
    T funcadd(T a, T b)
    {
        T addhe = a + b;
        return addhe;
    }

    template<int a, int b>
    int funcadd2()
    {
        int addhe = a + b;
        return addhe;
    }

    template<class T, int a, int b>
    int funcadd3(T c)
    {
        int addhe = static_cast<int>(c) + b + a;
        return addhe;
    }

    template<unsigned L1, unsigned L2>  // 本例中仍旧没有类型参数
    inline // 模板函数可以是inline，inline放在模板参数之后
    int charscomp(const char(&p1)[L1], const char(&p2)[L2])
    {
        return strcmp(p1, p2);
    }


    int main()
    {
        // 一：概述
        // 几句话
        // (1)所谓泛型编程是独立于特定类型的方式编写代码。使用泛型编程是，我们需要提供具体程序实例所操作的类习惯或者值
        // (2)模板是泛型编程的基础。模板是创建类或者函数的蓝图或公式，我们给这些蓝图或者公式提供足够的信息，让这些蓝图或者公式真正的转变为具体的类或者函数，这种转变发生在编译时。
        // (3)模板支持将类型作为参数的程序设计方式，从而实现了对泛型程序设计的直接支持。也就是说，C++模板机制允许在类定义、函数时将类型作为参数。

        // 模板一般分为函数模板和类模板  本节课主要讲函数模板

        // 二：函数模板的定义
        // (1)模板定义是用template关键字开头，后面跟<>，<>里面叫模板参数列表(模板实参),如果模板参数列表里面有多个参数，则用逗号分开。
        // <>里面至少得有一个模板参数,模板参数前面有个typename/class关键字。
        // 如果模板参数列表里面有多个模板参数，那你就要用多个typename/class:<typename T, typename Q>
        // (2)模板参数列表里面表示在函数定义中药用到的"类型"或者"值",也和函数参数列表类似。
        // 那我们用的时候，有的时候指定模板实参给它，指定的时候我们要用<>把模板参数包起来，有的时候又不需要指定模板实参给它
        // 系统能更加一些信息判断出来，后续我们会举例

        // 三：函数模板的使用
        // 函数模板调用和函数调用区别不大，调用的时候，编译器会根据你调用的函数模板时的实参去推断模板参数列表里的参数(形参)的类型
        // 大家一定要注意措辞:模板参数是推断出来的，推断的依据是什么，根据你调用这个函数的实参来推断的。
        // 当然有的时候，光凭函数实参不能推断出模板参数，这个时候就要用<>来主动的提供模板参数了。
        // int he = funcadd(1, 2);  // 系统认为是int，所以编译器能够推断出来的模板形参是个int型，也就是这个参数T是int型；
        // 编译器在推断出来这个模板的形参类型之后，编译器就为我们实例化一个特定版本的函数。


        // 四：非类型模板参数
        // 因为T前面有个typename/class，这表示T代表一个类型，是一个类型参数.
        // 那么在模板参数列表里，还可以定义非类型参数;
        // 既然非类型代表一个值，那么肯定不能用typename/class这种关键字来修饰这个值了。
        // 我们要用以往学习的传统类型名来指定非类型参数
        // 当模板被实例化时，这种非类型模板参数的值或者用户提供的，或者是编译器推断的都有可能。
        // 但是这些值必须是常量表达式，因为实例化这些模板是编译器在编译时实例化的。
        // std::cout << funcadd2<12, 13>() << endl;  // 显示的指定模板参数  在<>中提供额外的信息
        //int a = 12;
        //int result = funcadd2<a, 13>();  // 不可以，值必须是在编译时就能确定

        //int result = funcadd3<int, 11, 12>(13);  // 系统会以<>传递的类型为准，而不是13判断类型
        //cout << result << endl;

        int result3 = charscomp("test2", "test");  // 没有提供非类型模板参数系统会根据字符串长度推断L1,L2。

        // 模板定义并不会导致编译器生成代码，只有在我们调用这个函数模板时，
        // 编译器才会实例化一个特定版本的函数之后，编译器才会生成代码
        // 编译器生成代码的时候，需要能够找到函数体，所以模板的定义通常都是在.h文件中
        return 0;
    }

}

#endif